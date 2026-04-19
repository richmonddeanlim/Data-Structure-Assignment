// run with g++ main.cpp ResidentArray.cpp CSVLoader.cpp -o program
#include "ResidentArray.hpp"
#include "CSVLoader.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

static void printSeparator() {
    cout << "+-------+-----+---------------+----------+---------+------+------------+\n";
}

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
             << " | " << right << setw(7)  << fixed << setprecision(2) << r.carbonEmissionFactor
             << " | " << right << setw(4)  << r.avgDayPerMonth
             << " | " << right << setw(10) << fixed << setprecision(2) << r.emission()
             << " |\n";
    }
    printSeparator();
    cout << "  Showing " << shown << " of " << total << " residents.\n";
}

static void printStatus(const ResidentArray& arr) {
    cout << "\n--- Array Status ---\n";
    cout << "  Count    : " << arr.size()        << " residents\n";
    cout << "  Capacity : " << arr.getCapacity() << " slots\n";
    cout << "--------------------\n";
}

static void printMenu() {
    cout << "\n==========================================\n";
    cout << "  URBAN CARBON EMISSION ANALYSIS - ARRAY  \n";
    cout << "==========================================\n";
    cout << "  1. Reload all datasets\n";
    cout << "  2. Show array status\n";
    cout << "  3. Display first 20 residents\n";
    cout << "  4. Display ALL residents\n";
    cout << "  0. Exit\n";
    cout << "------------------------------------------\n";
    cout << "  Choice: ";
}

static void clearScreen() {
    system("cls");
}

int main() {
    const string pathA = "../dataset/dataset1-cityA.csv";
    const string pathB = "../dataset/dataset2-cityB.csv";
    const string pathC = "../dataset/dataset3-cityC.csv";

    ResidentArray residents;

    cout << "Loading datasets...\n";
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();
        switch (choice) {
            case 0: cout << "Goodbye.\n"; return 0;
            case 1:
                residents.clear();
                CSVLoader::loadAll(pathA, pathB, pathC, residents);
                cout << "Datasets reloaded.\n";
                break;
            case 2: printStatus(residents);    break;
            case 3: printTable(residents, 20); break;
            case 4: printTable(residents);     break;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}