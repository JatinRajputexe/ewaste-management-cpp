# E-Waste Management System (C++)

A C++ OOP console application that manages the collection, categorization, recycling and disposal of electronic waste. It supports **SDG 12** (Responsible Consumption and Production) and **SDG 13** (Climate Action).

## Features
- Abstract base class `EWaste` with derived classes `Computer`, `Mobile`, `Battery` and `CRTMonitor`
- Runtime polymorphism through virtual functions
- Identifies recyclable and non-recyclable items
- Calculates total recoverable weight and recycling rate
- Saves and loads records from a file (`ewaste.txt`)
- Prints a category-wise summary report

## Concepts Used
Classes and objects, abstract classes, inheritance, virtual functions, `vector`, `map`, `unique_ptr`, file streams.

## Recycling Rates Used
| Category | Recyclable fraction |
|---|---|
| Computer | 85% |
| Mobile | 80% |
| Battery | 60% |
| CRTMonitor | 0% (non-recyclable) |

## How to Run
Requires a C++11 (or later) compiler such as g++.
```bash
g++ -std=c++11 main.cpp -o ewaste
./ewaste
```
On Windows, run `ewaste.exe`.

## Sample Output
```
101 Desktop [Computer] 9.5 kg - Recyclable
104 CRT17in [CRTMonitor] 14 kg - Non-recyclable
...
--- Summary ---
Battery: 0.45 kg
CRTMonitor: 14 kg
Computer: 11.8 kg
Mobile: 0.3 kg
Recyclable items: 5, Non-recyclable: 1
Total weight: 26.55 kg
Recoverable weight: 10.54 kg
Recycling rate: 39.6987 %
```

## Possible Improvements
- Menu-driven input instead of fixed sample data
- Exception handling for invalid input
- A new category such as `Television`

## License
MIT
