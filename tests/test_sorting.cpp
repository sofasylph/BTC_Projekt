#include <cstdio>
#include <cstdlib>
#include "../include/Sorting.hpp"

/**
 * test_sorting.cpp
 *
 * Purpose:
 *   - Tests the quickSort and mergeSort implementations on small arrays
 *     and verifies correct ordering.
 */

static bool isSorted(const float* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

static void printArray(const float* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("=== Running test_sorting ===\n");

    // Test quickSort
    {
        float data1[] = {3.5f, 1.2f, 7.8f, 2.0f, 0.5f};
        int size1 = sizeof(data1) / sizeof(data1[0]);

        quickSort(data1, 0, size1 - 1);

        if (!isSorted(data1, size1)) {
            printf("[ERROR] quickSort failed to sort array.\n");
            printf("Result array: ");
            printArray(data1, size1);
            return 1;
        }
        printf("quickSort basic test passed.\n");
    }

    // Test mergeSort
    {
        float data2[] = {10.0f, -1.0f, 5.2f, 5.1f, 5.0f, 5.3f};
        int size2 = sizeof(data2) / sizeof(data2[0]);

        mergeSort(data2, 0, size2 - 1);

        if (!isSorted(data2, size2)) {
            printf("[ERROR] mergeSort failed to sort array.\n");
            printf("Result array: ");
            printArray(data2, size2);
            return 1;
        }
        printf("mergeSort basic test passed.\n");
    }

    // Test quickSort on an already sorted array
    {
        float data3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        int size3 = sizeof(data3) / sizeof(data3[0]);
        quickSort(data3, 0, size3 - 1);
        if (!isSorted(data3, size3)) {
            printf("[ERROR] quickSort sorted array incorrectly.\n");
            return 1;
        }
        printf("quickSort already-sorted array test passed.\n");
    }

    // Test mergeSort on reverse array
    {
        float data4[] = {9.0f, 8.0f, 7.0f, 6.0f, 5.0f};
        int size4 = sizeof(data4) / sizeof(data4[0]);
        mergeSort(data4, 0, size4 - 1);
        if (!isSorted(data4, size4)) {
            printf("[ERROR] mergeSort reverse array incorrectly.\n");
            return 1;
        }
        printf("mergeSort reverse array test passed.\n");
    }

    printf("=== test_sorting: ALL TESTS PASSED ===\n");
    return 0;
}