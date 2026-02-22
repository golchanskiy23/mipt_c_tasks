#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
//#include "u_template.h"
//#include "vector.h"

bool is_prime(int n){
    for(int i = 2; i <= (int)sqrt(n); i++){
        if(n%i == 0){
            return false;
        }
    }
    return true;
}

void prime_number(int n){
    int cnt = 0, curr = 2;
    while(true){
        if(is_prime(curr) == 1){
            cnt++;
            if(cnt == n){
                break;
            }
        }
        curr++;
    }
    printf("%d", curr);
}

void print1(){
    int n;
    scanf("%d", &n);
    prime_number(n);
}

void less_equal_prime_number(int n){
    int* arr = malloc((n+1)* sizeof(int));
    for(int i = 2; i <= n; i++){
        arr[i] = arr[i-1];
        if(is_prime(i) == 1){
            arr[i] += 1;
        }
    }
    printf("%d", arr[n]);
    free(arr);
}

void print2(){
    int n;
    scanf("%d", &n);
    less_equal_prime_number(n);
}

struct point_t {
    int x, y;
};

struct triangle_t {
    struct point_t pts[3];
};

int double_area(struct triangle_t tr){
    return abs((tr.pts[0].x*(tr.pts[1].y-tr.pts[2].y) +
        tr.pts[1].x*(tr.pts[2].y-tr.pts[0].y) +
        tr.pts[2].x*(tr.pts[0].y-tr.pts[1].y)));
}

void print3(){
    int a,b,c,d,e,f;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    struct triangle_t t = {
        {{a,b}, {c,d}, {e,f}}
    };
    printf("%d", double_area(t));
}

struct sieve_t {
    int n;
    char *s;
};

void fill_sieve(struct sieve_t *sv){
    int n = sv->n;
    char* s = sv->s;

    memset(s, 0, n);

    if (n > 0) s[0] = 1;
    if (n > 1) s[1] = 1;

    for(int i = 2; i < n; i++){
        if(s[i] == 0){
            long long start = (long long)i * i;
            if (start >= n) continue;
            for (long long j = start; j < n; j += i){
                s[j] = 1;
            }
        }
    }
}

int nth_prime(struct sieve_t *sv, int N){
    int curr = 0;
    for(int i = 2; i <= sv->n; i++){
        if(sv->s[i] == 0){
            curr++;
        }
        if(curr == N){
            return i;
        }
    }
    return -1;
}

void print4(){
    int n = 100;
    struct sieve_t sv;

    sv.n = n;
    sv.s = (char *)malloc((n + 1) * sizeof(char));
    fill_sieve(&sv);
    printf("%d", nth_prime(&sv, 10));
}

void generating_formulas(int N){
    struct sieve_t sv;
    int n = 1000000;
    sv.n = n;
    sv.s = (char *)malloc((n + 1) * sizeof(char));
    fill_sieve(&sv);

    int max = 0, max_a = 0, max_b = 0;
    // b
    for(int i = 2; i < N; i++){
        if(sv.s[i] == 0){
            // a
            for(int j = -N+1; j <= N-1; j++){
                int k = 0, curr = 0;
                while(true){
                    int tmp = k*k+j*k+i;
                    if(tmp > 0 && sv.s[tmp] == 0){
                        curr++;
                        if(curr > max){
                            max = curr;
                            max_a = j;
                            max_b = i;
                        }
                    } else{
                        break;
                    }
                    k++;
                }
            }
        }
    }
    printf("%d %d %d",max_a, max_b, max);
}

void print5(){
    int N;
    scanf("%d", &N);
    generating_formulas(N);
}

int divide_number(int n, struct sieve_t *sv){
    int num = n, len = 0;
    while(num > 0){
        num /= 10;
        len++;
    }

    int pow10 = 1;
    for(int i = 1; i < len; i++) pow10 *= 10;

    int rotated = n;
    for(int i = 0; i < len; i++){
        if(rotated > sv->n || sv->s[rotated] != 0){
            return 1;
        }
        int last_digit = rotated % 10;
        rotated = (last_digit * pow10) + (rotated / 10);
    }
    return 0;
}

int closest_prime(int n, struct sieve_t* sv){
    int distance = 1000000000, number = 0;
    for(int i = n-1; i >= 0; i--){
        if(divide_number(i, sv) == 0){
            if(n-i < distance){
                distance = n-i;
                number = i;
            }
        }
    }

    for(int i = n+1; i <= 1000000; i++){
        if(divide_number(i, sv) == 0){
            if(i-n < distance){
                distance = i-n;
                number = i;
            }
        }
    }
    return number;
}

