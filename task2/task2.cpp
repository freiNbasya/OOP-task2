#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime> 

class Product {
private:
    int productID;
    int generateRandomID() {
        static bool seedInitialized = false;
        if (!seedInitialized) {
            std::srand(std::time(0));
            seedInitialized = true;
        }
        return std::rand();
    }
    std::string name;
    double price;
    int quantityInStock;

public:
  
    Product( const std::string& n, double p, int quantity)
        : productID(generateRandomID()), name(n), price(p), quantityInStock(quantity) {}

   
    int getProductID() const { return productID; }
    void setProductID(int id) { productID = id; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }

    int getQuantityInStock() const { return quantityInStock; }
    void setQuantityInStock(int quantity) { quantityInStock = quantity; }

    double calculateTotalCost() const {
        return price * quantityInStock;
    }
    virtual ~Product() {}
};


int main() {

    return 0;
}

