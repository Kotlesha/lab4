#include "mpi_communication.h"
#include "rank_zero_functions.h"
#include <map>

int main(int argc, char** argv) {
    srand(time(0));
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 8)
    {
        std::cout << "Incorrect number of processes!" << std::endl;
        return -1;
    }

    int** matrix1, ** matrix2, ** resultMatrix, ** subMatrix1, ** subMatrix2;
    int*** subMatrices1, *** subMatrices2;

    matrixInitialize(subMatrix1, PART_SIZE);
    matrixInitialize(subMatrix2, PART_SIZE);

    MPI_Datatype row;
    MPI_Type_contiguous(PART_SIZE, MPI_INT, &row);
    MPI_Type_commit(&row);

    if (rank == 0) {
        initializeMatrices(matrix1, matrix2, resultMatrix);
        createMatrices(matrix1, matrix2);

        std::cout << "Matrix 1:" << std::endl;
        matrixPrint(matrix1, MATRIX_SIZE);
        std::cout << std::endl;

        std::cout << "Matrix 2:" << std::endl;
        matrixPrint(matrix2, MATRIX_SIZE);
        std::cout << std::endl;

        initializeSubMatrices(subMatrices1, subMatrices2);
        splitMatrices(matrix1, matrix2, subMatrices1, subMatrices2);

        for (int i = 1; i < size; i++)
        {
            const int* processNumSubMatrices = VARIANTS[i];

            subMatrix1 = subMatrices1[processNumSubMatrices[0]];
            subMatrix2 = subMatrices2[processNumSubMatrices[1]];

            packAndSendMatrix(subMatrix1, PART_SIZE, i, row);
            packAndSendMatrix(subMatrix2, PART_SIZE, i, row);
        }

        subMatrix1 = subMatrices1[VARIANTS[0][0]];
        subMatrix2 = subMatrices2[VARIANTS[0][1]];
    }
    else 
    {
        recvAndUnpackMatrix(subMatrix1, PART_SIZE, 0, row);
        recvAndUnpackMatrix(subMatrix2, PART_SIZE, 0, row);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double startTime = MPI_Wtime();

    int** subMatrixResultEven;
    matrixInitialize(subMatrixResultEven, PART_SIZE);

    if (rank % 2 == 0)
    {
        matrixMultiply(subMatrix1, subMatrix2, PART_SIZE, subMatrixResultEven);
        packAndSendMatrix(subMatrixResultEven, PART_SIZE, rank + 1, row);
    }
    else
    {
        int** subMatrixResultOdd;
        matrixInitialize(subMatrixResultOdd, PART_SIZE);
        recvAndUnpackMatrix(subMatrixResultEven, PART_SIZE, rank - 1, row);

        matrixMultiply(subMatrix1, subMatrix2, PART_SIZE, subMatrixResultOdd);
        matrixAddition(subMatrixResultEven, subMatrixResultOdd, PART_SIZE, subMatrixResultEven);

        matrixDispose(subMatrixResultOdd, PART_SIZE);
        packAndSendMatrix(subMatrixResultEven, PART_SIZE, 0, row);
    }

    if (rank == 0)
    {
        std::map<int, int**> allSubMatrices;
        matrixInitialize(resultMatrix, MATRIX_SIZE);

        for (int i = 0; i < Parts; i++)
        {
            int** resultSubMatrix;
            matrixInitialize(resultSubMatrix, PART_SIZE);
            int sourceRank = recvAndUnpackMatrix(resultSubMatrix, PART_SIZE, MPI_ANY_SOURCE, row);
            allSubMatrices[sourceRank] = resultSubMatrix;
        }

        mergeAllSubMatrices(allSubMatrices, resultMatrix);
        freeAllSubMatrices(allSubMatrices);

        std::cout << "Result matrix:" << std::endl;
        matrixPrint(resultMatrix, MATRIX_SIZE);

        //freeMatrices({ {std::ref(matrix1), MATRIX_SIZE}, {std::ref(matrix2), MATRIX_SIZE}, {std::ref(resultMatrix), MATRIX_SIZE} });
        freeMatrices(matrix1, matrix2, resultMatrix);
        freeSubMatrices(subMatrices1, subMatrices2);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    double endTime = MPI_Wtime();

    if (rank == 0) std::cout << "Total time: " << endTime - startTime << std::endl;

    matrixDispose(subMatrixResultEven, PART_SIZE);
    MPI_Type_free(&row);
    MPI_Finalize();
    return 0;
}

