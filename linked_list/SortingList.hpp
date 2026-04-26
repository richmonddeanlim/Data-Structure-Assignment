#pragma once
#include "LinkedList.hpp"

namespace SortingList {
    // Sorting functions for Linked List
    // These return the time taken in seconds (matching array experiment)
    double sortByAge(LinkedList& list);
    double sortByDistance(LinkedList& list);
    double sortByTransport(LinkedList& list);
}
