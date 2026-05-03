#pragma once
#include "LinkedList.hpp"
#include "Residents.hpp"

namespace SortingList {
    // Sorting functions for Linked List
    double sortByAge(LinkedList& list, size_t& memUsed, bool isAllCities = false);
    double sortByDistance(LinkedList& list, size_t& memUsed, bool isAllCities = false);
    double sortByEmission(LinkedList& list, size_t& memUsed, bool isAllCities = false);
    double sortByTransport(LinkedList& list, size_t& memUsed, bool isAllCities = false);
}
