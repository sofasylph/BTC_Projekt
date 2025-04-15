#include "Sorting.hpp"

static void merge(float* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    float* L = new float[n1];
    float* R = new float[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

void mergeSort(float* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

static void swapVals(float* arr, int i, int j) {
    float temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Classic Lomuto partition
static int partition(float* arr, int left, int right) {
    float pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapVals(arr, i, j);
        }
    }
    swapVals(arr, i+1, right);
    return i+1;
}

void quickSort(float* arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSort(arr, left, pi-1);
        quickSort(arr, pi+1, right);
    }
}