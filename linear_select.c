#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

void usage() {
    printf("usage: linear_lselect input_file k n\n");
    printf("       input_file - file to be sorted, must contain ints ");
    printf("separated by a space\n");
    printf("       k - the kth smallest element to be lselected, must ");
    printf("less than or equal to n\n");
    printf("       n - the number of elements to read from file\n");
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* three-way partition, return new index of pivot */
int partition(int *arr, int left, int right, int pivot) {
    int i;
    i = left - 1;

    swap(&arr[pivot],&arr[right]);

    for (; left < right; left++)
        if (arr[left] < arr[right])
            swap(&arr[++i],&arr[left]);
    swap(&arr[right],&arr[i+1]);

    return i+1;
}

/* insertion sort and return index of median */
int partition5(int *arr, int left, int right) {
    int i, j;
    i = left + 1;
    while (i <= right) {
        j = i;
        while (j > left && arr[j-1] > arr[j]) {
            swap(&arr[j-1],&arr[j]);
            j = j - 1;
        }
        i = i + 1;
    }

    return floor((left+right)/2);
}

/* find the kth order statistic */
int lselect(int *arr, int left, int right, int k) {
    int pivotIndex;

    for (;;) {
        if (right - left <= 50) {
            mergeSort(arr, left, right);
            return k;
        }

        pivotIndex = pivot(arr, left, right);
        pivotIndex = partition(arr, left, right, pivotIndex);
        int i;
        if (k < pivotIndex)
            right = pivotIndex - 1;
        else if (k > pivotIndex)
            left = pivotIndex + 1;
        else
            return k;
    }
}

/* find the median of medians */
int pivot(int *arr, int left, int right) {
    if (right - left < 5)
        return partition5(arr, left, right);

    int i, subRight, median5, mid;
    for (i = left; i < right; i += 5) {
        subRight = i + 4; 
        if (subRight > right) subRight = right;
        median5 = partition5(arr, i, subRight);
        swap(&arr[median5],&arr[left + (int)floor((i-left)/5)]);
    }

    mid = (right - left) / 10 + left + 1;
    return lselect(arr, left, left + (int)floor((right-left)/5), mid);
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
            printf("error reading data\n");
            usage();
            exit(1);
        }
    }

    int result = lselect(arr, 0, n-1, k-1);

    printf("%d\n", arr[result]);

    fclose(input);
}
