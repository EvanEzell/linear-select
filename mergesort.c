void merge(int arr[], int left, int mid, int right) { 
    int i, j, k, lsize, rsize; 

    /* create subarrays */
    lsize = mid - left + 1; 
    rsize =  right - mid; 
    int Left[lsize], Right[rsize]; 
  
    /* populate subarrays */
    for (i = 0; i < lsize; i++) Left[i] = arr[left + i]; 
    for (j = 0; j < rsize; j++) Right[j] = arr[mid + 1+ j]; 
  
    i = 0;
    j = 0;
    for (k = left; i < lsize && j < rsize; k++)
        if (Left[i] <= Right[j]) { 
            arr[k] = Left[i]; 
            i++; 
        } else { 
            arr[k] = Right[j]; 
            j++; 
        } 
  
    while (i < lsize) { 
        arr[k] = Left[i]; 
        i++; 
        k++; 
    } 
  
    while (j < rsize) { 
        arr[k] = Right[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int arr[], int left, int right) { 
    int mid;
    if (left < right) { 
        mid = left + (right-left)/2; 
  
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid+1, right); 
  
        merge(arr, left, mid, right); 
    } 
} 
