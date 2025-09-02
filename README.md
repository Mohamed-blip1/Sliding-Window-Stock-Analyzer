# 📈 Sliding Window Stock Analyzer

A C++ console application that simulates stock price tracking and performs real-time statistical analysis using a sliding window.

---

## 🚀 Features

- Simulates random stock prices over time
- Calculates:
  - Maximum
  - Minimum
  - Median
  - Average
- Supports sliding window analysis over any given window size
- Finds maximum stock price in the last **N minutes**
- Cleans old price data to limit memory usage
- Input validation and error handling

---

## 🛠️ Technologies

- **C++17**
- Standard Library (`<chrono>`, `<deque>`, `<vector>`, `<random>`, etc.)
- Command-line interface (CLI)

---

## 📦 How to Compile

Make sure you have `g++` installed.

```bash
g++ -std=c++17 main.cpp company.cpp -o analyzer.exe

````

Then run:

```
./analyzer.exe

```

---

## 📋 Menu Example

```
======= Sliding Window Stock menu =======
Menu:
1 - Reload prices
2 - Sliding window
3 - Max stock price in last N minutes
4 - Clean old prices
0 - Exit

```

---

## 🧪 Sample Output

```
Enter window size: 5

-----My Company-----
Max: 287
Min: 110
Med: 190
Avg: 185.6
...

```

---

## 📁 Project Structure

```
.
├── main.cpp
├── company.cpp
├── company.h
├── utils.h
└── README.md

```
---

## 🧑‍💻 Author

**Mohamed-blip1**

Feel free to connect or contribute!
