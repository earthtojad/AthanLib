# AthanLib

**AthanLib** is a lightweight and dependency-free **C++ library** for calculating Islamic prayer times based on astronomical formulas.  
It provides accurate timings for Fajr, Dhuhr, Asr, Maghrib, and Isha anywhere in the world.

---

## 🌍 Features

- 📅 Compute daily prayer times for any date and location  
- 🧭 Handles latitude, longitude, and timezone offsets  
- ⚙️ Simple API — easy to integrate into any C++ project  
- 🪶 Lightweight — no external libraries or dependencies  
- 🧮 Based on established astronomical conventions  

---

## 🛠️ Installation

You can install or use **AthanLib** in several ways.

### Option 1: Clone the Repository

```bash
git clone https://github.com/earthtojad/AthanLib.git
cd AthanLib
```

Then compile the example program:

```bash
g++ example.cpp AthanLib.cpp -o athan
./athan
```

### Option 2: Add to an Existing Project

Copy the files `AthanLib.cpp` and `AthanLib.h` into your project’s source folder.

Then include the header:

```cpp
#include "AthanLib.h"
```

Compile with your own code:

```bash
g++ main.cpp AthanLib.cpp -o my_app
```

### Option 3: Use as a Git Submodule (for larger projects)

```bash
git submodule add https://github.com/earthtojad/AthanLib.git external/AthanLib
```

Then link it in your build system (e.g., CMake):

```cmake
add_subdirectory(external/AthanLib)
target_link_libraries(your_project PRIVATE AthanLib)
```

---

## 🚀 Example Usage

Here’s a simple example:

```cpp
#include "AthanLib.h"

int main() {
    // Example: Riyadh, Saudi Arabia (latitude, longitude, GMT+3)
    AthanLib athan(24.7136, 46.6753, 3);
    athan.printPrayerTimes(2025, 10, 6);
    return 0;
}
```

Output:
```
Date: 2025-10-06
Fajr: 04:38
Dhuhr: 11:42
Asr: 15:08
Maghrib: 17:52
Isha: 19:14
```

*(Times shown are illustrative.)*

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
3. Commit your changes and open a Pull Request 🚀

---

## 🧠 Credits

Developed by **[earthtojad](https://github.com/earthtojad)**  
Inspired by traditional Islamic prayer time algorithms and open-source astronomical research.

---

> “Indeed, prayer has been decreed upon the believers a decree of specified times.” — *Qur’an 4:103*
