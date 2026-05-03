#include "ResidentArray.hpp"
#include "CSVLoader.hpp"
#include "Searching.hpp"
#include "Sorting.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#ifndef NOMINMAX
#define NOMINMAX
#endif
using namespace std;

static void printSeparator() {
    cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
}

//draw the table of the resident array
static void printTable(const ResidentArray& arr, int limit = -1) {
    int total = arr.size();
    int shown = (limit < 0 || limit > total) ? total : limit;

    printSeparator();
    cout << "| "  << left  << setw(5)  << "ID"
         << " | " << right << setw(3)  << "Age"
         << " | " << left  << setw(13) << "Mode"
         << " | " << right << setw(8)  << "Dist(km)"
         << " | " << right << setw(7)  << "Factor"
         << " | " << right << setw(4)  << "Days"
         << " | " << right << setw(10) << "Emission"
         << " |\n";
    printSeparator();

    for (int i = 0; i < shown; i++) {
        const Resident& r = arr.get(i);
        cout << "| "  << left  << setw(5)  << r.residentID
             << " | " << right << setw(3)  << r.age
             << " | " << left  << setw(13) << r.modeOfTransport
             << " | " << right << setw(8)  << r.dailyDistance
             << " | " << right << setw(7)  << fixed << setprecision(2) << r.co2Factor
             << " | " << right << setw(4)  << r.averageDayPerMonth
             << " | " << right << setw(10) << fixed << setprecision(2) << r.emission()
             << " |\n";
    }
    printSeparator();
    cout << "  Showing " << shown << " of " << total << " residents.\n";
}

//Showing array status and memory usage stats
static void printStatus(const ResidentArray& arr) {
    int n   = arr.size();
    int cap = arr.getCapacity();
 
    size_t perResident = sizeof(Resident);
    size_t structSize     = sizeof(arr);
    size_t used        = arr.dataSizeBytes();
    size_t allocated       = arr.allocatedBytes();
    size_t wasted      = arr.wastedBytes();
    size_t total       = arr.totalMemoryBytes();
    double fill        = (cap == 0) ? 0.0 : (100.0 * n / cap);
 
    cout << "\n------------------ Array Status ------------------\n";
    cout << "  Residents stored   : " << n << "\n";
    cout << "  Slots allocated    : " << cap << "\n";
    cout << "  Fill ratio         : " << fixed << setprecision(2) << fill << " %\n";
    cout << "  Bytes per resident : " << perResident << "\n";
    cout << "  Array object size  : " << structSize << "\n";
    cout << "\n";
    cout << "  Used memory        : " << used   << " bytes ("
         << fixed << setprecision(2) << used   / 1024.0 << " KB)\n";
    cout << "  Total allocated    : " << allocated  << " bytes ("
         << fixed << setprecision(2) << allocated  / 1024.0 << " KB)\n";
    cout << "  Wasted (unused)    : " << wasted << " bytes ("
         << fixed << setprecision(2) << wasted / 1024.0 << " KB)\n";
    cout << "  Grand total        : " << total  << " bytes ("
         << fixed << setprecision(2) << total  / 1024.0 << " KB)\n";
    cout << "--------------------------------------------------\n";
}

