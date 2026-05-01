#include "Residents.hpp"
#include "LinkedList.hpp"
#include "CSVLoaderList.hpp"
#include "SearchingList.hpp"
#include "SortingList.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void searchMenu(LinkedList& list) {
    int dataState, algorithm, criteria;

    cout << "\n    Search Resident    " << endl;
    cout << "-----------------------------------\n";
    cout << "Select Data State:" << endl;
    cout << "1. Unsorted Data" << endl;
    cout << "2. Sorted Data" << endl;
    cout << "3. Back" << endl;
    cout << "Choice: ";
    cin >> dataState;

    if (dataState == 3) return;

    if (dataState == 1) {
        cout << "\nSelect Algorithm:" << endl;
        cout << "1. Linear Search" << endl;
        cout << "Choice: ";
        cin >> algorithm;
        algorithm = 1; 
    } else {
        cout << "\nSelect Algorithm:" << endl;
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cout << "Choice: ";
        cin >> algorithm;
    }

    cout << "\nSelect Criteria:" << endl;
    cout << "1. Age Range" << endl;
    cout << "2. Mode of Transport" << endl;
    cout << "3. Distance Threshold" << endl;
    cout << "Choice: ";
    cin >> criteria;

    // Trigger Sorting if "Sorted Data" is selected
    if (dataState == 2) {
        cout << "\n[Running Sorting Experiment...]" << endl;
        double sortTime = 0;
        size_t memUsed = 0;
        if (criteria == 1) sortTime = SortingList::sortByAge(list, memUsed);
        else if (criteria == 2) sortTime = SortingList::sortByTransport(list, memUsed);
        else if (criteria == 3) sortTime = SortingList::sortByDistance(list, memUsed);
        cout << "Selection Sort completed in " << fixed << setprecision(6) << sortTime << " seconds." << endl;
        cout << "Memory Used: " << memUsed << " bytes" << endl;
    }

    // Execute Search
    if (criteria == 1) {
        int minAge, maxAge;
        cout << "Enter min age: "; cin >> minAge;
        cout << "Enter max age: "; cin >> maxAge;
        if (algorithm == 1) SearchingList::linearSearchAge(list, minAge, maxAge);
        else SearchingList::binarySearchAge(list, minAge, maxAge);
    } 
    else if (criteria == 2) {
        string mode;
        cout << "Enter mode of transport: ";
        cin >> mode;
        if (algorithm == 1) SearchingList::linearSearchTransport(list, mode);
        else SearchingList::binarySearchTransport(list, mode);
    }
    else if (criteria == 3) {
        int threshold;
        cout << "Enter distance threshold: "; cin >> threshold;
        if (algorithm == 1) SearchingList::linearSearchDistance(list, threshold);
        else SearchingList::binarySearchDistance(list, threshold);
    }
}

//The menu for sorting
void sortMenu(LinkedList& list) {
    int criteria;
    cout << "\n   Sort Residents   " << endl;
    cout << "==============================\n";
    cout << "Select Criteria:" << endl;
    cout << "1. Age" << endl;
    cout << "2. Carbon Emission" << endl;
    cout << "3. Daily Distance" << endl;
    cout << "4. Back" << endl;
    cout << "Choice: ";
    cin >> criteria;

    if (criteria == 4) return;

    double sortTime = 0;
    size_t memUsed = 0;
    if (criteria == 1) sortTime = SortingList::sortByAge(list, memUsed);
    else if (criteria == 2) sortTime = SortingList::sortByEmission(list, memUsed);
    else if (criteria == 3) sortTime = SortingList::sortByDistance(list, memUsed);

    cout << "\n[Success] Selection Sort completed in " << fixed << setprecision(6) << sortTime << " seconds." << endl;
    cout << "Memory Used: " << memUsed << " bytes" << endl;
    cout << "\n--- Sorted Results---\n";
    list.displayResidents();
}

