#include "SortingList.hpp"
#include "LinkedList.hpp"
#include "Residents.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;
using namespace std::chrono;

namespace SortingList {
    // Sort By Age
    double sortByAge(LinkedList& list, size_t& memUsed, bool isAllCities) {
        auto start = high_resolution_clock::now();
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.age < minNode->data.age) minNode = j;
            }
            if (minNode != i) swap(i->data, minNode->data);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        memUsed = list.totalMemoryBytes();
        duration<double, milli> elapsed_ms = elapsed;
        cout << "\n[Performance]\n";
        cout << "Execution Time: " << fixed << setprecision(4) << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";
        return elapsed.count();
    }

    // Sort By Daily Distance
    double sortByDistance(LinkedList& list, size_t& memUsed, bool isAllCities) {
        auto start = high_resolution_clock::now();
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.dailyDistance < minNode->data.dailyDistance) minNode = j;
            }
            if (minNode != i) swap(i->data, minNode->data);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        memUsed = list.totalMemoryBytes();
        duration<double, milli> elapsed_ms = elapsed;
        cout << "\n[Performance]\n";
        cout << "Execution Time: " << fixed << setprecision(4) << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";
        return elapsed.count();
    }

    // Sort By Carbon Emission
    double sortByEmission(LinkedList& list, size_t& memUsed, bool isAllCities) {
        auto start = high_resolution_clock::now();
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.emission() < minNode->data.emission()) minNode = j;
            }
            if (minNode != i) swap(i->data, minNode->data);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        memUsed = list.totalMemoryBytes();
        duration<double, milli> elapsed_ms = elapsed;
        cout << "\n[Performance]\n";
        cout << "Execution Time: " << fixed << setprecision(4) << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";
        return elapsed.count();
    }

    // Sort By Transportation Mode
    double sortByTransport(LinkedList& list, size_t& memUsed, bool isAllCities) {
        auto start = high_resolution_clock::now();
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.modeOfTransport < minNode->data.modeOfTransport) minNode = j;
            }
            if (minNode != i) swap(i->data, minNode->data);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        memUsed = list.totalMemoryBytes();
        duration<double, milli> elapsed_ms = elapsed;
        cout << "\n[Performance]\n";
        cout << "Execution Time: " << fixed << setprecision(4) << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";
        return elapsed.count();
    }
}
