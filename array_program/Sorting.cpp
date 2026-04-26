#include "Sorting.hpp"
#include <chrono>

using namespace std::chrono;

namespace Sorting {

    // Sort By Age 
    double sortByAge(ResidentArray& arr) {
        int n = arr.size();
        auto start = high_resolution_clock::now();

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr.get(j).age < arr.get(minIdx).age) minIdx = j;
            }
            arr.swap(i, minIdx);
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Daily Distance
    double sortByDistance(ResidentArray& arr) {
        int n = arr.size();
        auto start = high_resolution_clock::now();

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr.get(j).dailyDistance < arr.get(minIdx).dailyDistance) minIdx = j;
            }
            arr.swap(i, minIdx);
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Carbon Emission
    double sortByEmission(ResidentArray& arr) {
        int n = arr.size();
        auto start = high_resolution_clock::now();

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr.get(j).emission() < arr.get(minIdx).emission()) minIdx = j;
            }
            arr.swap(i, minIdx);
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }
    
    // Sort By Transportation Mode
    double sortByTransport(ResidentArray& arr) {
        int n = arr.size();
        auto start = high_resolution_clock::now();

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr.get(j).modeOfTransport < arr.get(minIdx).modeOfTransport) minIdx = j;
            }
            arr.swap(i, minIdx);
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }
}