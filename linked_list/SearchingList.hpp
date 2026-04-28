#pragma once
#include "LinkedList.hpp"
#include <string>

namespace SearchingList {
    // Linear Search Functions (O(n))
    void linearSearchAge(const LinkedList& list, int minAge, int maxAge);
    void linearSearchTransport(const LinkedList& list, std::string mode);
    void linearSearchDistance(const LinkedList& list, int threshold);

    // Binary Search Functions
    // Note: These simulate O(log n) logic but are O(n) in practice on a Linked List
    void binarySearchAge(const LinkedList& list, int minAge, int maxAge);
    void binarySearchTransport(const LinkedList& list, std::string mode);
    void binarySearchDistance(const LinkedList& list, int threshold);

    // Helper to print search results in a formatted table
    void printSearchResultTable(const LinkedList& results, double searchTimeMs, size_t memoryUsedBytes);
}
