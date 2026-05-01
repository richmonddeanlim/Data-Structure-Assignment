#include "SortingList.hpp"
#include "LinkedList.hpp"
#include "Residents.hpp"
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace std::chrono;

namespace SortingList {
    // Helper to get memory usage 
    static size_t getMemoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return pmc.PrivateUsage;
        }
        return 0;
    }

    // Sort By Age
    double sortByAge(LinkedList& list, size_t& memUsed) {
        size_t memBefore = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.age < minNode->data.age) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        size_t memAfter = getMemoryUsage();
        memUsed = (memAfter > memBefore) ? (memAfter - memBefore) : 0;
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Daily Distance
    double sortByDistance(LinkedList& list, size_t& memUsed) {
        size_t memBefore = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.dailyDistance < minNode->data.dailyDistance) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        size_t memAfter = getMemoryUsage();
        memUsed = (memAfter > memBefore) ? (memAfter - memBefore) : 0;
        duration<double> elapsed = end - start; 
        return elapsed.count();
    }

    // Sort By Carbon Emission
    double sortByEmission(LinkedList& list, size_t& memUsed) {
        size_t memBefore = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.emission() < minNode->data.emission()) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        size_t memAfter = getMemoryUsage();
        memUsed = (memAfter > memBefore) ? (memAfter - memBefore) : 0;
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Transportation Mode
    double sortByTransport(LinkedList& list, size_t& memUsed) {
        size_t memBefore = getMemoryUsage();
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.modeOfTransport < minNode->data.modeOfTransport) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        size_t memAfter = getMemoryUsage();
        memUsed = (memAfter > memBefore) ? (memAfter - memBefore) : 0;
        duration<double> elapsed = end - start;
        return elapsed.count();
    }
}
