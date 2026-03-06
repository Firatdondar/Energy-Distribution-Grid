#ifndef ENERGY_GRID_HPP
#define ENERGY_GRID_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Country.hpp"

/**
 * @brief Manages the grid network, handles data parsing, energy trading logic, and cost calculations.
 */
class EnergyGrid {
private:
    Country* countries;          
    int** distanceMatrix;    
    int countryCount;
    int capacity;

    std::string* splitString(const std::string& line, char delimiter, int& partCount);

public:
    EnergyGrid();  
    ~EnergyGrid(); 

    void loadData(const std::string& countryFile, const std::string& linesFile); 
    void calculateNetEnergy(); 
    double calculatePurchaseCost(double amount, double price, int distance);
    double calculatePenaltyCost(double amount, double coefficient);
    
    void sortByProfitability(); 

    void analyzeSystem(); 
    void generateReport();         
};

#endif