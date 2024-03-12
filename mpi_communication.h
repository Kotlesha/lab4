#include <mpi.h>
#include "constants.h"

void packAndSendMatrix(int** matrix, int size, int destRank, MPI_Datatype row) {
    char* buffer = new char[BUF_SIZE];
    int position = 0;
    MPI_Request request;

    for (int i = 0; i < size; i++) {
        MPI_Pack(matrix[i], 1, row, buffer, BUF_SIZE, &position, MPI_COMM_WORLD);
    }

    MPI_Isend(buffer, position, MPI_PACKED, destRank, destRank, MPI_COMM_WORLD, &request);
    delete[] buffer;
}

int recvAndUnpackMatrix(int** matrix, int size, int sourceRank, MPI_Datatype row) {
    char* buffer = new char[BUF_SIZE];
    MPI_Request request;

    MPI_Irecv(buffer, BUF_SIZE, MPI_PACKED, sourceRank, MPI_ANY_TAG, MPI_COMM_WORLD, &request);

    MPI_Status status;
    MPI_Wait(&request, &status);

    int position = 0;
    for (int i = 0; i < size; i++) {
        MPI_Unpack(buffer, BUF_SIZE, &position, matrix[i], 1, row, MPI_COMM_WORLD);
    }

    delete[] buffer;
    return status.MPI_SOURCE;
}
