#include <stdio.h>
#include <stdlib.h>
#include "linear_select.h"

void usage() {
    fprintf(stderr,"usage: linear_lselect input_file k n\n");
    fprintf(stderr,"       input_file - file to be sorted, must contain ints ");
    fprintf(stderr,"separated by a space\n");
    fprintf(stderr,"       k - the kth smallest element to be lselected, must ");
    fprintf(stderr,"less than or equal to n\n");
    fprintf(stderr,"       n - the number of elements to read from file\n");
}

int main (int argc, char **argv) {
    int n, k, result;
    FILE *input;

    /* take inputs and read in file */
    if (argc != 4) {
        usage();
        exit(1);
    }
    if (sscanf(argv[3], "%d", &n) == 0 || sscanf(argv[2], "%d", &k) == 0) {
        fprintf(stderr,"n and k must be integers\n");
        usage();
        exit(1);
    }
    if (n >= 1000000 || n < 1) {
        fprintf(stderr,"n must be between 1 and 1,000,000\n");
        usage();
        exit(1);
    }
    if (k < 1 || k > n) {
        fprintf(stderr,"k must be between 1 and n\n");
        usage();
        exit(1);
    }
    if (!(input = fopen(argv[1], "r"))) {
        fprintf(stderr,"file could not be opened\n");
        usage();
        exit(1);
    }

    int i, arr[n], ret;
    for (i = 0; i < n; i++) {
        if((ret = fscanf(input, "%d", arr + i)) == 0) {
            fprintf(stderr,"Error reading data. Only ints permitted\n");
            usage();
            exit(1);
        }
        if(ret == EOF) {
            fprintf(stderr,"EOF reached before reading %d numbers\n",n);
            usage();
            exit(1);
        }
    }

    result = lselect(arr, 0, n-1, k-1);
    printf("%d\n", arr[result]);

    fclose(input);
}
