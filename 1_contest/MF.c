#include <stdio.h>
#include "MF.h"

Matrix create_matrix(int a, int b, int c, int d){
    Matrix m = { a, b, c, d };
    return m;
}

Matrix multiply(Matrix a, Matrix b, int m){
    Matrix ans;
    ans.x00 = ((a.x00*b.x00)%m + (a.x01*b.x10)%m)%m;
    ans.x01 = ((a.x00*b.x01)%m + (a.x01*b.x11)%m)%m;
    ans.x10 = ((a.x10*b.x00)%m + (a.x11*b.x10)%m)%m;
    ans.x11 = ((a.x10*b.x01)%m + (a.x11*b.x11)%m)%m;
    return ans;
}

void multiply_matrix(Matrix matrix, int n, int m){
    Matrix E = create_matrix(1,0,0,1);
    E.x00 %= m;
    E.x01 %= m;
    E.x10 %= m;
    E.x11 %= m;
    while(n > 0){
        if(n%2==1){
            E = multiply(E, matrix, m);
        }
        matrix = multiply(matrix, matrix, m);
        n /= 2;
    }
    printf("%d %d %d %d", E.x00, E.x01, E.x10, E.x11);
}

void print11(){
    int a,b,c, d, n,m;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &n, &m);
    Matrix matrix = create_matrix(a,b,c,d);
    multiply_matrix(matrix, n, m);
}