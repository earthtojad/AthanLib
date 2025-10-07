#include "AthanLib.h"



// Math functions

 constexpr inline double deg2rad(double d){ 
  return d * M_PI / 180.0; 
   }

 constexpr inline double rad2deg(double r){ 
   return r * 180.0 / M_PI; 
   }

  inline double norm360(double d){// Allows us to warp variables above 360 degrees into an angle between 0-360 degrees.
  double r = std::fmod(d, 360.0); 
  return (r < 0 ? r + 360.0 : r); // Included this statement because fmod returns negative values. This statement corrects it.
  }

  inline double norm24(double h){// failsafe incase hours are >= 24
   double r = std::fmod(h, 24.0);
  return (r < 0 ? r + 24.0 : r); //if r<0, add 24, else: r
  }

 int sign(double x) { //Formula sourced from "https://en.wikipedia.org/wiki/Sign_function"
    if(x<0){
      x = -1;
    }
    else if(x ==0){
      x =0;
    }
    else if(x>0){
      x =1;
    }
    return x;
  }





// Time functions

 static int minutesFromDay(double hoursDay) {
  // round to nearest minute
  long m = (long)floor(hoursDay * 60.0 + 0.5);
  // wrap to [0, 24*60)
  const long DAY_M = 24L * 60L;
  m = ((m % DAY_M) + DAY_M) % DAY_M;
  return (int)m;
  }

 int getHour(double timeHours) {
  int m = minutesFromDay(timeHours);
  return (m / 60) % 24;
  }

 int getMinute(double timeHours) {
  int m = minutesFromDay(timeHours);
  return m % 60;
  }

 std::string getTime(double timeHours) {
  int h = getHour(timeHours);
  int m = getMinute(timeHours);
  char buf[6];
  snprintf(buf, sizeof(buf), "%02d:%02d", h, m);
  return std::string(buf);
  }

 double convertToJulianDate(int day, int month, int year){ // Sourced from "https://aa.usno.navy.mil/faq/JD_formula"
  double jD = 367 * year - std::trunc((7*(year + std::trunc((month+9)/12)))/4) + std::trunc((275 * month)/9) + day + 1721013.5 + (12/24.0)  - 0.5 * sign(100 * year + month - 190002.5) + 0.5;
  return jD;
  }





// Prayer time calculations "https://praytimes.org/docs/calculation"

 // Astronomical formulas
  double twilightFormula(double a, double lat, double D) { // Sunrise/Sunset calculation formula
  // The time difference between the mid-day and the time at which sun reaches an angle a below the horizon 
  // Formula sourced from "https://astronomycenter.net/pdf/mohamoud_2017.pdf"  and  "https://www.sjctni.edu/Department/ma/eLecture/Twilight.pdf", the formual used in https://praytimes.org/docs/calculation is incorrect.

  double aRad = deg2rad(a);
  double phi  = deg2rad(lat);
  double dec  = deg2rad(D);

  double num = std::sin(aRad) - std::sin(phi) * std::sin(dec);
  double den = std::cos(phi)  * std::cos(dec);
  double q   = num / den;

  // numeric safety (numbers passed through acos have to be between -1 and 1)
  if (q < -1.0) q = -1.0;
  if (q >  1.0) q =  1.0;

  double Hdeg = rad2deg(std::acos(q));
  return Hdeg / 15.0; //hours
  }



  double asrFormula(double n, double lat, double D) {

  //"The following formula calculates the time difference between solar noon and the moment when an object's shadow reaches t times its own length, in addition to the object's shadow length at noon: "

  double phi = deg2rad(lat);
  double dec = deg2rad(D);
  double aRad = std::atan(1.0 / (n + std::tan(std::fabs(phi - dec))));
  double aDeg = rad2deg(aRad);
  return twilightFormula(aDeg,lat,D); // hours from noon
  }



  void PrayerTimes::calcPrayerTimes(int day, int month, int year, double lat, double lon, double timeZone, ConventionAngle conv){

  // Variables for computing approximate solor coordinates (https://aa.usno.navy.mil/faq/sun_approx)
   double JD = convertToJulianDate(day, month, year); // Julian date
   const double d  = JD - 2451545.0; // Days since epoch "J2000.0"
   double g = norm360(357.529 + 0.98560028 * d); // Mean anomaly of the sun
   double q = norm360(280.459 + 0.98564736 * d); // Mean longitude of the sun
   double L = norm360(q + 1.915 * std::sin(deg2rad(g)) + 0.020 * std::sin(deg2rad(2.0 * g))); // Geocentric apparent ecliptic longitude of the sun
   double R = 1.00014 - 0.01671 * std::cos(deg2rad(g)) - 0.00014 * std::cos(deg2rad(2.0 * g)); // The distance of the sun from the Earth
   double e = 23.439 - 0.00000036 * d; // Mean obliquity of the ecliptic

   double y = std::cos(deg2rad(e)) * std::sin(deg2rad(L));
   double x = std::cos(deg2rad(L));
   double RAdeg = norm360(rad2deg(std::atan2(y, x)));
   double RA = RAdeg / 15.0; // The sun's right ascenion

   double D = rad2deg(std::asin(std::sin(deg2rad(e)) * std::sin(deg2rad(L)))); // The sun's declination
   double EqT = (q / 15.0) - RA; // The equation of time (hours)

  //Final calculations
   timeZone *= 1.0; // ensures timezone remains a double incase user types in an integer

   double dhuhrLocal  = 12.0 + timeZone - (lon / 15.0) - EqT;
   //Hour angles
    double H_fajr    = twilightFormula(conv.fajrAngle,lat,D);
    double H_sr_ss   = twilightFormula(-0.833,lat,D); //sunrise and sunset
    double H_asr1    = asrFormula(1.0,lat,D); //Shafi'i
    double H_asr2    = asrFormula(2.0,lat,D); //Hanafi

   //Assign timings to local variables
    this->fajr    = norm24(dhuhrLocal - H_fajr);
    this->sunrise = norm24(dhuhrLocal - H_sr_ss);
    this->dhuhr   = norm24(dhuhrLocal);
    this->asr1    = norm24(dhuhrLocal + H_asr1);
    this->asr2    = norm24(dhuhrLocal + H_asr2);
    this->maghrib = norm24(dhuhrLocal + H_sr_ss);

    //isha
    if(conv.ishaAngle == 99.0){ //Reserved ishaAngle 99 for Umm Al Qura, Umm Al Qura is the only convention angle with no isha angle since it uses manual offsets.
     double offsetMinutes = 90.0;
     // if(ramadan) { offsetMinutes = 120.0}; future feature
     double offsetHours = offsetMinutes/60.0;
     this->isha =  norm24(this->maghrib + offsetHours);
     }

    else{
     double H_isha    = twilightFormula(conv.ishaAngle,lat,D);
     this->isha    = norm24(dhuhrLocal + H_isha);
     }

   
   }
   



