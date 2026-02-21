#include <stdio.h>

unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (exp) {
        if (exp % 2) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void super_pow(unsigned long long a,unsigned long long b,unsigned long long n){
    unsigned long long start = 1;
    for(int i = 0; i < b-1; i++){
        start *= a;
    }
    unsigned long long ans = mod_pow(a,start,n);
    printf("%llu", ans);
}

void print7(){
    unsigned long long a,b,n;
    scanf("%llu %llu %llu", &a, &b, &n);
    super_pow(a,b,n);
}