#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <utils.h>

/**
 * Gets a line of input from stdin character by character.
 * A line is a sequence of characters ending with \n which is discarded.
 * @returns a pointer to the string representing a line of input
 */
char* get_line_by_char(){
    int buff_size = 0;
    char *buff = NULL;
    char c;
    int i = 0;
    /* read from input until \n is encountered */
    while((c = fgetc(stdin)) != '\n'){
        if(i == buff_size){
            if (buff_size != 0)
                buff_size = buff_size * 2;
            else buff_size = 1;
            buff = realloc(buff, buff_size);
        }
        buff[i] = c;
        ++i;
    }
    if(i == buff_size)
        buff = realloc(buff, buff_size + 1);
    buff[i] = '\0';
    return buff;
    /* The object return most likely has a tail of allocated memory after \0 which if necessary can be removed. */
}

char* get_line(){
    int buff_size = 256;
    char *buff = (char *)malloc(buff_size * sizeof(char));
    int line_length = 0;    //no of characters read
    char *cursor = buff;    //current position in buffer
    bool stop = false;
    //fills buffer buff and extends it if current buffer is full
    while(!stop){
        /* reads at most buff_size characters from stdin until stream empty and waits for more */
        if(buff_size == line_length + 1){
            buff_size = buff_size * 2;
            buff = (char *)realloc(buff, buff_size * sizeof(char));
        }
        fgets(cursor, buff_size - line_length, stdin);
        line_length = strlen(buff);
        //printf("Line length: %d\n", line_length);
        cursor = buff + line_length; //check \0
        // if buffer is about to overflow realloc
        // printf("%s\n", buff);
        /* if buffer contains \n stop */
        //printf("%c\n", buff[line_length - 1]);
        if(strchr(buff, '\n'))  //might be quicker to check buff[line_length - 1]
            stop = true;
    }
    //should the buffer be allocated to reflect the exact length of the string?
    return(buff);
}

int read_int(char *buff){
    return strtol(buff, NULL, 10);
}

/*
 * Reads n integers into an array from a string.
 * @param n: number of integers to be read from buffer
 * @param buff: space separated integers
 * @param data: array[int]
 * @returns number of read integers or 0 if unsuccessful
 */
int read_n_ints(int n, char* buff, int *data){
    int cnt = 0;
    char *tok = strtok(buff, " ");
    do {
        data[cnt] = strtol(tok, NULL, 10);
        tok = strtok(NULL, " ");
        ++cnt;
    } while(tok != NULL);
    return cnt;
}

void print_matrix(int rows, int cols, int **arr){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j)
            //TODO alignement
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

void print_array(int n, int *arr){
    for(int i = 0; i < n; ++i){
        //TODO alignement
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * Searches for the smallest element in an array of integers (O(n))
 * @param arr pointer to the beginning
 * @param n number of elements in the array
 * @returns the index of the first min element
 */
int min_array(int n, int *arr){
    int min_index = 0;
    int min_int = INT_MAX;
    for(int i = 0; i < n; ++i){
        if(arr[i] < min_int){ 
            min_index = i;
            min_int = arr[i];
        }
    }
    return min_index;
}

/*
 * Generates an array of n integers in the interval [min_val, max_val].
 */
int *generate_array(int n, int min_val, int max_val){
    int *arr = (int *)malloc(n * sizeof(int));
    
    srand(time(NULL));
    srand(rand());
    //srand(2);    

    for(int i = 0; i < n; ++i)
        arr[i] = rand() % (max_val - min_val + 1) + min_val;
    return arr;
}

int index_of(int *elem, int n, int *arr){
    int index = elem - arr;
    if(index < n) return index;
    return -1;
}
