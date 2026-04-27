#include <windows.h>
#include <psapi.h>
#include "SearchingList.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace SearchingList {

    static size_t getMemoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return pmc.PrivateUsage;
        }
        return 0;
    }

    static void printHeader() {
        cout << "\n+-------+-----+---------------+----------+---------+------+------------+\n";
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

    void printSearchResultTable(const LinkedList& results, double searchTimeMs, size_t memoryUsedBytes) {
        int count = 0;
        Node* current = results.getHead();
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        if (count == 0) {
            cout << "\nNo residents found matching the criteria.\n";
            cout << "Search execution time: " << fixed << setprecision(4) << searchTimeMs << " ms\n";
            cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
            return;
        }

        printHeader();
        Node* temp = results.getHead();
        while (temp != nullptr) {
            const Residents& r = temp->data;
            double emission = r.dailyDistance * r.carbonEmissionFactor * r.avgDayPerMonth;
            
            cout << "| "  << left  << setw(5)  << r.residentID
                 << " | " << right << setw(3)  << r.age
                 << " | " << left  << setw(13) << r.modeOfTransport
                 << " | " << right << setw(8)  << r.dailyDistance
                 << " | " << right << setw(7)  << fixed << setprecision(2) << r.carbonEmissionFactor
                 << " | " << right << setw(4)  << r.avgDayPerMonth
                 << " | " << right << setw(10) << fixed << setprecision(2) << emission
                 << " |\n";
            temp = temp->next;
        }
        cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
        cout << "Found " << count << " matches.\n";
        cout << "Search execution time: " << fixed << setprecision(4) << searchTimeMs << " ms\n";
        cout << "Memory consumption   : " << (memoryUsedBytes / 1024.0) << " KB\n";
    }

    void linearSearchAge(const LinkedList& list, int minAge, int maxAge) {
        LinkedList matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.age >= minAge && temp->data.age <= maxAge) matches.addResident(temp->data);
            temp = temp->next;
        }
        
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;
        
        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void linearSearchTransport(const LinkedList& list, string mode) {
        LinkedList matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.modeOfTransport == mode) matches.addResident(temp->data);
            temp = temp->next;
        }
        
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;

        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }

    void linearSearchDistance(const LinkedList& list, int threshold) {
        LinkedList matches;
        size_t memStart = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.dailyDistance > threshold) matches.addResident(temp->data);
            temp = temp->next;
        }
        
        auto end = high_resolution_clock::now();
        size_t memEnd = getMemoryUsage();
        duration<double, milli> elapsed = end - start;

        size_t diff = (memEnd > memStart) ? (memEnd - memStart) : 0;
        printSearchResultTable(matches, elapsed.count(), diff);
    }
}
