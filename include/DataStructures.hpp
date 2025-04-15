#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <cstdio>   // for FILE*, printf
#include <cstring>  // for strcpy, strcmp, etc.
#include <cstdlib>  // for malloc, free

// A simple dynamic array to store float or int data
// without using <vector> or <string>.
struct DynamicArray {
    float *data;    // pointer to array of floats
    int size;       // current number of elements
    int capacity;   // allocated capacity

    // Constructor-like function to init
    void init(int initialCap);

    // Append a float value
    void push_back(float value);

    // Free memory
    void cleanup();
};

// A node in a singly-linked list for grouping/stratification
struct GroupNode {
    float sum;
    int count;
    float minVal;
    float maxVal;

    // For example, store a "key" as an integer day or month
    int key;    

    GroupNode *next;
};

struct LinkedList {
    GroupNode *head;

    void init();
    void addOrUpdate(int groupKey, float value);
    void cleanup();
};

#endif // DATA_STRUCTURES_HPP