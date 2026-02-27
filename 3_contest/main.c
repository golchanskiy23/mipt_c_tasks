#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

typedef unsigned long long ull;

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

void qsort_impl(int *arr, unsigned low, unsigned high) {
    if (low >= high) return;
    unsigned pi = partition(arr, low, high);
    if (pi > low) qsort_impl(arr, low, pi - 1);
    qsort_impl(arr, pi + 1, high);
}
  
void quick_sort(int *arr, unsigned len) { qsort_impl(arr, 0u, len - 1); }

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

void multiplication_of_polynomials(){
    int n,m,curr = 0;
    scanf("%d %d",&n,&m);
    int first[n], second[m], total[n+m-1];
    memset(total,0,sizeof(total));
    for(int i = 0; i < n; i++){scanf("%d",&first[i]);}
    for(int i = 0; i < m; i++){scanf("%d",&second[i]);}

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            total[i+j] += (first[i]*second[j]);
        }
    }

    int real_len = n+m-1;
    while (real_len > 1 && total[real_len - 1] == 0) {
        real_len--;
    }

    for(int i = 0; i < real_len; i++){
        printf("%d",total[i]);
        if(i < real_len){
            printf(" ");
        }
    }
}

ull pow_of_two(ull n){
    ull curr = 1;
    while(curr < n){
        curr *= 2;
    }
    return curr;
}

void karatsuba_helper(ull *a, ull *b, ull *c, int n) {
    if (n <= 64) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                c[i + j] += a[i] * b[j];
            }
        }
        return;
    }
    
    int k = n / 2;
    ull l[k], r[k];
    ull t[2 * k];
    memset(t, 0, sizeof(t));
    
    for (int i = 0; i < k; i++) {
        l[i] = a[i] + a[k + i];
        r[i] = b[i] + b[k + i];
    }
    karatsuba_helper(l, r, t, k);
    karatsuba_helper(a, b, c, k);
    karatsuba_helper(a + k, b + k, c + n, k);
    ull *t1 = t, *t2 = t + k;
    ull *s1 = c, *s2 = c + k, *s3 = c + 2 * k, *s4 = c + 3 * k;
    for (int i = 0; i < k; i++) {
        ull c1 = s2[i] + t1[i] - s1[i] - s3[i];
        ull c2 = s3[i] + t2[i] - s2[i] - s4[i];
        c[k + i] = c1;
        c[n + i] = c2;
    }
}

void karatsuba() {
    ull n, m;
    scanf("%llu %llu", &n, &m);
    
    ull size = pow_of_two((n > m) ? n : m);
    ull first[size], second[size], total[2 * size];
    
    memset(first, 0, sizeof(first));
    memset(second, 0, sizeof(second));
    memset(total, 0, sizeof(total));
    
    for (ull i = 0; i < n; i++) {
        scanf("%llu", &first[i]);
    }
    for (ull i = 0; i < m; i++) {
        scanf("%llu", &second[i]);
    }
    
    karatsuba_helper(first, second, total, size);
    
    ull real_len = n + m - 1;
    while (real_len > 1 && total[real_len - 1] == 0) {
        real_len--;
    }
    
    for (ull i = 0; i < real_len; i++) {
        printf("%llu", total[i]);
        if (i < real_len - 1) {
            printf(" ");
        }
    }
}

int majority_element(const int *parr, int len){
    int count = 0, candidate = 0;
    for(int i = 0; i < len; i++){
        if(count == 0){
            candidate = parr[i];
            count++;
        } else{
            if(candidate == parr[i]){count++;} 
            else{count--;}
        }
    }
    count = 0;
    for(int i = 0; i < len; i++){
        if(parr[i] == candidate) count++;
    }
    if(count <= len/2) return -1;
    return candidate;
}

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

typedef struct{
    unsigned char* ptr;
    int size;
} Element;

