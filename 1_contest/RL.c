#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long gcd( long long x, long long y) {
    long long q;
    if (y < 0){y *= (-1);}
    if (x < 0){x *= (-1);}
    while(true){
        if (y > x){
            long long tmp = x;
            x = y;
            y = tmp;
        }
        assert (y > 0);
        q = x % y;
        if (q == 0) {
            return y;
        }
        x = q;
    }
    return -1;
}


void print1(){
    long long x = 0, y = 0, g;
    int res;
  
    res = scanf("%llu %llu", &x, &y);
    assert(res == 2);
    g = gcd(x, y);
    printf("%llu\n", g);
}