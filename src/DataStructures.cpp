#include "DataStructures.hpp"

// -------------------------
// DynamicArray definitions
// -------------------------

void DynamicArray::init(int initialCap) {
    if (initialCap <= 0) initialCap = 10;
    data = (float*)malloc(sizeof(float) * initialCap);
    if (!data) {
        printf("Memory allocation error\n");
        // Handle error or exit
    }
    size = 0;
    capacity = initialCap;
}

void DynamicArray::push_back(float value) {
    // Check if we need to resize
    if (size == capacity) {
        int newCap = capacity * 2;
        float* newData = (float*)realloc(data, sizeof(float) * newCap);
        if (!newData) {
            printf("Memory reallocation error\n");
            // Handle error or exit
        }
        data = newData;
        capacity = newCap;
    }
    data[size] = value;
    size++;
}

void DynamicArray::cleanup() {
    if (data) {
        free(data);
        data = nullptr;
    }
    size = 0;
    capacity = 0;
}

// -------------------------
// LinkedList definitions
// -------------------------

void LinkedList::init() {
    head = nullptr;
}

// Add or update a node with the given groupKey
// For example, groupKey might be "dayIndex" or "monthIndex"
void LinkedList::addOrUpdate(int groupKey, float value) {
    GroupNode *current = head;
    GroupNode *prev = nullptr;

    // Search for the groupKey
    while (current) {
        if (current->key == groupKey) {
            // Update existing node
            current->sum += value;
            current->count += 1;
            if (value < current->minVal) current->minVal = value;
            if (value > current->maxVal) current->maxVal = value;
            return;
        }
        prev = current;
        current = current->next;
    }

    // Not found, create a new node
    GroupNode *newNode = (GroupNode*)malloc(sizeof(GroupNode));
    if (!newNode) {
        printf("Memory allocation failed in addOrUpdate\n");
        return;
    }
    newNode->sum = value;
    newNode->count = 1;
    newNode->minVal = value;
    newNode->maxVal = value;
    newNode->key = groupKey;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
    } else {
        prev->next = newNode;
    }
}

void LinkedList::cleanup() {
    GroupNode *current = head;
    while (current) {
        GroupNode *temp = current;
        current = current->next;
        free(temp);
    }
    head = nullptr;
}