static void searchMenu(ResidentArray& residents) {
    int dataState, algorithm, criteria;

    cout << "\n  Search Resident    " << endl;
    cout << "====================\n";
    cout << "Select Data State:" << endl;
    cout << "1. Unsorted Data" << endl;
    cout << "2. Sorted Data" << endl;
    cout << "3. Back" << endl;
    cout << "Choice: ";
    
    if (!(cin >> dataState) || dataState == 3) {
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Returning to menu." << endl;
        }
        return;
    }

    if (dataState == 1) {
        cout << "\nSelect Algorithm:" << endl;
        cout << "1. Linear Search" << endl;
        cout << "Choice: ";

        if (!(cin >> algorithm)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Returning to menu." << endl;
            return;
        }

        if (algorithm != 1) {
            cout << "Invalid choice for unsorted data. Defaulting to Linear Search." << endl;
            algorithm = 1;
        }
    } 

    else if (dataState == 2) {
        cout << "\nSelect Algorithm:" << endl;
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cout << "Choice: ";

        if (!(cin >> algorithm)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Returning to menu." << endl;
            return;
        }

        if (algorithm < 1 || algorithm > 2) {
            cout << "Invalid choice. Defaulting to Linear Search." << endl;
            algorithm = 1;
        }
    }

    else {
        cout << "Invalid selection. Returning to menu." << endl;
        return;
    }

    cout << "\nSelect Criteria:" << endl;
    cout << "1. Age Range" << endl;
    cout << "2. Mode of Transport" << endl;
    cout << "3. Distance Threshold" << endl;
    cout << "Choice: ";
    if (!(cin >> criteria)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Returning to menu." << endl;
        return;
    }

    // Trigger Sorting if "Sorted Data" is selected
    if (dataState == 2) {
        double sortTime = 0;
        size_t memused = 0;

        if (criteria == 1){
            sortTime = Sorting::sortByAge(residents, memused);
        }

        else if (criteria == 2) {
            sortTime = Sorting::sortByTransport(residents, memused);
        }

        else if (criteria == 3) {
            sortTime = Sorting::sortByDistance(residents, memused);
        }
       
        else {
            cout << "Invalid criteria for sorting. Returning." << endl;
            return;
        }

        cout << "Selection Sort completed in " << fixed << setprecision(6) << sortTime << " seconds." << endl;
        cout << "Memory used: " << memused << " bytes" << endl;
    }

    // Execute Search
    if (criteria == 1) {
        int minAge, maxAge;
        while (true) {
            cout << "Enter min age: "; 
            if (!(cin >> minAge)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
                continue;
            }
            cout << "Enter max age: "; 
            if (!(cin >> maxAge)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
                continue;
            }

            else if (minAge > maxAge) {
                cout << "Error: Min age cannot be greater than max age. Please try again." << endl;
            } 
            
            else if (minAge < 0 || maxAge < 0) {
                cout << "Error: Age cannot be negative. Please try again." << endl;
            } 
            
            else {
                break;
            }
        }

        if (algorithm == 1) {
            Searching::linearSearchAge(residents, minAge, maxAge);
        }

        else {
            Searching::binarySearchAge(residents, minAge, maxAge);
        }
    }

    else if (criteria == 2) {
        string mode;
        cout << "Enter mode of transport: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, mode);

        if (mode == "Bicycle" || mode == "Bus" || mode == "Car" || mode == "Carpool" || mode == "School Bus" || mode == "Walking") {
            if (algorithm == 1){
                Searching::linearSearchTransport(residents, mode);
            }

            else {
                Searching::binarySearchTransport(residents, mode);
            }
        }

        else {
            cout << "Invalid mode of transport. (Note: Case-sensitive, e.g., 'Car', 'School Bus')" << endl;
        }

        cin.putback('\n');
    }

    else if (criteria == 3) {
        int threshold;
        while (true) {
            cout << "Enter distance threshold: "; 
            if (!(cin >> threshold)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
            } 
            
            else if (threshold < 0) {
                cout << "Error: Threshold cannot be negative." << endl;
            } 
            
            else {
                break;
            }
        }

        if (algorithm == 1){
            Searching::linearSearchDistance(residents, threshold);
        }

        else {
            Searching::binarySearchDistance(residents, threshold);
        }
    }}

