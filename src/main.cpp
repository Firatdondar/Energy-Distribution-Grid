#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include "../include/EnergyGrid.hpp"

using namespace std;

EnergyGrid::EnergyGrid() : countryCount(0), capacity(50) {
    countries = new Country[capacity]; 
    
    distanceMatrix = new int*[capacity];
    for(int i = 0; i < capacity; i++) {
        distanceMatrix[i] = new int[capacity];
        for(int j = 0; j < capacity; j++) {
            distanceMatrix[i][j] = 0;
        }
    }
}

EnergyGrid::~EnergyGrid() {
    delete[] countries;
    for(int i = 0; i < capacity; i++) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

string* EnergyGrid::splitString(const string& line, char delimiter, int& partCount) {
    string* parts = new string[capacity]; 
    partCount = 0;
    string temp = "";

    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == delimiter) {
            if (partCount < capacity) parts[partCount++] = temp; 
            temp = "";
        } else {
            temp += line[i]; 
        }
    }
    if (partCount < capacity) parts[partCount++] = temp; 
    return parts;
}

void EnergyGrid::loadData(const string& countryFile, const string& linesFile) {
    ifstream fileCountry(countryFile);
    if (!fileCountry.is_open()) {
        cerr << "ERROR: Cannot open " << countryFile << endl; return;
    }

    string line;
    getline(fileCountry, line); // Skip header

    int id;
    string name;
    double prod, cons, penalty, price;

    while (fileCountry >> id >> name >> prod >> cons >> penalty >> price) {
        if (countryCount < capacity) {
            countries[countryCount].setData(id, name, prod, cons, penalty, price);
            countryCount++;
        }
    }
    fileCountry.close();
    cout << "INFO: " << countryCount << " countries loaded." << endl;

    ifstream fileLines(linesFile);
    if (!fileLines.is_open()) {
        cerr << "ERROR: Cannot open " << linesFile << endl; return;
    }

    int rowIndex = 0;
    while (getline(fileLines, line) && rowIndex < countryCount) {
        int colCount = 0;
        string* cols = splitString(line, ',', colCount); 

        for (int j = 0; j < colCount && j < countryCount; j++) {
            string distStr = cols[j];
            if (distStr == "-" || distStr == "") {
                distanceMatrix[rowIndex][j] = 0;
            } else {
                distanceMatrix[rowIndex][j] = atoi(distStr.c_str()); 
            }
        }
        delete[] cols; 
        rowIndex++;
    }
    fileLines.close();
    cout << "INFO: Energy grid matrix initialized." << endl;
}

void EnergyGrid::calculateNetEnergy() {
    for(int i = 0; i < countryCount; i++) {
        double net = countries[i].getProduction() - countries[i].getConsumption();
        countries[i].setNetEnergy(net);
    }
}

double EnergyGrid::calculatePurchaseCost(double amount, double price, int distance) {
    return amount * price * ((double)distance / 100.0);
}

double EnergyGrid::calculatePenaltyCost(double amount, double coefficient) {
    return amount * coefficient;
}

/**
 * @brief Sorts countries based on their profit/loss margin using Selection Sort.
 */
void EnergyGrid::sortByProfitability() {
    for (int i = 0; i < countryCount - 1; i++) {
        int maxIndex = i; 
        
        for (int j = i + 1; j < countryCount; j++) {
            if (countries[j].getProfitLoss() > countries[maxIndex].getProfitLoss()) {
                maxIndex = j;
            }
        }
        
        if (maxIndex != i) {
            Country temp = countries[i];
            countries[i] = countries[maxIndex];
            countries[maxIndex] = temp;
        }
    }
}

