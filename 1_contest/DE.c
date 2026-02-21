#include <stdio.h>
#include "EE.h"

void solve_diophant(long long a, long long b, long long c){
    long long x_0, x_1;
    long long d = extended_gcd(a,b, &x_0, &x_1);
    if(c%d != 0){
        printf("NONE");
        return;
    }
    long long factor = c/d;
    x_0 *= factor;
    x_1 *= factor;
    printf("%lld %lld", x_0, x_1);
}

void print4(){
    long long a,b,c;
    scanf("%lld %lld %lld", &a, &b, &c);
    solve_diophant(a,b,c);
}