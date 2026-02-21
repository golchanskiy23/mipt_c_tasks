#include <stdio.h>
#include <stdbool.h>
#include "FM.h"

unsigned long long find_pizano_period(unsigned long long m){
    if(m == 0) return 0;
    if(m == 1) return 1;
    unsigned long long curr=0, next=1, period=1;
    while(true){
        unsigned long long oldNext = next;
        next = (curr+next)%m;
        curr = oldNext;
        if(curr == 0 && next == 1){
            break;
        }
        period++;
    }
    return period;
}

void pizano(unsigned long long m){
    unsigned long long period = find_pizano_period(m);
    printf(" %llu", period);
}

unsigned long long fibonacci_mod(unsigned long long n, unsigned long long m){
    if(n == 0) return 0;
    if(n == 1) return 1;
    if(m == 0) {
        unsigned long long prev = 0, next = 1, curr;
        for(unsigned long long i = 2; i <= n; i++){
            curr = prev + next;
            prev = next;
            next = curr;
        }
        return curr;
    }
    unsigned long long prev = 0, next = 1, curr;
    for(unsigned long long i = 2; i <= n; i++){
        curr = ((prev%m)+(next%m))%m;
        prev = next;
        next = curr;
    }
    return curr;
}

void print9(){
    unsigned long long x,m;
    scanf("%llu %llu", &x, &m);
    
    if(m == 0){
        unsigned long long result = fibonacci_mod(x, 0);
        printf("%llu 0", result);
        return;
    }
    
    unsigned long long period = find_pizano_period(m);
    unsigned long long reduced_x = x % period;
    unsigned long long result = fibonacci_mod(reduced_x, m);
    
    printf("%llu %llu", result, period);
}