// The menu function to display the operations.
void menu (LinkedList& list, string cityname) {
    int option;
    do {
        cout << "==============================" << endl;
        cout << "1. Add Resident" << endl;
        cout << "2. Display Residents" << endl;
        cout << "3. Remove Resident" << endl;
        cout << "4. Search Resident" << endl;
        cout << "5. Sort Residents" << endl;
        cout << "6. Back" << endl;
        cout << "Select an option: ";
        cin >> option;
        switch(option){
            case 1: {
                Residents r;
                cout << "Enter Resident ID: "; 
                cin >> r.residentID;
                char initial = cityname[5];
                if (r.residentID[0] != initial) {
                    cout << "Invalid Resident ID. The resident ID should start with '" << initial << "'." << endl;
                    break;
                }
                if (list.findResident(r.residentID)) {
                    cout << "Resident ID: " << r.residentID << " already exists. Please enter another ID." << endl;
                    break;
                }
                cout << "Enter Age: "; 
                cin >> r.age;
                cout << "Enter Mode of Transport: "; 
                cout << "1. Bicycle" << endl;
                cout << "2. Bus" << endl;
                cout << "3. Car" << endl;
                cout << "4. Carpool" << endl;
                cout << "5. School Bus" << endl;
                cout << "6. Walking" << endl;
                cout << "7. Others" << endl;
                cout << "Choice: ";
                int choice;
                cin >> choice;
                switch(choice){
                    case 1: 
                        r.modeOfTransport = "Bicycle"; 
                        break;
                    case 2: 
                        r.modeOfTransport = "Bus"; 
                        break;
                    case 3: 
                        r.modeOfTransport = "Car"; 
                        break;
                    case 4: 
                        r.modeOfTransport = "Carpool"; 
                        break;
                    case 5: 
                        r.modeOfTransport = "School Bus"; 
                        break;
                    case 6: 
                        r.modeOfTransport = "Walking"; 
                        break;
                    case 7:
                        cout << "Enter mode of transport: ";
                        cin.ignore();
                        getline(cin, r.modeOfTransport);
                        r.modeOfTransport[0] = toupper(r.modeOfTransport[0]);
                        break;
                    default: 
                    cout << "Invalid choice. Please try again." << endl; 
                    break;
                }
                cout << "Enter Daily Distance: "; 
                cin >> r.dailyDistance;
                cout << "Enter Carbon Emission Factor: "; 
                cin >> r.carbonEmissionFactor;
                cout << "Enter Average Days per Month: "; 
                cin >> r.avgDayPerMonth;
                r.city = cityname;
                list.addResident(r);
                break;
            }
            case 2:
                list.displayResidents();
                break;
            case 3: {
                string residentid;
                cout << "Enter Resident ID to remove: ";
                cin >> residentid;
                list.removeResident(residentid);
                break;
            }
            case 4:
                searchMenu(list);
                break;
            case 5:
                sortMenu(list);
                break;
            case 6:
                cout << "Going back..." << endl;
                return;
            default:
                cout << "Invalid option. Please choose a valid option!" << endl;
                break;
        }
    }while (option != 6);
}

// the function to display the menu for all cities.
void allcities(LinkedList& cityA, LinkedList& cityB, LinkedList& cityC) {
    int option;
    do {
        cout << "==============================" << endl;
        cout << "1. Add Resident "<< endl;
        cout << "2. Display Residents" << endl;
        cout << "3. Remove Resident" << endl;
        cout << "4. Back" << endl;
        cout << "Select an option: ";
        cin >> option;
        switch(option){
            case 1: {
                Residents r;
                cout << "Enter Resident ID: "; 
                cin >> r.residentID;
                char initial = r.residentID[0];
                if (initial != 'A' && initial != 'B' && initial != 'C') {
                    cout << "Invalid Resident ID. The resident ID should start with 'A', 'B', or 'C'." << endl;
                    break;
                }
                LinkedList* targetList = nullptr;
                if (initial == 'A') {
                    targetList = &cityA;
                }
                else if (initial == 'B') {
                    targetList = &cityB;
                }
                else if (initial == 'C') {
                    targetList = &cityC;
                }
                if (targetList->findResident(r.residentID)) {
                    cout << "Resident ID: " << r.residentID << " already exists. Please enter another ID." << endl;
                    break;
                }
                cout << "Enter Age: "; 
                cin >> r.age;
                cout << "Enter Mode of Transport: "; 
                cout << "1. Bicycle" << endl;
                cout << "2. Bus" << endl;
                cout << "3. Car" << endl;
                cout << "4. Carpool" << endl;
                cout << "5. School Bus" << endl;
                cout << "6. Walking" << endl;
                cout << "7. Others" << endl;
                cout << "Choice: ";
                int choice;
                cin >> choice;
                switch(choice){
                    case 1: 
                        r.modeOfTransport = "Bicycle"; 
                        break;
                    case 2: 
                        r.modeOfTransport = "Bus"; 
                        break;
                    case 3: 
                        r.modeOfTransport = "Car"; 
                        break;
                    case 4: 
                        r.modeOfTransport = "Carpool"; 
                        break;
                    case 5: 
                        r.modeOfTransport = "School Bus"; 
                        break;
                    case 6: 
                        r.modeOfTransport = "Walking"; 
                        break;
                    case 7:
                        cout << "Enter mode of transport: ";
                        cin.ignore();
                        getline(cin, r.modeOfTransport);
                        r.modeOfTransport[0] = toupper(r.modeOfTransport[0]);
                        break;
                    default: 
                    cout << "Invalid choice. Please try again." << endl; 
                    break;
                }
                cout << "Enter Daily Distance: "; 
                cin >> r.dailyDistance;
                cout << "Enter Carbon Emission Factor: "; 
                cin >> r.carbonEmissionFactor;
                cout << "Enter Average Days per Month: "; 
                cin >> r.avgDayPerMonth;
                if (initial == 'A') {
                    r.city = "City A";
                }
                else if (initial == 'B') {
                    r.city = "City B";
                }
                else if (initial == 'C') {
                    r.city = "City C";
                }
                targetList->addResident(r);
                cout << "Resident is added to " << r.city << "." << endl;
                break;
            }

            case 2:
                cout << "\n=== City A Residents ===" << endl;
                cityA.displayResidents();
                cout << "\n=== City B Residents ===" << endl;
                cityB.displayResidents();
                cout << "\n=== City C Residents ===" << endl;
                cityC.displayResidents();
                break;

            case 3: {
                string residentid;
                cout << "Enter Resident ID to remove: ";
                cin >> residentid;
                char initial = residentid[0];
                if (initial == 'A') {
                    cityA.removeResident(residentid);
                }
                else if (initial == 'B') {
                    cityB.removeResident(residentid);
                }
                else if (initial == 'C') {
                    cityC.removeResident(residentid);
                }
                else {
                    cout << "Invalid Resident ID. The resident ID should start with 'A', 'B', or 'C'." << endl;
                }
                break;
            }

            case 4:
                cout << "Going back..." << endl;
                return;

            default:
                cout << "Invalid option. Please choose a valid option!" << endl;
                break;
        }
    } while (option != 4);
}

