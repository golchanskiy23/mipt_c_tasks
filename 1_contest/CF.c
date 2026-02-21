#include <stdio.h>

void chain(long long a, long long b){
    while(b != 0){
        long long c = a/b;
        printf("%d ", c);
        long long tmp = a;
        a = b;
        b = tmp%b;
    }
}

void print2(){
    long long a,b;
    scanf("%d %d", &a , &b);
    chain(a,b);
}