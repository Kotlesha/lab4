#include <math.h>

#define M 1
#define Parts 4
#define Start 10
#define End 99

const int MATRIX_SIZE = M * 4;
const int PART_SIZE = MATRIX_SIZE / sqrt(Parts);
const int VARIANTS[8][2] = { {0,0} , {1,2} , {0,1} , {1,3} , {2,0} , {3,2} , {2,1} , {3,3} };