#include <stdio.h>
#include <stdlib.h>
#include "linear_select.h"

void usage() {
    printf("usage: linear_lselect input_file k n\n");
    printf("       input_file - file to be sorted, must contain ints ");
    printf("separated by a space\n");
    printf("       k - the kth smallest element to be lselected, must ");
    printf("less than or equal to n\n");
    printf("       n - the number of elements to read from file\n");
}

int main (int argc, char **argv) {
    int n, k;
    FILE *input;

    /* take inputs and read in file */
    if (argc != 4) {
        usage();
        exit(1);
    }
    if (sscanf(argv[3], "%d", &n) == 0 || sscanf(argv[2], "%d", &k) == 0)
    {
        printf("n and k must be integers\n");
        usage();
        exit(1);
    }
    if (n >= 1000000 || n < 1) {
        printf("n must be between 1 and 1,000,000\n");
        usage();
        exit(1);
    }
    if (k < 1 || k > n) {
        printf("k must be between 1 and n\n");
        usage();
        exit(1);
    }
    if (!(input = fopen(argv[1], "r"))) {
        printf("file could not be opened\n");
        usage();
        exit(1);
    }

    int i, arr[n];
    for (i = 0; i < n; i++) {
        if(fscanf(input, "%d", arr + i) == 0) {
            fprintf(stderr,"error reading data\n");
            usage();
            exit(1);
        }
        if(fscanf(input, "%d", arr + i) == EOF) {
            fprintf(stderr,"EOF reached before parsing %d numbers\n",n);
            usage();
            exit(1);
        }
    }

    int result = lselect(arr, 0, n-1, k-1);

    printf("%d\n", arr[result]);

    fclose(input);
}
