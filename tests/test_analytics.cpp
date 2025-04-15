#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/Analytics.hpp"
#include "../include/DataStructures.hpp"

/**
 * test_analytics.cpp
 *
 * Purpose:
 *   - Tests the functions from Analytics.cpp, such as CSV reading and grouping.
 *   - Since reading an actual CSV might be large, we create a small synthetic CSV file on the fly,
 *     parse it, and confirm results.
 */

// Helper to create a small test CSV.
static const char* TEST_CSV_NAME = "small_test.csv";

static void createSmallTestCSV() {
    FILE* fp = fopen(TEST_CSV_NAME, "w");
    if (!fp) {
        printf("[ERROR] Unable to create test CSV: %s\n", TEST_CSV_NAME);
        return;
    }
    // Write a simple header + rows
    fprintf(fp, "date,price,volume\n");
    fprintf(fp, "2023-01-01,100.50,5000.0\n");
    fprintf(fp, "2023-01-01,101.75,3000.0\n");
    fprintf(fp, "2023-02-01,200.00,10000.0\n");
    fclose(fp);
}

int main() {
    printf("=== Running test_analytics ===\n");

    // 1. Create a small CSV
    createSmallTestCSV();

    // 2. Prepare data structures
    DynamicArray prices;
    prices.init(10);

    LinkedList groups;
    groups.init();

    // 3. Read the CSV
    bool ok = readChunkFile(TEST_CSV_NAME, prices, groups);
    if (!ok) {
        printf("[ERROR] readChunkFile returned false\n");
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Expected results:
    // - We have 3 price values in `prices`: [100.50, 101.75, 200.00]
    // - We have two group keys: for 2023-01 => (2023*12 + 1)
    //   and for 2023-02 => (2023*12 + 2)
    if (prices.size != 3) {
        printf("[ERROR] Expected 3 prices, got %d\n", prices.size);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Check the 2 groups
    int groupCount = 0;
    GroupNode* cur = groups.head;
    while (cur) {
        groupCount++;
        cur = cur->next;
    }
    if (groupCount != 2) {
        printf("[ERROR] Expected 2 groups, found %d\n", groupCount);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Let's see if the sums are correct
    // For 2023-01 => key = 2023*12 + 1 = 24277
    // For 2023-02 => key = 2023*12 + 2 = 24278
    // Summaries:
    //   Jan group: sum=202.25, count=2, min=100.5, max=101.75
    //   Feb group: sum=200.0, count=1, min=max=200.0

    GroupNode* node = groups.head;
    GroupNode* janNode = nullptr;
    GroupNode* febNode = nullptr;

    while (node) {
        if (node->key == 24277) {
            janNode = node;
        } else if (node->key == 24278) {
            febNode = node;
        }
        node = node->next;
    }

    if (!janNode || !febNode) {
        printf("[ERROR] Could not find january or february node in grouping.\n");
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Check january
    if (janNode->count != 2) {
        printf("[ERROR] January node expected count=2, got %d\n", janNode->count);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }
    if (janNode->sum < 202.24f || janNode->sum > 202.26f) {
        printf("[ERROR] January node sum=%.2f, expected ~202.25\n", janNode->sum);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }
    if (janNode->minVal != 100.50f) {
        printf("[ERROR] January node minVal=%.2f, expected 100.50\n", janNode->minVal);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }
    if (janNode->maxVal != 101.75f) {
        printf("[ERROR] January node maxVal=%.2f, expected 101.75\n", janNode->maxVal);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Check february
    if (febNode->count != 1) {
        printf("[ERROR] February node expected count=1, got %d\n", febNode->count);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }
    if (febNode->sum != 200.0f) {
        printf("[ERROR] February node sum=%.2f, expected 200.0\n", febNode->sum);
        prices.cleanup();
        groups.cleanup();
        return 1;
    }

    // Everything okay
    prices.cleanup();
    groups.cleanup();

    printf("test_analytics: CSV reading & grouping test PASSED.\n");
    printf("=== test_analytics: ALL TESTS PASSED ===\n");
    return 0;
}