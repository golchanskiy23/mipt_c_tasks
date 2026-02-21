#ifndef NS_H
#define NS_H

#include <stddef.h>

typedef struct{
    int* data;
    int size;
    int capacity;
} array;

void init(array* arr, int cap);
void append(array* arr, int element);
void clear(array* arr);
void number_systems(int x, int y);
void print5();

#endif