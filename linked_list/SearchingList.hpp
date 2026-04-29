#pragma once
#include "LinkedList.hpp"
#include <string>

namespace SearchingList {
    // linear search functions
    void linearSearchAge(const LinkedList& list, int minAge, int maxAge);
    void linearSearchTransport(const LinkedList& list, std::string mode);
    void linearSearchDistance(const LinkedList& list, int threshold);

    // binary search functions
    void binarySearchAge(const LinkedList& list, int minAge, int maxAge);
    void binarySearchTransport(const LinkedList& list, std::string mode);
    void binarySearchDistance(const LinkedList& list, int threshold);

    // helper to print search results
    void printSearchResultTable(const LinkedList& results, double searchTimeMs, size_t memoryUsedBytes);
}
