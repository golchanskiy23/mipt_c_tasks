#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

void find_min_max(){
    int n, max = INT_MIN, min = INT_MAX;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int tmp;
        scanf("%d", &tmp);
        if(tmp < min){
            min = tmp;
        }
        if(tmp > max){
            max = tmp;
        }
    }
    printf("%d %d", min, max);
}

int myrand() {
    static unsigned long int seed = 1;
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % 32768;
}

void fisher_yiets(){
    int n;
    scanf("%d", &n);
    if(n == 0){
        printf("%d",0);
        return;
    }
    int* arr = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for(int i = n-1; i > 0; i--){
        int j = myrand()%(i+1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
}


int moveright(int *arr, int key, int last) {
    int i = last-1;
    while(i >= 0 && arr[i] > key){
        arr[i+1] = arr[i];
        i--;
    }
    return i+1;
}

void inssort(int *arr, int len) {
    int i;
    for (i = 0; i < len; ++i) {
      int key, pos;
      key = arr[i];
      pos = moveright(arr, key, i);
      arr[pos] = key;
    }
}

void selection_sort(int* a, int pos, int n){
    int start = pos;
    if (start < n) {
        int minIndex = start;
        for (int i = start + 1; i < n; ++i) {
            if (a[i] < a[minIndex]) {
                minIndex = i;
            }
        }
        if (minIndex != start) {
            int temp = a[start];
            a[start] = a[minIndex];
            a[minIndex] = temp;
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
}

void selection_sort_helper(){
    int n, last;
    scanf("%d",&n);
    int* arr = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
    scanf("%d",&last);
    selection_sort(arr,last,n);
    free(arr);
}

typedef int (*cmp_t)(void const * lhs, void const * rhs);

void template_swap(void* a, void* b, int size){
    char* buffer = malloc(size);
    memcpy(buffer,a,size);
    memcpy(a,b,size);
    memcpy(b,buffer,size);
    free(buffer);
}

//arr это массив, уже отсортированный до позиции nsorted, 
// на этой позиции (с нуля) стоит первый несортированный элемент
//eltsize это размер элементов массива, numelts это количество элементов в массиве
int selstep(void * parr, int eltsize, int numelts, int nsorted, cmp_t cmp) {
    char* arr = (char*)parr;
    char* first_unsorted = arr+(nsorted*eltsize);

    char* min = first_unsorted;
    int remained = numelts - nsorted;

    for(int i = 1; i < remained; i++){
        char* current = first_unsorted+(i*eltsize);
        if(cmp(current,min)){
            min = current;
        }
    }

    if(min != first_unsorted){
        template_swap(min,first_unsorted,eltsize);
    }
    return 0;
}

//Здесь key это элемент, который ищется, 
// base это массив в котором осуществляется поиск, 
// size это размер элементов массива (и, соответственно, элемента key), 
// num это количество элементов в массиве
void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp){
    int left = 0, right = num-1;
    while(left <= right){
        int mid = left+(right-left)/2;
        const char* mid_element = base+(size*mid);
        if(cmp(key,mid_element) < 0){
            right = mid-1;
        } else if(cmp(key,mid_element) > 0){
            left = mid+1;
        } else{
            return (void*)mid_element;
        }
    }
    return NULL;
}

void qsort_impl(int *arr, unsigned low, unsigned high) {
    if (low >= high) return;
    unsigned pi = partition(arr, low, high);
    if (pi > low) qsort_impl(arr, low, pi - 1);
    qsort_impl(arr, pi + 1, high);
}
  
void qsort(int *arr, unsigned len) { qsort_impl(arr, 0u, len - 1); }

unsigned partition(int *arr, unsigned low, unsigned high) {
    unsigned pivot = arr[low], left = low, right = high;
    while(true){
        while(left <= high && arr[left] <= pivot) left++;
        while(right >= low && arr[right] > pivot) right--;
        if(right <= left) break;
        template_swap(&arr[left],&arr[right],sizeof(int));
    }
    template_swap(&arr[low],&arr[right],sizeof(int));
    return right;
}

// [l;m] , [m+1;r]
void merge(int *arr, int l, int m, int r){
    int* tmp = malloc((r-l+1)*sizeof(int));
    int ls = l, rs = m+1, x = 0;
    while(ls <= m && rs <= r){
        while(ls <= m && rs <= r && arr[ls] < arr[rs]){
            tmp[x++] = arr[ls++];
        }

        while(ls <= m && rs <= r && arr[ls] >= arr[rs]){
            tmp[x++] = arr[rs++];
        }
    }

    while(ls <= m){
        tmp[x++] = arr[ls++];
    }

    while(rs <= r){
        tmp[x++] = arr[rs++];
    }

    for(int i = l; i <= r; i++){
        arr[i] = tmp[i-l];
    }

    free(tmp);
}

void merge_sort_imp(int *arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    merge_sort_imp(arr, l, m);
    merge_sort_imp(arr, m + 1, r);
    merge(arr, l, m, r);
}

void merge_sort(int *arr, int n) {
    merge_sort_imp(arr, 0, n - 1);
}

// void* - можно менять данные и менять указатель
// const void* - нельзя менять данные, но можно менять указатель
// void* const - можно менять данны, но нельзя менять указатель
// const void* const - нельзя менять данные и нельзя менять указатель

int main(){
    return 0;
}