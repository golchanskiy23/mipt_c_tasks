#ifndef MF_H
#define MF_H

typedef struct{
    int x00, x01, x10, x11;
} Matrix;

void print11();
Matrix create_matrix(int, int, int, int);
Matrix multiply(Matrix,Matrix,int);
void multiply_matrix(Matrix,int,int);

#endif