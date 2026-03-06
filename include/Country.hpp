#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <string>

/**
 * @brief Represents a node (country) in the energy grid with its production, consumption, and financial status.
 */
class Country {
private:
    int id;
    std::string name;
    double production;          
    double consumption;         
    double penaltyCoefficient;
    double sellingPrice;     
    
    double currentNetEnergy; 
    double totalCost;   
    double profitLoss;        

public:
    Country() : id(0), production(0), consumption(0), penaltyCoefficient(0), sellingPrice(0),
                currentNetEnergy(0), totalCost(0), profitLoss(0) {}

    void setData(int _id, const std::string& _name, double _prod, double _cons, double _penalty, double _price) {
        id = _id;
        name = _name;
        production = _prod;
        consumption = _cons;
        penaltyCoefficient = _penalty;
        sellingPrice = _price;
        currentNetEnergy = production - consumption;
    }

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getProduction() const { return production; }
    double getConsumption() const { return consumption; }
    double getNetEnergy() const { return currentNetEnergy; } 
    double getSellingPrice() const { return sellingPrice; }
    double getPenaltyCoefficient() const { return penaltyCoefficient; }
    double getProfitLoss() const { return profitLoss; }

    // Modifiers
    void setNetEnergy(double value) { currentNetEnergy = value; }

    void addCost(double amount) {
        totalCost += amount;
        profitLoss -= amount; 
    }

    void addRevenue(double amount) {
        profitLoss += amount; 
    }
};

#endif