static void sortMenu(ResidentArray& residents) {
    int criteria;

    cout << "\n   Sort Residents   " << endl;
    cout << "-------------------------\n";
    cout << "Select Criteria:" << endl;
    cout << "1. Age" << endl;
    cout << "2. Carbon Emission" << endl;
    cout << "3. Daily Distance" << endl;
    cout << "4. Back" << endl;
    cout << "Choice: ";
    cin >> criteria;

    if (criteria == 4) return;

    double sortTime = 0;
    size_t memused = 0;
    bool sorted = true;
    if (criteria == 1) sortTime = Sorting::sortByAge(residents, memused);
    else if (criteria == 2) sortTime = Sorting::sortByEmission(residents, memused);
    else if (criteria == 3) sortTime = Sorting::sortByDistance(residents, memused);
    
    if (sorted) {
        cout << "\n--- Sorted Results---\n";
        printTable(residents, -1); 
    } else {
        cout << "Invalid criteria selected.\n";
    }
}

static void printMenu() {
    cout << "\n==========================================\n";
    cout << "  Carbon Emission Analysis System (Array)  \n";
    cout << "==========================================\n";
    cout << "  1. Show array status\n";
    cout << "  2. Display first 20 residents\n";
    cout << "  3. Display ALL residents\n";
    cout << "  4. Carbon Emission Analysis\n";
    cout << "  5. Search Resident\n";
    cout << "  6. Sort Residents\n";
    cout << "  0. Exit\n";
    cout << "------------------------------------------\n";
    cout << "  Choice: ";
}

static void clearScreen() {
    system("cls");
}

static void pauseAndContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("cls");
}

