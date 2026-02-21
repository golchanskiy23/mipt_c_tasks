#include <stdio.h>

int arr[11];

void factorial(int n){
    arr[0]=1;
    arr[1]=1;
    for(int i = 2; i <= n; i++){
        arr[i] = i*arr[i-1];
    }
}

void factorial_system(int n, int k){
    for(int i = k; i >= 1; i--){
        if(n / arr[i] > 0){
            while(i >= 1){
                printf("%d.", n/arr[i]);
                n -= (n/arr[i])*arr[i];
                i--;
            }
        }
    }
}

void print6(){
    int n;
    scanf("%d", &n);
    factorial(10);
    factorial_system(n, 10);
}