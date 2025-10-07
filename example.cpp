#include <iostream>
#include "AthanLib.h"

int main() {
    // Create a PrayerTimes object
    PrayerTimes today;

    // Example inputs: 06-Oct-2025, Los Angeles, California, United States of America.    
    int day = 6;
    int month = 10;
    int year = 2025;


    const double timeZone = -7.0;
    const double lat = 34.0549; //REMINDER: if latitude is south or longitude is west, please make sure that the value is set to negative.
    const double lon = -118.2426;



    // Calculate prayer times
    today.calcPrayerTimes(day, month, year, lat, lon, timeZone, ISNA);

    // Display results
    std::cout << "Date: " << day << "/" << month << "/" << year << std::endl;
    std::cout << "Location: " << lat << ", " << lon << " (UTC" << timeZone << ")" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Fajr:     " << getTime(today.fajr)    << std::endl;
    std::cout << "Sunrise:  " << getTime(today.sunrise) << std::endl;
    std::cout << "Dhuhr:    " << getTime(today.dhuhr)   << std::endl;
    std::cout << "Asr (Shafi'i):  " << getTime(today.asr1)   << std::endl;
    std::cout << "Asr (Hanafi):   " << getTime(today.asr2)   << std::endl;
    std::cout << "Maghrib:  " << getTime(today.maghrib) << std::endl;
    std::cout << "Isha:     " << getTime(today.isha)    << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return 0;
}