int main() {
    const string pathA = "../dataset/dataset1-cityA.csv";
    const string pathB = "../dataset/dataset2-cityB.csv";
    const string pathC = "../dataset/dataset3-cityC.csv";

    ResidentArray residents;

    cout << "Loading Residents Datasets\n";
    CSVLoader::loadAll(pathA, pathB, pathC, residents);

    int choice;
    while (true) {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            cout << "Invalid input.\n";
            continue;
        }

        system("cls");
        switch (choice) {
            case 0: cout << "Goodbye.\n"; return 0;
            case 1:
                printStatus(residents);
                pauseAndContinue();
                break;
            case 2:
                printTable(residents, 20);
                pauseAndContinue();
                break;
            case 3:
                printTable(residents);
                pauseAndContinue();
                break;
            case 4:
            {
            const int DATASET_COUNT = 3;
            const int MODE_COUNT = 6;
            const int AGE_GROUP_COUNT = 5;

            string datasetNames[DATASET_COUNT] = {
                "City A",
                "City B",
                "City C"
            };

            string modeNames[MODE_COUNT] = {
                "Car",
                "Bus",
                "Bicycle",
                "Walking",
                "School Bus",
                "Carpool"
            };

            string ageGroupNames[AGE_GROUP_COUNT] = {
                "6-17",
                "18-25",
                "26-45",
                "46-60",
                "61-100"
            };

            double datasetTotal[DATASET_COUNT] = {0};
            double modeTotal[MODE_COUNT] = {0};
            double datasetAgeTotal[DATASET_COUNT][AGE_GROUP_COUNT] = {0};
            double ageTotal[AGE_GROUP_COUNT] = {0};
            int ageCount[AGE_GROUP_COUNT] = {0};

            for (int i = 0; i < residents.size(); i++) {
                const Resident& r = residents.get(i);
                double emission = r.emission();

                int datasetIndex = -1;
                if (r.residentID.length() > 0) {
                    if (r.residentID[0] == 'A') datasetIndex = 0;
                    else if (r.residentID[0] == 'B') datasetIndex = 1;
                    else if (r.residentID[0] == 'C') datasetIndex = 2;
                }

                int modeIndex = -1;
                for (int m = 0; m < MODE_COUNT; m++) {
                    if (r.modeOfTransport == modeNames[m]) {
                        modeIndex = m;
                        break;
                    }
                }

                int ageIndex = -1;
                if (r.age >= 6 && r.age <= 17) ageIndex = 0;
                else if (r.age >= 18 && r.age <= 25) ageIndex = 1;
                else if (r.age >= 26 && r.age <= 45) ageIndex = 2;
                else if (r.age >= 46 && r.age <= 60) ageIndex = 3;
                else if (r.age >= 61 && r.age <= 100) ageIndex = 4;

                if (datasetIndex != -1) {
                    datasetTotal[datasetIndex] += emission;
                }

                if (modeIndex != -1) {
                    modeTotal[modeIndex] += emission;
                }

                if (ageIndex != -1) {
                    ageTotal[ageIndex] += emission;
                    ageCount[ageIndex]++;

                    if (datasetIndex != -1) {
                        datasetAgeTotal[datasetIndex][ageIndex] += emission;
                    }
                }
            }

            cout << "\n================ CARBON EMISSION ANALYSIS ================\n";

            cout << "\nTOTAL CARBON EMISSIONS PER DATASET\n";
            cout << "+------------+--------------------------+\n";
            cout << "| " << left << setw(10) << "Dataset"
                << " | " << right << setw(24) << "Total Emission(kg CO2)" << " |\n";
            cout << "+------------+--------------------------+\n";

            for (int i = 0; i < DATASET_COUNT; i++) {
                cout << "| " << left << setw(10) << datasetNames[i]
                    << " | " << right << setw(24) << fixed << setprecision(2) << datasetTotal[i]
                    << " |\n";
            }

            cout << "+------------+--------------------------+\n";

            cout << "\nCARBON EMISSIONS PER MODE OF TRANSPORT\n";
            cout << "+---------------+--------------------------+\n";
            cout << "| " << left << setw(13) << "Mode"
                << " | " << right << setw(24) << "Total Emission(kg CO2)" << " |\n";
            cout << "+---------------+--------------------------+\n";

            for (int i = 0; i < MODE_COUNT; i++) {
                cout << "| " << left << setw(13) << modeNames[i]
                    << " | " << right << setw(24) << fixed << setprecision(2) << modeTotal[i]
                    << " |\n";
            }

            cout << "+---------------+--------------------------+\n";

            cout << "\nCARBON EMISSION COMPARISON ACROSS DATASETS AND AGE GROUPS\n";
            cout << "+------------+------------+------------+------------+------------+------------+\n";
            cout << "| " << left << setw(10) << "Dataset";

            for (int i = 0; i < AGE_GROUP_COUNT; i++) {
                cout << " | " << right << setw(10) << ageGroupNames[i];
            }

            cout << " |\n";
            cout << "+------------+------------+------------+------------+------------+------------+\n";

            for (int d = 0; d < DATASET_COUNT; d++) {
                cout << "| " << left << setw(10) << datasetNames[d];

                for (int a = 0; a < AGE_GROUP_COUNT; a++) {
                    cout << " | " << right << setw(10) << fixed << setprecision(2) << datasetAgeTotal[d][a];
                }

                cout << " |\n";
            }

            cout << "+------------+------------+------------+------------+------------+------------+\n";

            cout << "\nAGE GROUP EMISSION SUMMARY\n";
            cout << "+------------+------------+----------------+----------------+\n";
            cout << "| " << left << setw(10) << "Age Group"
                << " | " << right << setw(10) << "Residents"
                << " | " << right << setw(14) << "Total CO2"
                << " | " << right << setw(14) << "Avg/Resident" << " |\n";
            cout << "+------------+------------+----------------+----------------+\n";

            for (int i = 0; i < AGE_GROUP_COUNT; i++) {
                double average = 0;

                if (ageCount[i] > 0) {
                    average = ageTotal[i] / ageCount[i];
                }

                cout << "| " << left << setw(10) << ageGroupNames[i]
                    << " | " << right << setw(10) << ageCount[i]
                    << " | " << right << setw(14) << fixed << setprecision(2) << ageTotal[i]
                    << " | " << right << setw(14) << fixed << setprecision(2) << average
                    << " |\n";
            }

            cout << "+------------+------------+----------------+----------------+\n";

            pauseAndContinue();

            break;
        }
            case 5:
                searchMenu(residents);
                pauseAndContinue();
                break;

            case 6:
                sortMenu(residents);
                pauseAndContinue();
                break;

            default: cout << "Invalid choice.\n"; break;

        }
        
    }
}
