#include "product.h"
#include "generator.h"


Product::Product(const std::string& n, double p, int quantity)
        : productID(Generator::generateID()), name(move(n)), price(p), quantityInStock(quantity) {}


    int Product::getProductID() const { return productID; }
    void Product::setProductID(int id) { productID = id; }

    const std::string& Product::getName() const { return name; }
    void Product::setName(const std::string& n) { name = n; }

    double Product::getPrice() const { return price; }
    void Product::setPrice(double p) { price = p; }

    int Product::getQuantityInStock() const { return quantityInStock; }
    void Product::setQuantityInStock(int quantity) { quantityInStock = quantity; }

    double Product::calculateTotalCost() const {
        return price * quantityInStock;
    }
    Product::~Product() {}


