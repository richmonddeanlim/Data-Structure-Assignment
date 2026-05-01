#pragma once
#include "LinkedList.hpp"
#include "Residents.hpp"

namespace SortingList {
    // Sorting functions for Linked List
    double sortByAge(LinkedList& list);
    double sortByDistance(LinkedList& list);
    double sortByEmission(LinkedList& list);
    double sortByTransport(LinkedList& list);
}
