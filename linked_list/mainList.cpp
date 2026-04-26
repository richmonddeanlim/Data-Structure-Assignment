#include "Residents.hpp"
#include "LinkedList.hpp"
#include "CSVLoaderList.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void menu (LinkedList& list) {
    int option;
    do {
        cout << "==============================" << endl;
        cout << "1. Add Resident" << endl;
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
                cout << "Enter Age: ";
                cin >> r.age;
                cout << "Enter Mode of Transport: ";
                cin >> r.modeOfTransport;
                cout << "Enter Daily Distance: ";
                cin >> r.dailyDistance;
                cout << "Enter Carbon Emission Factor: ";
                cin >> r.carbonEmissionFactor;
                cout << "Enter Average Days per Month: ";
                cin >> r.avgDayPerMonth;
                cout << "Enter City: ";
                cin >> r.city;
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
                cout << "Going back..." << endl;
                return;
            default:
                cout << "Invalid option. Please choose a valid option!" << endl;
                break;
        }
    }while (option != 4);
}
int main() {
    LinkedList cityA, cityB, cityC;
    CSVLoaderList load;
    load.loadFile("../dataset/dataset1-cityA.csv", cityA);
    load.loadFile("../dataset/dataset2-cityB.csv", cityB);
    load.loadFile("../dataset/dataset3-cityC.csv", cityC);  
    cout << "==============================" << endl;
    cout << "City Carbon Emission Analysis" << endl;
    cout << "==============================" << endl;
    cout << "Select a city(s): " << endl;
    cout << "1. City A" << endl;
    cout << "2. City B" << endl;
    cout << "3. City C" << endl;
    cout << "4. All Cities" << endl;
    cout << "5. Exit" << endl;
    int choice;
    cin >> choice;
    do{
        switch(choice){
            case 1: 
                cout << "City A: " << endl;
                menu(cityA);
                break;
            case 2:
                cout << "City B: " << endl;
                menu(cityB);
                break;
            case 3:
                cout << "City C: " << endl;
                menu(cityC);
                break;
            case 4:
                cout << "All Cities: " << endl;
                cityA.displayResidents();
                cityB.displayResidents();
                cityC.displayResidents();
                break;
            case 5:
                cout << "Exiting... " << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option!" << endl;
                break;
        }
        cout << "Select a city: ";
        cin >> choice;
    } while(choice != 5);
    return 0;
}

