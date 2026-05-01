#include "CSVLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//cleaning whitespace. extraspace, hidden newline from the start and end of the string
static string trim(const string& s) {
    const char* ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

//takes a single row from the csv and split it to fills the resident struct
static bool parseLine(const string& line, Resident& out) {
    stringstream ss(line);   
    string fields[6];       
    int i = 0;
    while (i < 6 && getline(ss, fields[i], ',')) {
        fields[i] = trim(fields[i]);
        i++;
    }
    if (i < 6) return false; 
    try {
        out.residentID = fields[0];        
        out.age = stoi(fields[1]);     
        out.modeOfTransport = fields[2];         
        out.dailyDistance = stoi(fields[3]);    
        out.co2Factor = stod(fields[4]);    
        out.averageDayPerMonth = stoi(fields[5]);   
    } catch (...) {
        return false;  
    }

    return true;
}

namespace CSVLoader {
    //open the file and load all the resident into the array.
    bool loadFromFile(const string& filename, ResidentArray& arr) {
        ifstream in(filename);
        if (!in.is_open()) {
            cerr << "CSVLoader Could not open: " << filename << "\n";
            return false;
        }

        string line;
        bool headerSkipped = false;
        int loaded = 0;
        int skipped = 0;

        while (getline(in, line)) {
            if (trim(line).empty()) continue; 
            if (!headerSkipped) {
                headerSkipped = true;         
                continue;
            }
            Resident r;
            if (parseLine(line, r)) {
                arr.add(r);
                loaded++;
            } else {
                skipped++;
            } }
        cout << "CSVLoader " << filename << " -> loaded " << loaded << ", skipped " << skipped << "\n";
        return true;
    }

    //load all three dataset at once
    int loadAll(const string& cityAPath, const string& cityBPath, const string& cityCPath, ResidentArray& combined) {
        int successes = 0;
        if (loadFromFile(cityAPath, combined)) successes++;
        if (loadFromFile(cityBPath, combined)) successes++;
        if (loadFromFile(cityCPath, combined)) successes++;
        return successes;
    }

} 