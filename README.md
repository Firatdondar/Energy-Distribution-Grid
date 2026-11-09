# ⚡ European Energy Distribution Grid Simulator

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-064F8C?logo=cmake&logoColor=white)
![Domain](https://img.shields.io/badge/Domain-Power%20Grid%20Optimization-yellow)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

An object-oriented **C++17** simulation engine that models cross-border electricity distribution and financial trade across European power grids. It pairs surplus-producing nations with deficit nations along minimum-cost transmission corridors and ranks national grid profitability.

---

## 📌 Overview

National power grids frequently experience either generation surpluses or consumption deficits. This simulator ingests country-level production/consumption metrics (`data/countries.txt`) and an inter-country transmission distance matrix (`data/power_lines.txt`) to:
1. Compute net energy balance ($\text{Net} = \text{Production} - \text{Consumption}$) for each country.
2. Match energy-deficit countries with the most cost-effective surplus exporters based on distance and unit energy tariff.
3. Apply regulatory penalty costs when deficits cannot be fully satisfied through cross-border trade.
4. Rank all participating nations from highest net profit to largest financial deficit.

---

## ✨ Key Features

- **2D Adjacency Matrix Grid:** Models cross-border high-voltage transmission distances between European countries.
- **Greedy Trade Cost Optimizer:** Evaluates unit price and transmission distance to minimize import expenditure for deficit nations.
- **STL-Free Memory Architecture:** Uses custom raw pointer arrays (`new`/`delete`) and low-level character parsing without STL containers.
- **Automated Financial Ledger:** Generates `result.txt` with trade transactions, penalty assessments, and Selection-Sorted profitability rankings.

---

## 🗂️ Project Structure

```text
Energy-Distribution-Grid/
├── data/
│   ├── countries.txt        # Country production, consumption, tariffs & penalties
│   └── power_lines.txt      # Inter-country transmission distance matrix
├── include/
│   ├── Country.hpp          # Country entity & energy balance state
│   └── EnergyGrid.hpp       # Grid matrix, trade matching & sorting engine
├── src/
│   └── main.cpp             # Simulation entry point
├── CMakeLists.txt           # Cross-platform CMake build configuration
├── LICENSE                  # MIT License
└── README.md                # Project documentation
```

---

## 🚀 Build & Run Instructions

```bash
git clone https://github.com/Firatdondar/Energy-Distribution-Grid.git
cd Energy-Distribution-Grid
mkdir build && cd build
cmake ..
cmake --build .
./EnergyDistributionGrid
```

---

## 📄 License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.
