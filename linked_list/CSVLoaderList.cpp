#include "CSVLoaderList.hpp"
#include <fstream>
#include <sstream>  
#include <iostream>

void CSVLoaderList::loadFile(string filename, LinkedList& list, string city) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        string head;
        getline(file, head);
        while(getline(file, line)){
            stringstream s(line);
            Residents r;
            string temp;

            getline(s, r.residentID, ',');
            getline(s, temp, ',');
            r.age = stoi(temp);
            getline(s, r.modeOfTransport, ',');
            getline(s, temp, ',');
            r.dailyDistance = stoi(temp);
            getline(s, temp, ',');
            r.carbonEmissionFactor = stod(temp);
            getline(s, temp, ',');
            r.avgDayPerMonth = stoi(temp);
            r.city = city;
            list.addResident(r);
        }; 
    }
    else {
        cout << "Error opening the file: " << filename << endl;
    }
}