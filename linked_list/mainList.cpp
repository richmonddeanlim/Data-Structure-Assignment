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
        if (criteria == 1) sortTime = SortingList::sortByAge(list);
        else if (criteria == 2) sortTime = SortingList::sortByTransport(list);
        else if (criteria == 3) sortTime = SortingList::sortByDistance(list);
        cout << "Selection Sort completed in " << fixed << setprecision(6) << sortTime << " seconds." << endl;
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

// The menu function to display the operations.
void menu (LinkedList& list, string cityname) {
    int option;
    do {
        cout << "==============================" << endl;
        cout << "1. Add Resident" << endl;
        cout << "2. Display Residents" << endl;
        cout << "3. Remove Resident" << endl;
        cout << "4. Search Resident" << endl;
        cout << "5. Back" << endl;
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
                cout << "Going back..." << endl;
                return;
            default:
                cout << "Invalid option. Please choose a valid option!" << endl;
                break;
        }
    }while (option != 5);
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
    cout << "5. Exit" << endl;
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
                cout << "Exiting... " << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option!" << endl;
                break;
        }
        showMenu();
        cin >> choice;
    } while(choice != 5);
    return 0;
}
