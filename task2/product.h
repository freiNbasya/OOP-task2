
#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Product {
public:
    Product(const std::string& n, double p, int quantity);

    int getProductID() const;
    void setProductID(int id);

    const std::string& getName() const;
    void setName(const std::string& n);

    double getPrice() const;
    void setPrice(double p);

    int getQuantityInStock() const;
    void setQuantityInStock(int quantity);

    virtual void displayInfo() const;

    double calculateTotalCost() const;
    virtual ~Product();

private:
    int productID;
    std::string name;
    double price;
    int quantityInStock;
};
