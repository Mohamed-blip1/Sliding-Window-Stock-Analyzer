# Sliding Window Stock Analyzer

A C++ program that simulates stock price updates and provides statistical analysis using a **sliding window** technique.  
It can compute maximum, minimum, median, and average stock prices over a user-defined time window.

---

## Features
- 📈 Simulate stock price updates with random values.
- ⏳ Analyze stock prices over sliding windows of customizable size.
- 🔎 Query the maximum stock price within the last **N minutes**.
- 🧹 clean up prices older than a defined limit.
- 📝 Rename companies and manage multiple companies interactively.

---

## Project Structure
```
📁 Project Structure
project/
├── .gitignore
├── README.md                 # This file
└── Social_Network_Mini/
    ├── include/              # Header files
    │   ├── companies.h       
    │   ├── company.h.h       
    │   ├── menu.h            
    │   └── utils.h           # Utilities

    ├── src/                  # Source files
    │   ├── companies.cpp
    │   ├── company.cpp
    │   ├── menu.cpp
    │   └── utils.cpp

    ├── main.cpp              # Program entry point
    └── Makefile              # Build configuration
````

---

## Build Instructions

### Prerequisites
- A C++17 (or later) compiler (e.g. `g++`, `clang++`, MSVC).
- A terminal or shell.

### Compile & Run
```bash
# Navigate to project directory
cd path/to/Sliding-Window-Stock-Analyzer/project

# Compile (example with g++)
g++ -std=c++17 main.cpp menu.cpp companies.cpp company.cpp utils.cpp -o main.exe

# Run
./main.exe   # (Linux/macOS)
main.exe     # (Windows)
````

---

## Example Usage

Once running, you’ll see a menu with options like:

* Add a company
* Enter a company
* Analyze with sliding window
* Query max price in last N minutes
* Clean old prices
* Rename company
* Exit

---

## License

MIT License — free to use and modify.
