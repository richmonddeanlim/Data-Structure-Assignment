#pragma once
#include <string>

struct Resident {
    std::string residentID;           // example: "A001", "B042", "C117"
    int         age;                  // in years
    std::string modeOfTransport;      // "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
    int         dailyDistance;        // in kilometers
    double      co2Factor;            // kg CO2 per km
    int         averageDayPerMonth;       // days per month this mode is used

    // Calculate the total monthly carbon emission in kg CO2.
    double emission() const {
        return dailyDistance * co2Factor * averageDayPerMonth;}
};