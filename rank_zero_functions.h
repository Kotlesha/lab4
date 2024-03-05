#include "matrix.h"
#include "constants.h"

void initializeMatrices(int** &outMatrix1, int** &outMatrix2, int** &outMatrix3) {
    matrixInitialize(outMatrix1, MATRIX_SIZE);
    matrixInitialize(outMatrix2, MATRIX_SIZE);
    matrixInitialize(outMatrix3, MATRIX_SIZE);
}

void createMatrices(int** outMatrix1, int** outMatrix2) {
    matrixGenerate(outMatrix1, MATRIX_SIZE, Start, End);
    matrixGenerate(outMatrix2, MATRIX_SIZE, Start, End);
}

void splitMatrices(int** matrix1, int** matrix2, int*** outSubMatrices1, int*** outSubMatrices2) {
    matrixSplit(matrix1, PART_SIZE, outSubMatrices1);
    matrixSplit(matrix2, PART_SIZE, outSubMatrices2);
}

void freeMatrices(int** matrix1, int** matrix2, int** matrix3) {
    matrixDispose(matrix1,MATRIX_SIZE);
    matrixDispose(matrix2, MATRIX_SIZE);
    matrixDispose(matrix3, MATRIX_SIZE);
}

void freeSubMatrices(int*** subMatrix1, int*** subMatrix2) {
    for (int i = 0; i < Parts; i++) {
        matrixDispose(subMatrix1[i], PART_SIZE);
        matrixDispose(subMatrix2[i], PART_SIZE);
    }

    free(subMatrix1);
    free(subMatrix2);
}