void EnergyGrid::analyzeSystem() {
    calculateNetEnergy(); 
    
    ofstream costFile("financial_analysis.txt");
    costFile << fixed << setprecision(2);
    cout << fixed << setprecision(2);

    cout << "\n--- GRID ANALYSIS STARTED ---" << endl;

    for (int i = 0; i < countryCount; i++) {
        if (countries[i].getNetEnergy() < 0) { 
            double deficit = -countries[i].getNetEnergy(); 
            double remainingDeficit = deficit;
            
            cout << "--------------------------------" << endl;
            cout << "NODE: " << countries[i].getName() << " | Deficit: " << deficit << " GWh" << endl;
            
            costFile << "--------------------------------" << endl;
            costFile << "NODE: " << countries[i].getName() << "\nEnergy Deficit: " << deficit << " GWh\n";

            while (remainingDeficit > 0.001) {
                int bestNeighbor = -1;
                double lowestPrice = 999999999.0; 

                for (int j = 0; j < countryCount; j++) {
                    if (distanceMatrix[i][j] > 0 && countries[j].getNetEnergy() > 0) {
                        double unitCost = calculatePurchaseCost(1, countries[j].getSellingPrice(), distanceMatrix[i][j]);
                        
                        if (unitCost < lowestPrice) {
                            lowestPrice = unitCost;
                            bestNeighbor = j;
                        }
                    }
                }

                double penaltyRate = countries[i].getPenaltyCoefficient();

                if (bestNeighbor != -1 && lowestPrice < penaltyRate) {
                    double neighborSurplus = countries[bestNeighbor].getNetEnergy();
                    double amountToBuy = (remainingDeficit < neighborSurplus) ? remainingDeficit : neighborSurplus;

                    double tradeCost = calculatePurchaseCost(amountToBuy, countries[bestNeighbor].getSellingPrice(), distanceMatrix[i][bestNeighbor]);
                    
                    countries[i].addCost(tradeCost);
                    countries[bestNeighbor].addRevenue(tradeCost); 
                    countries[bestNeighbor].setNetEnergy(countries[bestNeighbor].getNetEnergy() - amountToBuy);

                    remainingDeficit -= amountToBuy;
                    
                    cout << " * Trade Executed: Bought from " << countries[bestNeighbor].getName() 
                         << " (" << amountToBuy << " GWh). Cost: " << tradeCost << " EUR" << endl;
                    costFile << " * Trade: Bought from " << countries[bestNeighbor].getName() 
                             << " (" << amountToBuy << " GWh). Cost: " << tradeCost << " EUR\n";

                } else {
                    double penaltyCost = calculatePenaltyCost(remainingDeficit, countries[i].getPenaltyCoefficient());
                    countries[i].addCost(penaltyCost);
                    
                    cout << " * Deficit Penalty: Remaining " << remainingDeficit << " GWh unresolved. Cost: " 
                         << penaltyCost << " EUR" << endl;
                    costFile << " * Penalty: " << remainingDeficit << " GWh unresolved. Cost: " 
                             << penaltyCost << " EUR\n";
                                   
                    remainingDeficit = 0; 
                }
            }
        }
    }
    costFile.close();
    cout << "\nINFO: Analysis complete. Detailed log saved to 'financial_analysis.txt'." << endl;
}

void EnergyGrid::generateReport() {
    sortByProfitability(); 

    ofstream reportFile("final_report.txt");
    cout << fixed << setprecision(0); 
    reportFile << fixed << setprecision(0);

    cout << "\n--- GLOBAL FINANCIAL REPORT (Profit -> Loss) ---" << endl;
    reportFile << "--- GLOBAL FINANCIAL REPORT ---\n";

    for (int i = 0; i < countryCount; i++) {
        cout << i + 1 << ". " << countries[i].getName() 
             << " \t| Balance: " << countries[i].getProfitLoss() << " EUR" << endl;
             
        reportFile << i + 1 << ". " << countries[i].getName() 
                   << " \t| Balance: " << countries[i].getProfitLoss() << " EUR\n";
    }
    reportFile.close();
    cout << "INFO: Ranked list saved to 'final_report.txt'." << endl;
}

int main() {
    EnergyGrid grid;
    
    cout << "===========================================" << endl;
    cout << "   EUROPEAN ENERGY DISTRIBUTION SIMULATOR" << endl;
    cout << "===========================================" << endl;

    grid.loadData("data/countries.txt", "data/power_lines.txt");
    grid.analyzeSystem();
    grid.generateReport();

    return 0;
}