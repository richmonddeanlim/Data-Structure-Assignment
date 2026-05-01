#pragma once
#include "LinkedList.hpp"
#include "Residents.hpp"

namespace SortingList {
    // Sorting functions for Linked List
    double sortByAge(LinkedList& list, size_t& memUsed);
    double sortByDistance(LinkedList& list, size_t& memUsed);
    double sortByEmission(LinkedList& list, size_t& memUsed);
    double sortByTransport(LinkedList& list, size_t& memUsed);
}
