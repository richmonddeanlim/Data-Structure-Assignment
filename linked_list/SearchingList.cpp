#include "SearchingList.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace SearchingList {

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

    void printSearchResultTable(const LinkedList& results, double searchTimeMs) {
        int count = 0;
        Node* current = results.getHead();
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        if (count == 0) {
            cout << "\nNo residents found matching the criteria.\n";
            cout << "Search execution time: " << fixed << setprecision(4) << searchTimeMs << " ms\n";
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
    }

    // Helpers
    static Node* getNodeAt(Node* head, int index) {
        Node* curr = head;
        for (int i = 0; i < index && curr != nullptr; i++) curr = curr->next;
        return curr;
    }

    static int getCount(Node* head) {
        int count = 0;
        while (head != nullptr) { count++; head = head->next; }
        return count;
    }

    // --- Linear Searches ---
    void linearSearchAge(const LinkedList& list, int minAge, int maxAge) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.age >= minAge && temp->data.age <= maxAge) matches.addResident(temp->data);
            temp = temp->next;
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }

    void linearSearchTransport(const LinkedList& list, string mode) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.modeOfTransport == mode) matches.addResident(temp->data);
            temp = temp->next;
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }

    void linearSearchDistance(const LinkedList& list, int threshold) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        Node* temp = list.getHead();
        while (temp != nullptr) {
            if (temp->data.dailyDistance > threshold) matches.addResident(temp->data);
            temp = temp->next;
        }
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }

    // --- Binary Searches ---
    void binarySearchAge(const LinkedList& list, int minAge, int maxAge) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        
        int count = getCount(list.getHead());
        int low = 0, high = count - 1, startIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            Node* midNode = getNodeAt(list.getHead(), mid);
            if (midNode->data.age >= minAge) { startIndex = mid; high = mid - 1; }
            else { low = mid + 1; }
        }

        if (startIndex != -1) {
            Node* curr = getNodeAt(list.getHead(), startIndex);
            while (curr != nullptr && curr->data.age <= maxAge) {
                matches.addResident(curr->data);
                curr = curr->next;
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }

    void binarySearchTransport(const LinkedList& list, string mode) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        
        int count = getCount(list.getHead());
        int low = 0, high = count - 1, startIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            Node* midNode = getNodeAt(list.getHead(), mid);
            if (midNode->data.modeOfTransport >= mode) {
                if (midNode->data.modeOfTransport == mode) startIndex = mid;
                high = mid - 1;
            } else { low = mid + 1; }
        }

        if (startIndex != -1) {
            Node* curr = getNodeAt(list.getHead(), startIndex);
            while (curr != nullptr && curr->data.modeOfTransport == mode) {
                matches.addResident(curr->data);
                curr = curr->next;
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }

    void binarySearchDistance(const LinkedList& list, int threshold) {
        LinkedList matches;
        auto start = high_resolution_clock::now();
        
        int count = getCount(list.getHead());
        int low = 0, high = count - 1, startIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            Node* midNode = getNodeAt(list.getHead(), mid);
            if (midNode->data.dailyDistance > threshold) { startIndex = mid; high = mid - 1; }
            else { low = mid + 1; }
        }

        if (startIndex != -1) {
            Node* curr = getNodeAt(list.getHead(), startIndex);
            while (curr != nullptr) {
                matches.addResident(curr->data);
                curr = curr->next;
            }
        }

        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        printSearchResultTable(matches, elapsed.count());
    }
}
