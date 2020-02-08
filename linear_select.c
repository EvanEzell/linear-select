#include <math.h>
#include "mergesort.h"

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* three-way partition, return new index of pivot */
int partition(int arr[], int left, int right, int pivot) {
    int i;

    swap(&arr[pivot],&arr[right]);

    for (i = left-1; left < right; left++)
        if (arr[left] < arr[right])
            swap(&arr[++i],&arr[left]);

    swap(&arr[right],&arr[++i]);

    return i;
}

/* insertion sort and return index of median */
int insertion(int arr[], int left, int right) {
    int i, j;

    for (i = left+1; i <= right; i++) {
        j = i;
        while (j > left && arr[j-1] > arr[j]) {
            swap(&arr[j-1],&arr[j]);
            j--;
        }
    }

    return floor((left+right)/2);
}

/* find the kth order statistic */
int lselect(int arr[], int left, int right, int k) {
    int i, pivotIndex;

    for (;;) {
        if (right - left <= 50) {
            mergeSort(arr, left, right);
            return k;
        }

        pivotIndex = pivot(arr, left, right);
        pivotIndex = partition(arr, left, right, pivotIndex);
        if (k < pivotIndex)
            right = pivotIndex - 1;
        else if (k > pivotIndex)
            left = pivotIndex + 1;
        else
            return k;
    }
}

/* find the median of medians */
int pivot(int arr[], int left, int right) {
    if (right - left < 5)
        return insertion(arr, left, right);

    int i, subRight, median, mid;
    for (i = left; i < right; i += 5) {
        if ((subRight = i + 4) > right)
            subRight = right;
        median = insertion(arr, i, subRight);
        swap(&arr[median],&arr[left + (int)floor((i-left)/5)]);
    }

    mid = (right - left) / 10 + left + 1;
    return lselect(arr, left, left + (int)floor((right-left)/5), mid);
}
