#include "matrix.h"
#include "constants.h"

void initializeMatrices(int** &outMatrix1, int** &outMatrix2, int** &outMatrix3) {
    initializeMatrix(outMatrix1, MATRIX_SIZE);
    initializeMatrix(outMatrix2, MATRIX_SIZE);
    initializeMatrix(outMatrix3, MATRIX_SIZE);
}

void createMatrices(int** outMatrix1, int** outMatrix2) {
    generateMatrix(outMatrix1, MATRIX_SIZE, Start, End);
    generateMatrix(outMatrix2, MATRIX_SIZE, Start, End);
}

void splitMatrices(int** matrix1, int** matrix2, int*** outSubMatrices1, int*** outSubMatrices2) {
    splitMatrix(matrix1, PART_SIZE, outSubMatrices1);
    splitMatrix(matrix2, PART_SIZE, outSubMatrices2);
}

void freeMatrices(int** matrix1, int** matrix2, int** matrix3) {
    disposeMatrix(matrix1,MATRIX_SIZE);
    disposeMatrix(matrix2, MATRIX_SIZE);
    disposeMatrix(matrix3, MATRIX_SIZE);
}

void freeSubMatrices(int*** subMatrix1, int*** subMatrix2) {
    for (int i = 0; i < Parts; i++) {
        disposeMatrix(subMatrix1[i], PART_SIZE);
        disposeMatrix(subMatrix2[i], PART_SIZE);
    }
    free(subMatrix1);
    free(subMatrix2);
}