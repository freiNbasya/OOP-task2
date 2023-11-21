#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime> 

class Product {
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
};

class Electronics : public Product {
public:

    Electronics(int id, const std::string& n, double p, int quantity,
        const std::string& b, const std::string& m, double power)
        : Product(n, p, quantity), brand(b), model(m), powerConsumption(power) {}


    const std::string& getBrand() const { return brand; }
    void setBrand(const std::string& b) { brand = b; }

    const std::string& getModel() const { return model; }
    void setModel(const std::string& m) { model = m; }

    double getPowerConsumption() const { return powerConsumption; }
    void setPowerConsumption(double power) { powerConsumption = power; }


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
        : Product(n, p, quantity), author(a), genre(g), ISBN(isbn) {}


    const std::string& getAuthor() const { return author; }
    void setAuthor(const std::string& a) { author = a; }

    const std::string& getGenre() const { return genre; }
    void setGenre(const std::string& g) { genre = g; }

    const std::string& getISBN() const { return ISBN; }
    void setISBN(const std::string& isbn) { ISBN = isbn; }


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
        : Product(n, p, quantity), size(s), color(c), material(m) {}


    const std::string& getSize() const { return size; }
    void setSize(const std::string& s) { size = s; }

    const std::string& getColor() const { return color; }
    void setColor(const std::string& c) { color = c; }

    const std::string& getMaterial() const { return material; }
    void setMaterial(const std::string& m) { material = m; }


    void displaySize() const {
        std::cout << "Size: " << size << std::endl;
    }
private:
    std::string size;
    std::string color;
    std::string material;
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



            std::string productType = tokens[0];
            std::string productName = tokens[1];
            double price = std::stod(tokens[2]);
            int quantity = std::stoi(tokens[3]);

            if (productType == "Electronics") {
                std::string brand = tokens[4];
                std::string model = tokens[5];
                double powerConsumption = std::stod(tokens[6]);
                products.push_back(new Electronics(0, productName, price, quantity, brand, model, powerConsumption));
            }
            else if (productType == "Books") {
                std::string author = tokens[4];
                std::string genre = tokens[5];
                std::string ISBN = tokens[6];
                products.push_back(new Books(0, productName, price, quantity, author, genre, ISBN));
            }
            else if (productType == "Clothing") {
                std::string size = tokens[4];
                std::string color = tokens[5];
                std::string material = tokens[6];
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

    return 0;
}

