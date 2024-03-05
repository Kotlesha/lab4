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

void matrixSplit(int** matrix, int finalSize, int*** outMatrices) {}

void matrixMultiply(int** matrix1, int** matrix2, int size, int** outMatrix) 
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            outMatrix[i][j] = 0;

            for (int k = 0; k < size; k++)
                outMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
        }
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
    outMatrix = nullptr;
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