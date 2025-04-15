#include <cstdio>
#include <cstdlib>
#include "../include/DataStructures.hpp"

/**
 * test_structures.cpp
 *
 * Purpose:
 *   - Tests the DynamicArray and LinkedList data structures.
 *   - Confirms correct memory expansion, insertion, updates, etc.
 */

int main() {
    printf("=== Running test_structures ===\n");

    // -------------------------
    // 1. Test DynamicArray
    // -------------------------
    {
        DynamicArray arr;
        arr.init(2);

        // Insert data
        arr.push_back(1.5f);
        arr.push_back(2.5f);
        arr.push_back(3.5f);  // triggers a resize if initial capacity was 2

        // Check size
        if (arr.size != 3) {
            printf("[ERROR] Expected arr.size = 3, got %d\n", arr.size);
            arr.cleanup();
            return 1;
        }

        // Check actual contents
        if (arr.data[0] != 1.5f || arr.data[1] != 2.5f || arr.data[2] != 3.5f) {
            printf("[ERROR] DynamicArray contents mismatch!\n");
            for (int i = 0; i < arr.size; i++) {
                printf("arr[%d] = %.2f\n", i, arr.data[i]);
            }
            arr.cleanup();
            return 1;
        }

        arr.cleanup();
        printf("DynamicArray tests passed.\n");
    }

    // -------------------------
    // 2. Test LinkedList
    // -------------------------
    {
        LinkedList lst;
        lst.init();

        // We'll treat key=10 and key=11 as different groups
        lst.addOrUpdate(10, 2.0f);
        lst.addOrUpdate(10, 4.0f); // same key => should update the existing node
        lst.addOrUpdate(11, 5.0f); // different key => new node

        // Traverse to see what we have
        // We expect two nodes: one with key=10 (sum=6.0, count=2)
        // and one with key=11 (sum=5.0, count=1)
        GroupNode *headNode = lst.head;
        if (!headNode) {
            printf("[ERROR] LinkedList has no head after insertion.\n");
            lst.cleanup();
            return 1;
        }

        // Check node #1
        if (headNode->key != 10) {
            printf("[ERROR] Expected first node key=10, got %d\n", headNode->key);
            lst.cleanup();
            return 1;
        }
        if (headNode->sum != 6.0f) {
            printf("[ERROR] For key=10, expected sum=6.0, got %.2f\n", headNode->sum);
            lst.cleanup();
            return 1;
        }
        if (headNode->count != 2) {
            printf("[ERROR] For key=10, expected count=2, got %d\n", headNode->count);
            lst.cleanup();
            return 1;
        }

        // Check min/max
        if (headNode->minVal != 2.0f || headNode->maxVal != 4.0f) {
            printf("[ERROR] For key=10, min=%.2f, max=%.2f, expected 2.00/4.00\n",
                   headNode->minVal, headNode->maxVal);
            lst.cleanup();
            return 1;
        }

        // Check node #2
        GroupNode *secondNode = headNode->next;
        if (!secondNode) {
            printf("[ERROR] Expected a second node, but got NULL.\n");
            lst.cleanup();
            return 1;
        }
        if (secondNode->key != 11) {
            printf("[ERROR] For second node, expected key=11, got %d\n", secondNode->key);
            lst.cleanup();
            return 1;
        }
        if (secondNode->sum != 5.0f || secondNode->count != 1) {
            printf("[ERROR] For key=11, expected sum=5.0 and count=1. Got sum=%.2f, count=%d\n",
                   secondNode->sum, secondNode->count);
            lst.cleanup();
            return 1;
        }
        if (secondNode->minVal != 5.0f || secondNode->maxVal != 5.0f) {
            printf("[ERROR] For key=11, min=%.2f, max=%.2f, expected 5.0/5.0\n",
                   secondNode->minVal, secondNode->maxVal);
            lst.cleanup();
            return 1;
        }

        // Ensure no further nodes
        if (secondNode->next != nullptr) {
            printf("[ERROR] Unexpected extra node in LinkedList.\n");
            lst.cleanup();
            return 1;
        }

        // Cleanup
        lst.cleanup();
        printf("LinkedList tests passed.\n");
    }

    printf("=== test_structures: ALL TESTS PASSED ===\n");
    return 0;
}