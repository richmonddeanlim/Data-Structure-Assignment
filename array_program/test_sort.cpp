#include <iostream>
#include <iomanip>
#include "ResidentArray.hpp"
#include "CSVLoader.hpp"
#include "Sorting.hpp"

using namespace std;

void displayPreview(ResidentArray& arr, string attribute) {
    cout << left << setw(8)  << "No." 
         << setw(10) << "Age" 
         << setw(15) << "Distance" 
         << "Emission" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    int n = arr.size();

    for (int i = 0; i < 25 && i < n; i++) {
        cout << left << setw(8)  << (i + 1)
             << setw(10) << arr.get(i).age 
             << setw(15) << (to_string(arr.get(i).dailyDistance) + " km")
             << fixed << setprecision(2) << arr.get(i).emission() << " kg" << endl;
    }

    cout << "  ... [ Middle " << (n - 20) << " rows hidden ] ..." << endl;

    for (int i = n - 25; i < n; i++) {
        if (i < 0) continue; 
        cout << left << setw(8)  << (i + 1)
             << setw(10) << arr.get(i).age 
             << setw(15) << (to_string(arr.get(i).dailyDistance) + " km")
             << fixed << setprecision(2) << arr.get(i).emission() << " kg" << endl;
    }
    cout << "---------------------------------------------------------------------------\n" << endl;
}

int main() {

    const string pathA = "../dataset/dataset1-cityA.csv";
    const string pathB = "../dataset/dataset2-cityB.csv";
    const string pathC = "../dataset/dataset3-cityC.csv";

    ResidentArray residents;

    cout << "Loading datasets..." << endl;
    CSVLoader::loadAll(pathA, pathB, pathC, residents);
    cout << "Total records loaded: " << residents.size() << "\n" << endl;

    if (residents.size() == 0) {
        cout << "ERROR: No data loaded. Check your CSV paths!" << endl;
        return 1;
    }

    cout << "--- TEST 1: Sorting by AGE (Smallest to Largest) ---" << endl;
    double timeAge = Sorting::sortByAge(residents);
    displayPreview(residents, "Age");
    cout << "Time taken: " << fixed << setprecision(6) << timeAge << " seconds\n" << endl;

    cout << "--- TEST 2: Sorting by DISTANCE (Shortest to Longest) ---" << endl;
    double timeDist = Sorting::sortByDistance(residents);
    displayPreview(residents, "Distance");
    cout << "Time taken: " << fixed << setprecision(6) << timeDist << " seconds\n" << endl;

    cout << "--- TEST 3: Sorting by EMISSION (Cleanest to Most Polluting) ---" << endl;
    double timeEmit = Sorting::sortByEmission(residents);
    displayPreview(residents, "Emission");
    cout << "Time taken: " << fixed << setprecision(6) << timeEmit << " seconds\n" << endl;

    cout << "All sorting tests complete. Use these times for Task 8 of your report!" << endl;

    return 0;
}