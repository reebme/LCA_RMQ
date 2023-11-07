#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <bt.h>
#include <utils.h>
#include <rmq.h>

int main(void){
    // Generate an array for RMQ
    const long int n = 10000000;
    const int min_val = 1;
    const int max_val = INT_MAX;
    int *A = generate_array(n, min_val, max_val);
    //print_array(n, A);

    clock_t start, end;
    double cpu_time;
    
    //RMQ precalculation
    start = clock();
    int **b = RMQ_ST(A, n); 
    end = clock();
    cpu_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Preprocess time: %f\n", cpu_time);
    //print_matrix(n, (int)ceil(log2(n)), b);
    
    //RMQ calculation with measuring time
    int i = 1;
    int j = n-2;

    start = clock();
    for(int i = 0; i < 1000; ++i)
        RMQ(i, j, A, n, b);
    end = clock();
    cpu_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed: %f\n", cpu_time);
    printf("%d\n", RMQ(i, j, A, n, b));
    
    start = clock();
    for(int i = 0; i < 1000; ++i)
        RMQ_linear(A, n, i, j);
    end = clock();
    cpu_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time elapsed: %f\n", cpu_time);
    printf("%d\n", RMQ_linear(A, n, i, j));
/* 
    //array of pointers to node in the tree correspondint to the ith element in array A
    node *point_to_ctree[n];
    //Cartesian Tree from array A
    node *cart_root = arr_to_cart_with_depth(A, A, n, 0, (node **) point_to_ctree);
    print_ptr_to_ctree_array(point_to_ctree, n);
    inorder_with_depth(cart_root);

    //Euler tour from the Cartesian Tree
    int *et = euler_tour_with_depth(cart_root, n);
    int et_size = 2 * (n-1) + 1;
    print_array(et_size, et);
*/
}
