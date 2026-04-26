#include "ResidentArray.hpp"
#include "CSVLoader.hpp"
#include "Searching.hpp"
#include <iostream>

using namespace std;

// Helper to sort by Mode (Alphabetical)
void sortByMode(ResidentArray& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr.get(j).modeOfTransport > arr.get(j + 1).modeOfTransport) {
                arr.swap(j, j + 1);
            }
        }
    }
}

// Helper to sort by Distance (Numerical)
void sortByDistance(ResidentArray& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr.get(j).dailyDistance > arr.get(j + 1).dailyDistance) {
                arr.swap(j, j + 1);
            }
        }
    }
}

int main() {
    const string pathA = "../dataset/dataset1-cityA.csv";
    const string pathB = "../dataset/dataset2-cityB.csv";
    const string pathC = "../dataset/dataset3-cityC.csv";

    ResidentArray residents;

    cout << "Loading datasets for testing...\n";
    CSVLoader::loadAll(pathA, pathB, pathC, residents);
    cout << "Total residents loaded: " << residents.size() << "\n\n";

    cout << "--- TEST 1: Binary Search for Transport (Bicycle) ---\n";
    cout << "Sorting by Transport Mode...\n";
    sortByMode(residents);
    Searching::binarySearchTransport(residents, "Bicycle");
    cout << "\n";

    cout << "--- TEST 2: Binary Search for Distance (> 20km) ---\n";
    cout << "Sorting by Distance...\n";
    sortByDistance(residents);
    Searching::binarySearchDistance(residents, 20);
    cout << "\n";

    return 0;
}
