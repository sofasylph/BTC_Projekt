#include "Analytics.hpp"
#include <cstring>
#include <cstdlib>

// This function reads lines from the CSV file, parsing date, price, volume, etc.,
// and updates both the DynamicArray (for later sorting/ranking) and the LinkedList
// (for grouping by, say, day-of-year or month).
bool readChunkFile(const char* filename, DynamicArray &prices, LinkedList &groups) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filename);
        return false;
    }

    // Example CSV: date,price,volume
    // e.g. 2023-01-05,16600.32,234567.89

    char line[256];
    bool firstLine = true;
    while (fgets(line, sizeof(line), fp)) {
        if (firstLine) {
            // skip header
            firstLine = false;
            continue;
        }
        PriceRecord record;
        // parse
        // note: be sure to handle CSV commas carefully.
        int matched = sscanf(line, "%10[^,],%f,%f", record.date, &record.price, &record.volume);
        if (matched == 3) {
            // store in dynamic array for sorting
            prices.push_back(record.price);

            // grouping example: let's group by (month + year*12)
            // record.date = "YYYY-MM-DD"
            // parse year, month:
            char yearStr[5];
            char monthStr[3];
            strncpy(yearStr, record.date, 4);
            yearStr[4] = '\0';
            strncpy(monthStr, record.date+5, 2);
            monthStr[2] = '\0';

            int year = atoi(yearStr);
            int month = atoi(monthStr);

            // convert to some integer key
            // e.g. groupKey = (year * 12) + month
            int groupKey = (year * 12) + month;

            groups.addOrUpdate(groupKey, record.price);
        }
    }

    fclose(fp);
    return true;
}

// Example function that prints out average, min, max for each group in LinkedList
void stratifyAndPrint(LinkedList &groups) {
    printf("\nStratification Results:\n");
    GroupNode *cur = groups.head;
    while (cur) {
        float avg = (cur->count > 0) ? (cur->sum / cur->count) : 0.0f;
        printf("GroupKey = %d => Count=%d, Avg=%.2f, Min=%.2f, Max=%.2f\n",
               cur->key, cur->count, avg, cur->minVal, cur->maxVal);
        cur = cur->next;
    }
}