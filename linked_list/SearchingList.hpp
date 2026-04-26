#pragma once
#include "LinkedList.hpp"
#include <string>

namespace SearchingList {
    // Linear Search Functions (O(n))
    void linearSearchAge(const LinkedList& list, int minAge, int maxAge);
    void linearSearchTransport(const LinkedList& list, std::string mode);
    void linearSearchDistance(const LinkedList& list, int threshold);

    // Binary Search Functions (O(n) on LL, but logically O(log n))
    // These assume the list is already sorted by the respective field.
    void binarySearchAge(const LinkedList& list, int minAge, int maxAge);
    void binarySearchTransport(const LinkedList& list, std::string mode);
    void binarySearchDistance(const LinkedList& list, int threshold);

    // Helper to print search results in a formatted table
    void printSearchResultTable(const LinkedList& results, double searchTimeMs);
}
