#include <mpi.h>
#include "rank_zero_functions.h"

int main(int argc, char** argv) {
    srand(time(0));
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int** matrix1, ** matrix2, ** resultMatrix;

    MPI_Datatype row;
    MPI_Type_contiguous(PART_SIZE, MPI_INT, &row);
    MPI_Type_commit(&row);

    if (rank == 0) {
        initializeMatrices(matrix1, matrix2, resultMatrix);
        createMatrices(matrix1, matrix2);

        int*** subMatrices1, *** subMatrices2;
        splitMatrices(matrix1, matrix2, subMatrices1, subMatrices2);

        //i
        //j
        // 
        //k
        //l
    }
    else {
        
    }


    MPI_Type_free(&row);
    MPI_Finalize();
    return 0;
}

