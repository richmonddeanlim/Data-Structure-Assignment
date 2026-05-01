#include "Searching.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace Searching {

    static void printHeader() {
        cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
        cout << "| "  << left  << setw(5)  << "ID"
             << " | " << right << setw(3)  << "Age"
             << " | " << left  << setw(13) << "Mode"
             << " | " << right << setw(8)  << "Dist(km)"
             << " | " << right << setw(7)  << "Factor"
             << " | " << right << setw(4)  << "Days"
             << " | " << right << setw(10) << "Emission"
             << " |\n";
        cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
    }

    // print the search results 
    void printSearchResultTable(const ResidentArray& results, double timeTakenMs, size_t memoryUsedBytes) {
        
        // checking if the array got something
        if (results.size() == 0) {
            cout << "\nNo residents found matching the criteria.\n";
            cout << "Search execution time: " << fixed << setprecision(4) << timeTakenMs << " ms\n";
            cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
            return;
        }

        // print the header of the table and loop the array content
        printHeader();
        for (int i = 0; i < results.size(); i++) {
            const Resident& r = results.get(i);
            cout << "| "  << left  << setw(5)  << r.residentID
                 << " | " << right << setw(3)  << r.age
                 << " | " << left  << setw(13) << r.modeOfTransport
                 << " | " << right << setw(8)  << r.dailyDistance
                 << " | " << right << setw(7)  << fixed << setprecision(2) << r.co2Factor
                 << " | " << right << setw(4)  << r.averageDayPerMonth
                 << " | " << right << setw(10) << fixed << setprecision(2) << r.emission()
                 << " |\n";
        }
        cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
        cout << "Found " << results.size() << " matches.\n";
        cout << "Search execution time: " << fixed << setprecision(4) << timeTakenMs << " ms\n";
        cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
    }

    // linear search age
    void linearSearchAge(const ResidentArray& arr, int minAge, int maxAge) {
        ResidentArray matches;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.age >= minAge && r.age <= maxAge){
                matches.add(r);
            }    
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }

    // linear search transport
    void linearSearchTransport(const ResidentArray& arr, string mode) {
        ResidentArray matches;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.modeOfTransport == mode) matches.add(r);
        }
        
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }

    //  linear search distance
    void linearSearchDistance(const ResidentArray& arr, int threshold) {
        ResidentArray matches;

        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.dailyDistance > threshold) matches.add(r);
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }

    // binary search age
    void binarySearchAge(const ResidentArray& arr, int minAge, int maxAge) {
        ResidentArray matches;

        auto start = high_resolution_clock::now();

        // binary search to find the starting index of the age range
        int low = 0, high = arr.size() - 1, startIndex = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).age >= minAge) { 
                startIndex = mid; high = mid - 1; 
            }

            else { 
                low = mid + 1; 
            }
        }

        // if a starting index is found, iterate from there until we exceed the max age
        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                if (arr.get(i).age > maxAge) {
                    break;
                }
                matches.add(arr.get(i));
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }

    // binary search transport
    void binarySearchTransport(const ResidentArray& arr, string mode) {
        ResidentArray matches;

        auto start = high_resolution_clock::now();

        int low = 0, high = arr.size() - 1, startIndex = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).modeOfTransport >= mode) {
                if (arr.get(mid).modeOfTransport == mode) {
                    startIndex = mid;
                    high = mid - 1;
                }
            } 

            else { 
                low = mid + 1; 
            }
        }

        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                if (arr.get(i).modeOfTransport != mode) {
                    break;
                }
                matches.add(arr.get(i));
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }

    // binary search distance
    void binarySearchDistance(const ResidentArray& arr, int threshold) {   
        ResidentArray matches;

        auto start = high_resolution_clock::now();

        int low = 0, high = arr.size() - 1, startIndex = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).dailyDistance > threshold) {
                startIndex = mid;
                high = mid - 1;
            }

            else {
                low = mid + 1;
            }
        }

        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                matches.add(arr.get(i));
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;

        size_t exactMemoryBytes = matches.totalMemoryBytes();
        printSearchResultTable(matches, elapsed.count(), exactMemoryBytes);
    }
}
