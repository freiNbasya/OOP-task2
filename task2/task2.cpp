#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime> 
#include "product.h"
#include "generator.h"


class Electronics : public Product {
public:

    Electronics(int id, const std::string& n, double p, int quantity,
        const std::string& b, const std::string& m, double power)
        : Product(n, p, quantity), brand(move(b)), model(move(m)), powerConsumption(power) {}


    const std::string& getBrand() const { return brand; }
    void setBrand(const std::string& b) { brand = b; }

    const std::string& getModel() const { return model; }
    void setModel(const std::string& m) { model = m; }

    double getPowerConsumption() const { return powerConsumption; }
    void setPowerConsumption(double power) { powerConsumption = power; }

    void displayInfo() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << getName() << ", Quantity: " << getQuantityInStock() << ", Price: $" << getPrice();
        std::cout << ", Brand: " << getBrand() << ", Model: " << getModel() << ", Power Consumption: " << getPowerConsumption()  << " Watts" << std::endl;
    }
    void displayPowerConsumption() const {
        std::cout << "Power Consumption: " << powerConsumption << " Watts" << std::endl;
    }
private:
    std::string brand;
    std::string model;
    double powerConsumption;
};

class Books : public Product {
public:

    Books(int id, const std::string& n, double p, int quantity,
        const std::string& a, const std::string& g, const std::string& isbn)
        : Product(n, p, quantity), author(move(a)), genre(move(g)), ISBN(move(isbn)) {}


    const std::string& getAuthor() const { return author; }
    void setAuthor(const std::string& a) { author = a; }

    const std::string& getGenre() const { return genre; }
    void setGenre(const std::string& g) { genre = g; }

    const std::string& getISBN() const { return ISBN; }
    void setISBN(const std::string& isbn) { ISBN = isbn; }
    
    void displayInfo() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << getName() << ", Quantity: " << getQuantityInStock() << ", Price: $" << getPrice();
        std::cout << "Author: " << author << ", Genre: " << genre << ", ISBN: " << ISBN << std::endl;
    }

    void displayAuthor() const {
        std::cout << "Author: " << author << std::endl;
    }
private:
    std::string author;
    std::string genre;
    std::string ISBN;
};


class Clothing : public Product {
public:

    Clothing(int id, const std::string& n, double p, int quantity,
        const std::string& s, const std::string& c, const std::string& m)
        : Product(n, p, quantity), size(move(s)), color(move(c)), material(move(m)) {}


    const std::string& getSize() const { return size; }
    void setSize(const std::string& s) { size = s; }

    const std::string& getColor() const { return color; }
    void setColor(const std::string& c) { color = c; }

    const std::string& getMaterial() const { return material; }
    void setMaterial(const std::string& m) { material = m; }

    void displayInfo() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << getName() << ", Quantity: " << getQuantityInStock() << ", Price: $" << getPrice();
        std::cout << "Size: " << size << ", Color: " << color << ", Material: " << material << std::endl;
    }

    void displaySize() const {
        std::cout << "Size: " << size << std::endl;
    }
private:
    std::string size;
    std::string color;
    std::string material;
};

class Order {
public:
    Order(std::vector<Product*>& products)
        : orderID(Generator::generateID()), totalCost(0.0), orderStatus("Pending") {
        inputCustomerInformation();
    }

    void inputCustomerInformation() {
        std::cout << "Enter customer name: ";
        std::cin >> customer;
    }

    void orderProductsByID(std::vector<Product*>& products) {
        int productID;
        char continueOrdering;
        do {
            std::cout << "Enter Product ID to add to the order: ";
            std::cin >> productID;

            Product* selectedProduct = nullptr;
            for (const auto& product : products) {
                if (product->getProductID() == productID) {
                    selectedProduct = product;
                    break;
                }
            }

            if (selectedProduct) {
                orderedProducts.push_back(selectedProduct);
                std::cout << "Product added to the order.\n";
                calculateTotalCost(selectedProduct->getPrice());
            }
            else {
                std::cout << "Product not found.\n";
            }

            std::cout << "Do you want to continue ordering? (y/n): ";
            std::cin >> continueOrdering;
        } while (continueOrdering == 'y' || continueOrdering == 'Y');

    }

    void calculateTotalCost(double price) {
        totalCost += price;

    }

    void checkOrder() const {
        std::cout << "\nCustomer: " << customer << "\nOrdered Products:\n";
        for (const auto& product : orderedProducts) {
            
        }
        std::cout << "Total Cost: $" << totalCost << std::endl;
    }

    void approveOrder() {
        std::cout << "Order confirmed. Total cost: $" << totalCost << std::endl;


        for (const auto& product : orderedProducts) {
            int currentQuantity = product->getQuantityInStock();
            product->setQuantityInStock(currentQuantity - 1);
        }

        orderStatus = "Approved";
        orderedProducts.clear();
        totalCost = 0.0;
        orderStatus = "Pending";
        inputCustomerInformation();
    }

private:
    int orderID;
    std::string customer;
    std::vector<Product*> orderedProducts;
    double totalCost;
    std::string orderStatus;
};

class ProductCatalog {
private:
    std::vector<Product*>& products;

public:
    ProductCatalog(std::vector<Product*>& products)
        : products(products) {}

    void addProduct(Product* product) {
        products.push_back(product);
    }


    void updateProductDetails(int productID, double newPrice, int newQuantity) {
        for (auto& product : products) {
            if (product->getProductID() == productID) {
                product->setPrice(newPrice);
                product->setQuantityInStock(newQuantity);
                
                break;
            }
        }
    }