// the function to display the main menu for city selection
void showMenu() {
    cout << "==============================" << endl;
    cout << "City Carbon Emission Analysis" << endl;
    cout << "==============================" << endl;
    cout << "1. City A" << endl;
    cout << "2. City B" << endl;
    cout << "3. City C" << endl;
    cout << "4. All Cities" << endl;
    cout << "5. Carbon Emission Analysis" << endl;
    cout << "6. Exit" << endl;
    cout << "Select a city(s): " << endl;
}

// the main function to load the datasets into the linked list and display the menu for ciy selectio and operations.
int main() {
    LinkedList cityA, cityB, cityC;
    CSVLoaderList load;
    load.loadFile("../dataset/dataset1-cityA.csv", cityA, "City A");
    load.loadFile("../dataset/dataset2-cityB.csv", cityB, "City B");
    load.loadFile("../dataset/dataset3-cityC.csv", cityC, "City C");
    showMenu();
    int choice;
    cin >> choice;
    do{
        switch(choice){
            case 1: 
                cout << "City A: " << endl;
                menu(cityA, "City A");
                break;
            case 2:
                cout << "City B: " << endl;
                menu(cityB, "City B");
                break;
            case 3:
                cout << "City C: " << endl;
                menu(cityC, "City C");
                break;
            case 4:
                cout << "All Cities: " << endl;
                allcities(cityA, cityB, cityC);
                break;
            case 5:
            {
            const int DATASET_COUNT = 3;
            const int MODE_COUNT = 6;
            const int AGE_GROUP_COUNT = 5;

            string datasetNames[DATASET_COUNT] = {"City A", "City B", "City C"};
            string modeNames[MODE_COUNT] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
            string ageGroupNames[AGE_GROUP_COUNT] = {"6-17", "18-25", "26-45", "46-60", "61-100"};

            LinkedList* lists[DATASET_COUNT] = {&cityA, &cityB, &cityC};

            double datasetTotal[DATASET_COUNT] = {0};
            double modeTotal[MODE_COUNT] = {0};
            double datasetAgeTotal[DATASET_COUNT][AGE_GROUP_COUNT] = {0};
            double ageTotal[AGE_GROUP_COUNT] = {0};
            int ageCount[AGE_GROUP_COUNT] = {0};

            for (int d = 0; d < DATASET_COUNT; d++) {
                Node* current = lists[d]->getHead();

                while (current != nullptr) {
                    Residents r = current->data;

                    double emission = r.dailyDistance * r.carbonEmissionFactor * r.avgDayPerMonth;

                    datasetTotal[d] += emission;

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

                    if (modeIndex != -1) {
                        modeTotal[modeIndex] += emission;
                    }

                    if (ageIndex != -1) {
                        ageTotal[ageIndex] += emission;
                        ageCount[ageIndex]++;
                        datasetAgeTotal[d][ageIndex] += emission;
                    }

                    current = current->next;
                }
            }

            cout << "\n================ LINKED LIST CARBON EMISSION ANALYSIS ================\n";

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

            break;
        }

            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option!" << endl;
                break;
        }
        showMenu();
        cin >> choice;
    } while(choice != 6);
    return 0;
}
