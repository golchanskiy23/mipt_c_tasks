#include <stdio.h>
#include "NS.h"

int arr[47];

void init_fibonacci(){
    arr[0] = 0;
    arr[1] = 1;
    for(int i = 2; i <= 46; i++){
        arr[i] = arr[i-1]+arr[i-2];
    }
}

void fibonacci_system(int x){
    array a;
    init(&a, 1);

    for(int i = 46; i >= 2; i--){
        if(x >= arr[i]){
            while(i >= 2){
                if(x >= arr[i]){
                    x -= arr[i];
                    append(&a, 1);
                } else{
                    append(&a, 0);
                }
                i--;
            }
            break;
        }
    }
    for(int i = 0; i < a.size; i++){
        printf("%d",a.data[i]);
    }
    clear(&a);
}

void print10(){
    int x;
    scanf("%d", &x);
    init_fibonacci();
    fibonacci_system(x);
}