#include <stdio.h>
#include <stdlib.h>
#include "NS.h"

void init(array* arr, int cap){
    arr->data = malloc(cap * sizeof(int));
    if (!arr->data) {
        perror("malloc failed");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = cap;
}

void append(array* arr, int element){
    if(arr->size == arr->capacity){
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = element;
}

void clear(array* arr){
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void number_systems(int x, int y){
    array arr;
    init(&arr, 1);
    while(x != 0){
        append(&arr, x%y);
        x /= y;
    }
    for(int i = arr.size-1; i >= 0; i--){
        printf("%d", arr.data[i]);
    }
    clear(&arr);
}

void print5(){
    int x,y;
    scanf("%d %d", &x, &y);
    number_systems(x,y);
}