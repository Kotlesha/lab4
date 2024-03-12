#include <ctime>
#include <iostream>

void matrixInitialize(int**& outMatrix, int size) {
    outMatrix = new int* [size];
    for (int i = 0; i < size; i++)
        outMatrix[i] = new int[size];
}

void matrixGenerate(int** outMatrix, int size, int start, int end) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            outMatrix[i][j] = rand() % (end - start + 1) + start;
}

void matrixSplit(int** matrix, int size, int finalSize, int*** outMatrices) 
{
    for (int i = 0; i < finalSize; i++)
        for (int j = 0; j < finalSize; j++)
        {
            outMatrices[0][i][j] = matrix[i][j];
            outMatrices[1][i][j] = matrix[i][j + finalSize];
            outMatrices[2][i][j] = matrix[i + finalSize][j];
            outMatrices[3][i][j] = matrix[i + finalSize][j + finalSize];
        }
}

//void matrixSplit(int** matrix, int size, int finalSize, int*** outMatrices)
//{
//    //for (int i = 0; i < finalSize; ++i) {
//    //    outMatrices[0][i] = &matrix[i][0];
//    //    outMatrices[1][i] = &matrix[i][finalSize];
//    //    outMatrices[2][i] = &matrix[finalSize + i][0];
//    //    outMatrices[3][i] = &matrix[finalSize + i][finalSize];
//    //}
//
//    for (int i = 0; i < finalSize; ++i) {
//        memcpy(outMatrices[0][i], &matrix[i][0], finalSize * sizeof(int));
//        memcpy(outMatrices[1][i], &matrix[i][finalSize], finalSize * sizeof(int));
//        memcpy(outMatrices[2][i], &matrix[finalSize + i][0], finalSize * sizeof(int));
//        memcpy(outMatrices[3][i], &matrix[finalSize + i][finalSize], finalSize * sizeof(int));
//    }
//}

void matrixMultiply(int** matrix1, int** matrix2, int size, int** outMatrix) 
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            outMatrix[i][j] = 0;

            for (int k = 0; k < size; k++)
                outMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
        }
}

void matrixAddition(int** matrix1, int** matrix2, int size, int** outMatrix) 
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            outMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
}

void matrixDispose(int**& outMatrix, int size) {
    for (int i = 0; i < size; i++)
        delete[] outMatrix[i];

    delete[] outMatrix;
}

void matrixPrint(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            std::cout << matrix[i][j] << "\t";

        std::cout << std::endl;
    }
}