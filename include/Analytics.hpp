#ifndef ANALYTICS_HPP
#define ANALYTICS_HPP

#include <cstdio>
#include "DataStructures.hpp"

// Example record structure for a CSV row
struct PriceRecord {
    char date[11]; // e.g. "YYYY-MM-DD"
    float price;
    float volume;
};

// Functions to parse CSV chunks, do grouping, ranking, etc.
bool readChunkFile(const char* filename, DynamicArray &prices, LinkedList &groups);

// Additional "stratify" or "quantile" function
void stratifyAndPrint(LinkedList &groups);

#endif // ANALYTICS_HPP