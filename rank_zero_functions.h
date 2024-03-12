#include "matrix.h"
#include "constants.h"
#include <vector>
#include <map>

void initializeMatrices(int** &outMatrix1, int** &outMatrix2, int** &outMatrix3) {
    matrixInitialize(outMatrix1, MATRIX_SIZE);
    matrixInitialize(outMatrix2, MATRIX_SIZE);
    matrixInitialize(outMatrix3, MATRIX_SIZE);
}

void initializeSubMatrices(int*** &outSubMatrices1, int*** &outSubMatrices2)
{
    outSubMatrices1 = new int** [Parts];
    outSubMatrices2 = new int** [Parts];

    for (int i = 0; i < Parts; i++)
    {
        matrixInitialize(outSubMatrices1[i], PART_SIZE);
        matrixInitialize(outSubMatrices2[i], PART_SIZE);
    }
}

void createMatrices(int** outMatrix1, int** outMatrix2) {
    matrixGenerate(outMatrix1, MATRIX_SIZE, Start, End);
    matrixGenerate(outMatrix2, MATRIX_SIZE, Start, End);
}

void splitMatrices(int** matrix1, int** matrix2, int*** outSubMatrices1, int*** outSubMatrices2) {
    matrixSplit(matrix1, MATRIX_SIZE, PART_SIZE, outSubMatrices1);
    matrixSplit(matrix2, MATRIX_SIZE, PART_SIZE, outSubMatrices2);
}

//void freeMatrices(std::vector<std::pair<std::reference_wrapper<int**>, int>> args) {
//    for (auto& matrixPair : args) {
//        int** matrix = matrixPair.first.get();
//        int size = matrixPair.second;
//        matrixDispose(matrix, size);
//    }
//}

void freeMatrices(int** &matrix1, int** &matrix2, int** &matrix3)
{
    matrixDispose(matrix1, MATRIX_SIZE);
    matrixDispose(matrix2, MATRIX_SIZE);
    matrixDispose(matrix3, MATRIX_SIZE);
}

void freeSubMatrices(int*** &subMatrices1, int*** &subMatrices2) {
    for (int i = 0; i < Parts; i++) {
        matrixDispose(subMatrices1[i], PART_SIZE);
        matrixDispose(subMatrices2[i], PART_SIZE);
    }

    delete[] subMatrices1;
    delete[] subMatrices2;
}

void mergeAllSubMatrices(std::map<int, int**>& allSubMatrices, int** resultMatrix)
{
    for (int i = 0; i < PART_SIZE; i++)
        for (int j = 0; j < PART_SIZE; j++)
        {
            resultMatrix[i][j] = allSubMatrices[1][i][j];
            resultMatrix[i][j + PART_SIZE] = allSubMatrices[3][i][j];
            resultMatrix[i + PART_SIZE][j] = allSubMatrices[5][i][j];
            resultMatrix[i + PART_SIZE][j + PART_SIZE] = allSubMatrices[7][i][j];
        }
}

void freeAllSubMatrices(std::map<int, int**>& allSubMatrices) {
    for (auto& pair : allSubMatrices) {
        int** &matrixPtr = pair.second;
        matrixDispose(matrixPtr, PART_SIZE);
    }

    allSubMatrices.clear(); 
}