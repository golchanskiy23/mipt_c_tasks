#include <stdio.h>

void fibonacci(int n, int m){
    if(n == 0){
        printf("%llu", 0);
        return;
    } else if(n==1){
        printf("%llu", 1);
        return;
    }
    long long prev = 0, next = 1, curr;
    for(int i = 2; i <= n; i++){
        curr = ((prev%m)+(next%m))%m;
        prev = next;
        next = curr;
    }
    printf("%llu", curr);
}

void print8(){
    long long n,m;
    scanf("%llu %llu", &n,&m);
    fibonacci(n,m);
}