void generic_merge(Element* a, int left,int mid, int right, xcmp_t cmp){
    int n = right-left;
    Element* result = malloc(n*sizeof(Element));

    int i = left, j = mid, k = 0;
    while(i < mid && j < right){
        if (cmp(a[i].ptr, a[i].size, a[j].ptr, a[j].size) <= 0){
            result[k++] = a[i++];
        } else {
            result[k++] = a[j++];
        }
    }
  
    while(i < mid){
        result[k++] = a[i++];
    }
  
    while(j < right){
        result[k++] = a[j++];
    }
  
    for(i = left; i < right; i++){
        a[i] = result[i-left];
    }
    free(result);
}

void generic_merge_sort(void* mem, int left, int right, xcmp_t cmp){
    int mid = left+(right-left)/2;
    if(left+1 >= right) return;
    generic_merge_sort(mem,left,mid,cmp);
    generic_merge_sort(mem,mid,right,cmp);
    generic_merge(mem,left,mid,right,cmp);
}

// Здесь mem это начало памяти, sizes это массив размеров, nelts - число элементов
// обобщёенная сортировка слиянием разных размеров
void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp)
{
    Element *arr = malloc(nelts * sizeof(Element));

    unsigned char *p = mem;
    for (int i = 0; i < nelts; i++) {
        arr[i].ptr  = p;
        arr[i].size = sizes[i];
        p += sizes[i];
    }

    generic_merge_sort(arr, 0, nelts, cmp);

    int total_size = 0;
    for (int i = 0; i < nelts; i++)
        total_size += arr[i].size;

    unsigned char *buffer = malloc(total_size);
    unsigned char *dst = buffer;

    for (int i = 0; i < nelts; i++) {
        memcpy(dst, arr[i].ptr, arr[i].size);
        arr[i].ptr = dst;
        dst += arr[i].size;
    }

    memcpy(mem, buffer, total_size);

    free(buffer);
    free(arr);
}

void counting_sort(const int* parr, int n){
    int* arr = malloc(100001*sizeof(int));
    int the_biggest = 0;
    for(int i = 0; i < n; i++){
        if(parr[i] > the_biggest){the_biggest = parr[i];}
        arr[parr[i]]++;
    }
    for(int i = 0; i <= the_biggest; i++){
        printf("%d",arr[i]);
        if(i < the_biggest){
            printf(" ");
        }
    }
    free(arr);
}

void radix(int* arr, int n, int exp){
    int count[10];
    int output[n];
    memset(count,0,10*sizeof(int));
    for(int i = 0;i < n; i++) count[(arr[i]/exp)%10]++;
    for(int i = 1; i < 10; i++) count[i] += count[i-1];
    for(int i = n-1; i >= 0; i--){
        int idx = (arr[i]/exp)%10;
        output[--count[idx]] = arr[i];
    }
    memcpy(arr,output,n*sizeof(int));
    for(int i = 0; i < n; i++){
        printf("%d",arr[i]);
        if(i < n-1){printf(" ");}
    }
}

/*void identity_matrix(unsigned A[N][N]){
    memset(A, 0, sizeof(unsigned)*N*N);
    for(int i = 0; i < N; i++){
        A[i][i] = 1;
    }
}

void matrix_multiply(unsigned res[N][N], unsigned a[N][N], unsigned b[N][N], unsigned m){
    unsigned tmp[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            __uint128_t sum = 0;
            for(int k = 0; k < N; k++){
                sum = (sum+(a[i][k]*b[k][j])%m)%m;
            }
            tmp[i][j] = (unsigned)(sum%m);
        }
    }

    memcpy(res, tmp, sizeof(unsigned)*N*N);
}

void powNxN (unsigned (*A)[N], unsigned k, unsigned m){
    unsigned result[N][N];
    unsigned base[N][N];
    identity_matrix(result);
    memcpy(base,A,sizeof(unsigned)*N*N);
    while(k > 0){
        if(k%2 == 1){
            matrix_multiply(result, result, base, m);
        }
        matrix_multiply(base, base, base, m);
        k /= 2;
    }

    memcpy(A, result, sizeof(unsigned)*N*N);
}*/