void print6(){
    int N;
    scanf("%d", &N);
    struct sieve_t sv;
    int n = 1000000;
    sv.n = n;
    sv.s = (char *)malloc((n + 1) * sizeof(char));
    fill_sieve(&sv);

    printf("%d", closest_prime(N, &sv));
}

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

long long lcm_help(long long a, long long b) {
    return a / gcd(a, b) * b;  // Изменен порядок операций для избежания переполнения
}

long long lcm(int n) {
    long long ans = 1;
    for (int i = 2; i <= n; i++) {
        ans = lcm_help(ans, i);
    }
    return ans;
}

void print7(){
    int n;
    scanf("%d", &n);
    printf("%lld", lcm(n));
}

void high_low_bit(int n){
    if(n == 0){
        printf("NO");
        return;
    }
    int low = 0, high = 0, is_low = 0, cnt = 0;
    while(n > 0){
        int reminder = n%2;
        if(reminder == 1){
            if(is_low == 0){
                is_low = 1;
                low = cnt;
            }
            high = cnt;
        }
        n /= 2;
        cnt++;
    }
    printf("%d %d", high, low);
}

void print8(){
    int n;
    scanf("%d", &n);
    high_low_bit(n);
}

void invert_N_bit(int* arr, int arr_size, int n){
    if(8*arr_size <= n) return;
    int byte_index = n/8;
    int bit_in_byte = n%8;
    arr[byte_index] ^= 1 << bit_in_byte;
}

void print9(){
    int n,N;
    scanf("%d", &n);
    int* arr = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        int tmp;
        scanf("%d", &tmp);
        arr[i] = tmp;
    }
    scanf("%d", &N);
    invert_N_bit(arr, n, N);
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
}

struct bit_sieve_t {
    int n;
    unsigned char* s;
};

int get_composite(struct bit_sieve_t *sv, int x){
    return (sv->s[x/8] >> (x%8)) & 1;
}

void set_composite(struct bit_sieve_t *sv, int x){
    sv->s[x/8] |= (1<<(x%8));
}

void fill_bit_sieve(struct bit_sieve_t *sv){
    int max_num = sv->n*8;
    
    if(sv->n > 0) set_composite(sv, 0);
    if(sv->n > 1) set_composite(sv, 1);

    for(int i = 2; i*i < max_num; i++){
        if(get_composite(sv, i) == 0){
            for(int j = i*i; j < max_num; j += i){
                set_composite(sv, j);
            }
        }
    }
}

int is_bit_prime(struct bit_sieve_t *sv, unsigned n){
    return get_composite(sv, n) == 0;
}

typedef unsigned long long ull;

ull mod_pow(ull a, ull b, ull mod) {
    ull result = 1;
    a = a % mod;
    while (b > 0) {
        if (b & 1)
            result = (__uint128_t)result * a % mod;
        a = (__uint128_t)a * a % mod;
        b >>= 1;
    }
    return result;
}

int fermat_test(ull p, int k) {
    if (p < 4)
        return (p == 2 || p == 3);
    for (int i = 0; i < k; i++) {
        ull a = 2 + rand() % (p - 3);
        if (mod_pow(a, p - 1, p) != 1)
            return 0;
    }
    return 1;
}

void print12(){
    ull p;
    scanf("%llu", &p);
    srand(time(NULL));
    printf("%d\n", fermat_test(p, 5));
}

static inline ull mod_mul(ull a, ull b, ull mod) {
    return (ull)((__uint128_t)a * b % mod);
}

int is_prime_miller_rabin(ull n){
    if (n < 2) return 0;
    if (n < 4) return 1;
    if (n % 2 == 0) return 0;

    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    static const ull bases[] = {
        2ULL, 325ULL, 9375ULL, 28178ULL,
        450775ULL, 9780504ULL, 1795265022ULL
    };

    for (int i = 0; i < 7; i++) {
        ull a = bases[i];
        if (a % n == 0) continue;

        ull x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        int composite = 1;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = 0;
                break;
            }
        }
        if (composite == 1) return 0;
    }
    return 1;
}

ull closest_prime_fibonacci(ull k, ull n){
    ull a = 0, b = 1, best = 0;
    while(b < mod_pow(2,60,10000000000000000000)){
        if(is_prime_miller_rabin(b) == 1){
            best = b;
        }
        ull next = n*a+k*b;
        a = b;
        b = next;
    }

    return best;
}

void print13(){
    ull n,k;
    scanf("%llu %llu", &n, &k);
    printf("%llu", closest_prime_fibonacci(n,k));
}

int main(){
    print13();
    return 0;
}