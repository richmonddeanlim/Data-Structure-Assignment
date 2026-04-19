//this represent a single resident record and will be used by both the array and linked list program.
#pragma once
#include <string>

struct Resident {
    std::string residentID;           // e.g. "A001", "B042", "C117"
    int         age;                  // in years
    std::string modeOfTransport;      // "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    int         dailyDistance;        // km travelled per day
    double      carbonEmissionFactor; // kg CO2 per km
    int         avgDayPerMonth;       // days per month this mode is used

    // Monthly carbon emission in kg CO2.
    double emission() const {
        return dailyDistance * carbonEmissionFactor * avgDayPerMonth;
    }
};