void TimSort(void){
    int N, K, X, runs = 0, pos = 0;
    scanf("%d %d %d", &N, &K, &X);
    int *cur = malloc(sizeof(int) * N);
    int *tmp = malloc(sizeof(int) * N);
    int *src = cur;
    int *dst = tmp;
    int *run_starts = malloc(sizeof(int) * (N));
    int *run_lens   = malloc(sizeof(int) * (N));

    long long total = (long long)N * K;
    int *rec = malloc(sizeof(int) * total);

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < K; ++j){
            scanf("%d", &rec[i*K + j]);
        }
    }
    
    for(int i = 0; i < N; ++i) cur[i] = i;

    #define KEY_BY_IDX(idx) (rec[(idx)*K + X])

    while(pos < N){
        int start = pos;
        if(pos + 1 == N){
            pos++;
            run_starts[runs] = start;
            run_lens[runs] = 1;
            runs++;
            break;
        }
        if(KEY_BY_IDX(cur[pos]) <= KEY_BY_IDX(cur[pos+1])){
            pos++;
            while(pos + 1 < N && KEY_BY_IDX(cur[pos]) <= KEY_BY_IDX(cur[pos+1])) pos++;
            int len = pos - start + 1;
            run_starts[runs] = start;
            run_lens[runs] = len;
            runs++;
            pos++;
        } else {
            pos++;
            while(pos + 1 < N && KEY_BY_IDX(cur[pos]) > KEY_BY_IDX(cur[pos+1])) pos++;
            int end = pos;
            int i = start, j = end;
            while(i < j){
                int t = cur[i]; cur[i] = cur[j]; cur[j] = t;
                i++; j--;
            }
            int len = end - start + 1;
            run_starts[runs] = start;
            run_lens[runs] = len;
            runs++;
            pos++;
        }
    }

    while(runs > 1){
        int new_runs = 0;
        int write_pos = 0;

        for(int r = 0; r < runs; r += 2){
            if(r + 1 >= runs){
                int s = run_starts[r];
                int len = run_lens[r];
                for(int i = 0; i < len; ++i) dst[write_pos + i] = src[s + i];
                run_starts[new_runs] = write_pos;
                run_lens[new_runs] = len;
                write_pos += len;
                new_runs++;
            } else {
                int s1 = run_starts[r], l1 = run_lens[r];
                int s2 = run_starts[r+1], l2 = run_lens[r+1];
                int i1 = s1, i2 = s2;
                int end1 = s1 + l1, end2 = s2 + l2;
                int out = write_pos;
                while(i1 < end1 && i2 < end2){
                    int a = src[i1], b = src[i2];
                    int ka = KEY_BY_IDX(a), kb = KEY_BY_IDX(b);
                    if(ka <= kb){
                        dst[out++] = a;
                        i1++;
                    } else {
                        dst[out++] = b;
                        i2++;
                    }
                }
                while(i1 < end1) dst[out++] = src[i1++];
                while(i2 < end2) dst[out++] = src[i2++];
                run_starts[new_runs] = write_pos;
                run_lens[new_runs] = l1 + l2;
                write_pos += l1 + l2;
                new_runs++;
            }
        }

        int *tmp_ptr = src; 
        src = dst; 
        dst = tmp_ptr;
        runs = new_runs;
    }

    for(int i = 0; i < N; ++i){
        int idx = src[i];
        int field_index = i % N;
        if(field_index >= K) field_index %= K;
        int val = rec[idx*K + field_index];
        if(i) putchar(' ');
        printf("%d", val);
    }
    putchar('\n');

    free(rec);
    free(cur); free(tmp);
    free(run_starts); free(run_lens);
}

int main() {
    TimSort();
    return 0;
}