#ifndef ATHANLIB_H
#define ATHANLIB_H

#include <cmath>
#include <string>
#include <utility>

#define M_PI 3.141592653589793238462643

// Math functions
 constexpr inline double deg2rad(double d);
 constexpr inline double rad2deg(double r);
  inline double norm360(double d); // Allows us to warp variables above 360 degrees into an angle between 0-360 degrees.
  inline double norm24(double h); // failsafe incase hours are >= 24
 int sign(int x); //Formula sourced from "https://en.wikipedia.org/wiki/Sign_function"



// Time functions
 int getHour(double time); 
 int getMinute(double time);
 std::string getTime(double timeHours);
 double convertToJulianDate(int day, int month, int year); // Sourced from "https://aa.usno.navy.mil/faq/JD_formula"



//Prayer time calculations
 //Astronomical formulas
  double twilightFormula(double a, double lat, double D); // Sunrise/Sunset calculation formula
  double asrFormula(double n, double lat, double D);
  
 //Convention Angles
  struct ConventionAngle {
    double fajrAngle;
    double ishaAngle;
  };

  inline constexpr ConventionAngle ISNA       { -15.0, -15.0 }; // Islamic Society of North America
  inline constexpr ConventionAngle MWL        { -18.0, -17.0 }; // Muslim World League
  inline constexpr ConventionAngle Egypt        { -19.5, -17.5 }; // Egyptian General Authority of Survey 
  inline constexpr ConventionAngle Shia        { -16.0, -14.0 }; // Shia Ithna-Ashari, Leva Institute, Qum
  inline constexpr ConventionAngle UIS        { -18.0, -18.0 }; // University of Islamic Sciences, Karachi
  inline constexpr ConventionAngle UmmAlQura        { -18.5, 99.0}; // Umm al-Qura, Makkah.     Reserved ishaAngle 99 for UmmAlQura since its the only one that doesnt have an isha angle and instead uses manual offsets.
  inline constexpr ConventionAngle France        { -12.0, -12.0 }; // Muslims of France
  inline constexpr ConventionAngle Russia        { -16.0, -15.0 }; // Spiritual Administration of Muslims of Russia
  inline constexpr ConventionAngle Singapore        { -20.0, -18.0 }; // Islamic Religious Council of Singapore
  //inline constexpr ConventionAngle Custom { }; Coming soon



 //Prayer times formulas
  struct PrayerTimes {
   double fajr, sunrise, dhuhr, asr1, asr2, maghrib, isha;

   void calcPrayerTimes(int day =7, int month=10, int year=2025, double lat = 21.4241, double lon = 39.8173, double timeZone = 3.0, ConventionAngle conv = UmmAlQura); //defaults incase user doesnt assign anything (Mecca, Saudi Arabia)
   };



/*SOURCES:
  Prayer Times Calculation, https://praytimes.org/docs/calculation
  Computing Approximate Solar Coordinates,  https://aa.usno.navy.mil/faq/sun_approx
  Twilight formula correction sources: https://astronomycenter.net/pdf/mohamoud_2017.pdf  &  https://www.sjctni.edu/Department/ma/eLecture/Twilight.pdf
  Sign function: https://en.wikipedia.org/wiki/Sign_function
*/


#endif 
