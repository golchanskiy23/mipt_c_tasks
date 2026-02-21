#include <stdio.h>

// return gcd(a,b)=ax+by
long long extended_gcd(long long a, long long b, long long *x, long long *y){
    if(b == 0){
        *x = 1;
        *y = 0;
        return a;
    }
    
    long long x1, y1;
    long long d = extended_gcd(b, a%b, &x1, &y1);
    *x = y1;
    *y = x1 - (a/b)*y1;
    return d;
}

void print3(){
    long long a,b, x,y;
    scanf("%lld %lld", &a, &b);
    long long d = extended_gcd(a, b, &x, &y);
    if (d < 0) {
        d = -d;
        x = -x;
        y = -y;
    }
    printf("%lld %lld %lld", x, y, d);
}
