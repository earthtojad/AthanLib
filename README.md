# AthanLib

**AthanLib** is a lightweight and dependency-free **C++ library** for calculating Islamic prayer times based on astronomical formulas.  
It provides accurate timings for Fajr, Dhuhr, Asr, Maghrib, and Isha anywhere in the world.

---

## 🌍 Features

- 📅 Compute daily prayer times for any date and location  
- 🧭 Handles latitude, longitude, and timezone offsets  
- ⚙️ Simple API, easy to integrate into any C++ project  
- 🪶 Lightweight, no external libraries or dependencies  
- 🧮 Based on well known astronomical conventions used around the world and in many countries  

---


## ⚙️ Installation

You don’t need to install anything special, just clone it and place the files in whatever project you're using it for.

### 🧭 1. Download

```bash
git clone https://github.com/earthtojad/AthanLib.git
cd AthanLib
```



### 2. Use in Your Projects
Copy these two files into your project:
```
AthanLib.cpp
AthanLib.h
```

Then include it in your code:
```cpp
#include "AthanLib.h"
```

That’s it! 🎉

---

## 🚀 Example Usage

Here’s a simple example:

```cpp
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
    std::cout << "Fajr:     " << getTime(today.fajr) << std::endl;
    std::cout << "Sunrise:  " << getTime(today.sunrise) << std::endl;
    std::cout << "Dhuhr:    " << getTime(today.dhuhr) << std::endl;
    std::cout << "Asr (Shafi'i):  " << getTime(today.asr1) << std::endl;
    std::cout << "Asr (Hanafi):   " << getTime(today.asr2) << std::endl;
    std::cout << "Maghrib:  " << getTime(today.maghrib) << std::endl;
    std::cout << "Isha:     " << getTime(today.isha) << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return 0;
}
```

Output:
```
Date: 6/10/2025
Location: 34.0549, -118.243 (UTC-7)
----------------------------------------
Fajr:     05:43
Sunrise:  06:51
Dhuhr:    12:41
Asr (Shafi'i):  16:00
Asr (Hanafi):   16:49
Maghrib:  18:31
Isha:     19:39
----------------------------------------

```


---

## 📦 File Structure

```
AthanLib/
 ├── AthanLib.cpp      # Core calculation code
 ├── AthanLib.h        # Header file
 ├── example.cpp       # Example usage
 └── LICENSE           # GPL-3.0 license
```

---

## ⚖️ License

**AthanLib** is released under the **GPL-3.0 License**.  
You are free to use, modify, and redistribute it, provided that your project also uses the GPL-3.0 license.

---

## 🤝 Contributing

Contributions are welcome!  
If you find bugs, want to add regional calculation methods, or improve documentation:

1. Fork the repo  
2. Create a new branch:  
   ```bash
   git checkout -b feature/my-improvement
   ```
3. Commit your changes and open a Pull Request 

---

## Credits

Developed by **[earthtojad](https://github.com/earthtojad)**  
Inspired by traditional Islamic prayer time algorithms and open-source astronomical research.

---

> “Indeed, prayer has been decreed upon the believers a decree of specified times.” — *Qur’an 4:103*
