#include <cstdio>
#include <cstdlib>
#include "DataStructures.hpp"
#include "Sorting.hpp"
#include "Analytics.hpp"

int main() {
    // 1. Initialize structures
    DynamicArray prices;
    prices.init(1000000); // an initial guess for capacity

    LinkedList groups;
    groups.init();

    // 2. Process each chunk
    const char* files[] = {
        "data/chunk_0.csv",
        "data/chunk_1.csv",
        "data/chunk_2.csv",
        "data/chunk_3.csv",
        "data/chunk_4.csv",
        "data/chunk_5.csv",
        "data/chunk_6.csv"
    };

    int numFiles = sizeof(files) / sizeof(files[0]);
    for (int i = 0; i < numFiles; i++) {
        printf("Reading %s ...\n", files[i]);
        readChunkFile(files[i], prices, groups);
    }

    // 3. Sort the entire prices array to do a "ranking" by price
    // For demonstration, we use quickSort
    printf("Sorting all price data...\n");
    quickSort(prices.data, 0, prices.size - 1);

    // 4. Print out top 5 prices
    printf("Top 5 prices:\n");
    for (int i = prices.size - 1; i >= 0 && i >= prices.size - 5; i--) {
        printf("%.2f\n", prices.data[i]);
    }

    // 5. Show stratification results
    stratifyAndPrint(groups);

    // 6. Cleanup
    prices.cleanup();
    groups.cleanup();
    return 0;
}