    void removeProduct(int productID) {
        products.erase(std::remove_if(products.begin(), products.end(), [productID](Product* p) { return p->getProductID() == productID; }), products.end());
    }


    void viewAllProducts() const {
        for (const auto& product : products) {
            if (auto* electronics = dynamic_cast<Electronics*>(product)) {
                electronics->displayInfo();
            }
            else if (auto* book = dynamic_cast<Books*>(product)) {
                book->displayInfo();
            }
            else if (auto* clothing = dynamic_cast<Clothing*>(product)) {
                clothing->displayInfo();
            }
            std::cout << std::endl;
        }
    }
};

class Inventory {
private:
    std::vector<Product*>& products;
    int lowStockThreshold;

public:
    Inventory(std::vector<Product*>& products, int lowStockThreshold)
        : products(products), lowStockThreshold(lowStockThreshold) {}
    void manageStock(int productID, int quantity) {
        for (auto& product : products) {
            if (product->getProductID() == productID) {
                int currentQuantity = product->getQuantityInStock();
                if (currentQuantity + quantity >= 0) {
                    product->setQuantityInStock(currentQuantity + quantity);
                }
                break;
            }
        }
    }



    std::vector<Product*> generateRestockingList() const {
        std::vector<Product*> restockingList;
        for (const auto& product : products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                restockingList.push_back(product);
            }
        }
        return restockingList;
    }
};

class ConfigReader {
public:

    static void readConfig(const std::string& filename, std::vector<Product*>& products) {
        std::ifstream configFile(filename);

        if (!configFile.is_open()) {
            std::cerr << "Error: Unable to open config file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line.empty() || line[0] == '#') {

                continue;
            }

            std::vector<std::string> tokens = split(line, ',');



            std::string& productType = tokens[0];
            std::string& productName = tokens[1];
            double price = std::stod(tokens[2]);
            int quantity = std::stoi(tokens[3]);

            if (productType == "Electronics") {
                std::string& brand = tokens[4];
                std::string& model = tokens[5];
                double powerConsumption = std::stod(tokens[6]);
                products.push_back(new Electronics(0, productName, price, quantity, brand, model, powerConsumption));
            }
            else if (productType == "Books") {
                std::string& author = tokens[4];
                std::string& genre = tokens[5];
                std::string& ISBN = tokens[6];
                products.push_back(new Books(0, productName, price, quantity, author, genre, ISBN));
            }
            else if (productType == "Clothing") {
                std::string& size = tokens[4];
                std::string& color = tokens[5];
                std::string& material = tokens[6];
                products.push_back(new Clothing(0, productName, price, quantity, size, color, material));
            }
            else {
                std::cerr << "Error: Unknown product type or invalid format." << std::endl;
            }
        }

        configFile.close();
    }

private:

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream tokenStream(s);
        std::string token;
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

int main() {
    std::vector<Product*> products;
    ConfigReader::readConfig("C:/Labs_Kse/OOP/task2/config.txt", products);

    ProductCatalog catalog(products);
    Inventory inventory(products, 10);
    Order currentOrder(products);

    int choice;

    do {
        std::cout << "\nProduct Management System \n";
        std::cout << "1. View Products\n";
        std::cout << "2. Add Product to Order\n";
        std::cout << "3. View Order\n";
        std::cout << "4. Checkout\n";
        std::cout << "5. View Product Catalog\n";
        std::cout << "6. Update Product Details\n";
        std::cout << "7. Remove Product from Catalog\n";
        std::cout << "8. Restock Product\n";
        std::cout << "9. Generate Restocking List\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "\n View Product Catalog \n";
            catalog.viewAllProducts();
        }
              break;
        case 2:
        {
            currentOrder.orderProductsByID(products);
        }
        break;
        case 3:
        {
            std::cout << "\n View Order \n";
            currentOrder.checkOrder();
        }
        break;
        case 4:
        {
            std::cout << "\n Checkout \n";
            currentOrder.approveOrder();

        }
        break;
        case 5: {
            std::cout << "\n View Product Catalog \n";
            catalog.viewAllProducts();
        }
              break;
        case 6: {
            std::cout << "\n Update Product Details \n";
            int updateProductID;
            double newPrice;
            int newQuantity;

            std::cout << "Enter Product ID to update: ";
            std::cin >> updateProductID;

            std::cout << "Enter new price: ";
            std::cin >> newPrice;

            std::cout << "Enter new quantity: ";
            std::cin >> newQuantity;

            catalog.updateProductDetails(updateProductID, newPrice, newQuantity);
            std::cout << "Product details updated.\n";
        }
              break;
        case 7: {
            std::cout << "\n Remove Product from Catalog \n";
            int removeProductID;
            std::cout << "Enter Product ID to remove: ";
            std::cin >> removeProductID;
            catalog.removeProduct(removeProductID);
            std::cout << "Product removed from the catalog.\n";
        }
              break;
        case 8:
        {
            std::cout << "\n Restock Product \n";
            int restockProductId;
            int quantityRestock;
            std::cout << "Enter Product ID to restock: ";
            std::cin >> restockProductId;
            std::cout << "Enter how much to restock: ";
            std::cin >> quantityRestock;
            inventory.manageStock(restockProductId, quantityRestock);
        }
        break;
        case 9:
        {
            std::cout << "\n Generate Restocking List \n";
            auto restockingList = inventory.generateRestockingList();
            std::cout << "Products needing restocking:\n";
            for (const auto& product : restockingList) {
                std::cout << "Product ID: " << product->getProductID() << ", Name: " << product->getName() << std::endl;
            }
        }
        break;
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 0);

    for (auto& product : products) {
        delete product;
    }

    return 0;
}

