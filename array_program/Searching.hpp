#pragma once
#include "ResidentArray.hpp"
#include <string>

namespace Searching {
    // Linear Search Functions
    void linearSearchAge(const ResidentArray& arr, int minAge, int maxAge);
    void linearSearchTransport(const ResidentArray& arr, std::string mode);
    void linearSearchDistance(const ResidentArray& arr, int threshold);

    // Binary Search Functions
    void binarySearchAge(const ResidentArray& arr, int minAge, int maxAge);
    void binarySearchTransport(const ResidentArray& arr, std::string mode);
    void binarySearchDistance(const ResidentArray& arr, int threshold);

    // Helper to print search results
    void printSearchResultTable(const ResidentArray& results, double timeTakenMs, size_t memoryUsedBytes);
}
