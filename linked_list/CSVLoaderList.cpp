// This file implements the CSVLoaderList class, which loads the resident data from the CSV files / datasets into the linked list. 
#include "CSVLoaderList.hpp"
#include <fstream> // To handle file input and output 
#include <sstream>  // To handle string stream and to parse the CSV / dataset files
#include <iostream>

// A function from CSVLoaderList header file that takes the filename, the linkedlist to load the data and the city as parameters.
void CSVLoaderList::loadFile(string filename, LinkedList& list, string city) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        string head;
        getline(file, head);
        while(getline(file, line)){
            stringstream s(line); // include the string stream to parse the line in the datasets and extract them. 
            Residents r; // initialize the resident struct.
            string temp; // as a temporary variable to hold the values from the dataset.

            // the getline function is used to read the values line by line from the datasets.
            // using stoi function to convert the string values into integer for age, dailyDistance, avgDayPerMonth.
            // using stod function to convert the string values into double for carbonEmissionFactor.
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
        cout << "Error opening the file: " << filename << endl; // For file opening error handling.
    }
}