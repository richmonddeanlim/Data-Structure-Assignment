#pragma once
#define resident_hpp
#include <string>
using namespace std;

struct Residents {
    string residentID;
    int age;
    string modeOfTransport;
    int dailyDistance;
    double carbonEmissionFactor;
    int avgDayPerMonth;
    string city;
};