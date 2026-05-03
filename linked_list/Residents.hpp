#pragma once
#define resident_hpp
#include <string>
using namespace std;

// The residents struct that contains the attributes of the residents.
struct Residents {
    string residentID;
    int age;
    string modeOfTransport;
    int dailyDistance;
    double carbonEmissionFactor;
    int avgDayPerMonth;
    double emission() const {
        return dailyDistance * carbonEmissionFactor * avgDayPerMonth;
    }
};
