# European Energy Distribution Simulator

An object-oriented C++ simulation designed to analyze and optimize energy distribution networks across European countries using custom graph structures and financial trade logic.

## 📌 Project Overview
This project simulates an international power grid where countries experience either energy surpluses or deficits. The system parses country data and inter-country distance matrices to determine the most cost-effective energy trading routes. If an energy deficit cannot be resolved through trading, a country must pay a penalty cost. Finally, the system ranks all countries based on their net financial profit or loss.

## ⚙️ Core Features
* **Custom Data Parsing:** Reads and processes complex relational data (`countries.txt` and `power_lines.txt`) without relying on standard string stream libraries, demonstrating low-level string manipulation.
* **Graph-Based Network:** Represents the energy grid using a dynamic 2D distance matrix.
* **Financial Optimization:** Calculates trade costs based on distance and unit price, prioritizing the cheapest available energy source to resolve deficits.
* **Profitability Ranking:** Implements a custom Selection Sort algorithm to rank countries from most profitable to the largest financial deficit.
* **Dynamic Memory Management:** Strictly utilizes pointers and dynamic arrays (`new`/`delete`) for data storage, avoiding STL containers to demonstrate memory lifecycle control.

## 🛠️ Technologies & Build System
* **Language:** C++ (Standard 17)
* **Architecture:** Object-Oriented Programming (OOP)
* **Build System:** CMake
* **Compiler:** GCC (MinGW-w64)

## 🚀 Installation & Execution

The project relies on CMake for a compiler-agnostic build process.

### Build Steps (Terminal)
1. Clone the repository:
   ```bash
   git clone [https://github.com/your-username/EnergyDistributionGrid.git](https://github.com/your-username/EnergyDistributionGrid.git)
   cd EnergyDistributionGrid