#include <windows.h>
#include <psapi.h>
#include "Searching.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace Searching {

    static size_t getMemoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return pmc.PrivateUsage;
        }
        return 0;
    }

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

    void printSearchResultTable(const ResidentArray& results, double timeTakenMs, size_t memoryUsedBytes) {
        if (results.size() == 0) {
            cout << "\nNo residents found matching the criteria.\n";
            cout << "Search execution time: " << fixed << setprecision(4) << timeTakenMs << " ms\n";
            cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
            return;
        }

        printHeader();
        for (int i = 0; i < results.size(); i++) {
            const Resident& r = results.get(i);
            cout << "| "  << left  << setw(5)  << r.residentID
                 << " | " << right << setw(3)  << r.age
                 << " | " << left  << setw(13) << r.modeOfTransport
                 << " | " << right << setw(8)  << r.dailyDistance
                 << " | " << right << setw(7)  << fixed << setprecision(2) << r.carbonEmissionFactor
                 << " | " << right << setw(4)  << r.avgDayPerMonth
                 << " | " << right << setw(10) << fixed << setprecision(2) << r.emission()
                 << " |\n";
        }
        cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
        cout << "Found " << results.size() << " matches.\n";
        cout << "Search execution time: " << fixed << setprecision(4) << timeTakenMs << " ms\n";
        cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
    }

    void linearSearchAge(const ResidentArray& arr, int minAge, int maxAge) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.age >= minAge && r.age <= maxAge) matches.add(r);
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void linearSearchTransport(const ResidentArray& arr, string mode) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.modeOfTransport == mode) matches.add(r);
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void linearSearchDistance(const ResidentArray& arr, int threshold) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        for (int i = 0; i < arr.size(); i++) {
            const Resident& r = arr.get(i);
            if (r.dailyDistance > threshold) matches.add(r);
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void binarySearchAge(const ResidentArray& arr, int minAge, int maxAge) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        int low = 0, high = arr.size() - 1, startIndex = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).age >= minAge) { startIndex = mid; high = mid - 1; }
            else { low = mid + 1; }
        }
        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                if (arr.get(i).age > maxAge) break;
                matches.add(arr.get(i));
            }
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void binarySearchTransport(const ResidentArray& arr, string mode) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        int low = 0, high = arr.size() - 1, startIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).modeOfTransport >= mode) {
                if (arr.get(mid).modeOfTransport == mode) startIndex = mid;
                high = mid - 1;
            } else { low = mid + 1; }
        }

        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                if (arr.get(i).modeOfTransport != mode) break;
                matches.add(arr.get(i));
            }
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void binarySearchDistance(const ResidentArray& arr, int threshold) {
        ResidentArray matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        int low = 0, high = arr.size() - 1, startIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr.get(mid).dailyDistance > threshold) {
                startIndex = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (startIndex != -1) {
            for (int i = startIndex; i < arr.size(); i++) {
                matches.add(arr.get(i));
            }
        }
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }
}
