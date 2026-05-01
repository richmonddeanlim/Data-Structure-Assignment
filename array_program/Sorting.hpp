#pragma once
#include "ResidentArray.hpp"

namespace Sorting {
    // Sorting functions for Array
    double sortByAge(ResidentArray& arr, size_t& memUsed);
    double sortByDistance(ResidentArray& arr, size_t& memUsed);
    double sortByEmission(ResidentArray& arr, size_t& memUsed);
    double sortByTransport(ResidentArray& arr, size_t& memUsed); 
}
