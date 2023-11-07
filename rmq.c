#include <math.h>
#include <stdlib.h>
#include <rmq.h>
#include <bt.h>
#include <utils.h>

/*
 * Sparse Table algorithm
 * "Lowest Common Ancestors in Trees and Directed Acyclic Graphs"
 * (with further enhancements)
 * @param i: starting index of RMQ (range minimum query)
 * @param j: 2^j is length of interval starting at index i
 * @param a: array of integers subject to RMQs
 * @param n: number of elements in a
 * @param b: result of ST alg, precomputed results for RMQ
 */
int ST(int i, int j, int *a, int n, int **b){
    if(i >= n) return -1;
    if(b[i][j] >= 0) return b[i][j];
    if(j == 0){
        b[i][j] = i;
        return b[i][j];
    }
    //b[i][j] = b[i][j-1] < b[i + 2^(j-1)][j-1] ? b[i][j-1] : b[i + 2^(j-1)][j-1]
    int left_idx = ST(i, j - 1, a, n, b);
    int right_idx = ST(i + (int)pow(2, j - 1), j - 1, a, n, b);
    if(i + pow(2, j) > n) return -1;
    int left = a[left_idx];
    int right = a[right_idx];
    b[i][j] = ((left <= right) ? left_idx : right_idx);
    return b[i][j];
}

/*
 * Sparse Table Algorithm preprocessing the array.
 * Recursive O(nlgn)
 * @param a: pointer to an array of integers to do the RMQ on
 * @param n: number of elements in the array pointed to by a
 * @returns: n x ceil(lgn) array of integers b
 *           b[i][j] is arg min RMQ(i, i + 2^j)
 */
//TODO How about an iterative version?
//TODO cont It takes a long time
int **RMQ_ST(int *a, int n){
    //longest necessary interval length is 2^(up-1)
    int up = (int)ceil(log2(n));
    int **b = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; ++i)
        b[i] = (int *)malloc(up * sizeof(int));
    //initialize b with -1
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < up; ++j)
            b[i][j] = -1;
    }
    for(int i = 0; i < n; ++i)
        ST(i, up - 1, a, n, b);
    return b;
}

/*
 * Range minimum query
 * @param i, j: boundaries
 * @param a: pointer to an array of integers to do the RMQ on
 * @param n: number of elements in the array pointed to by a
 * @param b: result of ST alg, precomputed results for RMQ
 */
int RMQ(int i, int j, int *a, int n, int **b){
    int len = (int)floor(log2(j - i + 1));
    int pow_len = (int)pow(2, len);
    int min_left = b[i][len];
    int min_right = b[j - pow_len + 1][len];
    return a[min_left] <= a[min_right] ? min_left : min_right;
}

int RMQ_linear(int *a, int n, int i, int j){
    return i + min_array(j - i + 1, a + i);
}
