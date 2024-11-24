#include <iostream>
#include <string>
#include <vector>
#include <memory> // Pentru smart pointers
#include <utility> // Pentru std::move

class Dish {
private:
    std::string name;
    double price;
    bool isAvailable;

public:
    // Constructor de inițializare
    Dish(const std::string& name = "Unnamed Dish", double price = 0.0, bool isAvailable = true)
        : name(name), price(price), isAvailable(isAvailable) {
        std::cout << "Dish created: " << name << " - Price: $" << price << std::endl;
    }

    // Constructor de copiere
    Dish(const Dish& other)
        : name(other.name), price(other.price), isAvailable(other.isAvailable) {
        std::cout << "Copy constructor called for: " << name << std::endl;
    }

    // Constructor de mutare
    Dish(Dish&& other) noexcept
        : name(std::move(other.name)), price(other.price), isAvailable(other.isAvailable) {
        std::cout << "Move constructor called for: " << name << std::endl;
        other.price = 0.0;
        other.isAvailable = false;
    }

    // Operator "=" de copiere
    Dish& operator=(const Dish& other) {
        if (this == &other) return *this;
        name = other.name;
        price = other.price;
        isAvailable = other.isAvailable;
        std::cout << "Copy assignment operator called for: " << name << std::endl;
        return *this;
    }

    // Operator "=" de mutare
    Dish& operator=(Dish&& other) noexcept {
        if (this == &other) return *this;
        name = std::move(other.name);
        price = other.price;
        isAvailable = other.isAvailable;
        std::cout << "Move assignment operator called for: " << name << std::endl;
        other.price = 0.0;
        other.isAvailable = false;
        return *this;
    }

    // Getter și Setter
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }

    void setPrice(double price) { this->price = price; }
    double getPrice() const { return price; }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }
    bool getAvailability() const { return isAvailable; }

    // Metode supraincarcate
    virtual void displayInfo() const { // Marcat virtual pentru polimorfism
        std::cout << "Dish: " << name << " - Price: $" << price
                  << (isAvailable ? " (Available)" : " (Not Available)") << std::endl;
    }

    virtual ~Dish() {
    if (name != "") {
        std::cout << "Dish \"" << name << "\" destroyed (in destructor)" << std::endl;
    } else {
        std::cout << "Dish moved, no name to display (in destructor)" << std::endl;
    }
}

};

class SpecialDish : public Dish {
private:
    std::string specialNote;

public:
    SpecialDish(const std::string& name, double price, const std::string& note, bool isAvailable = true)
        : Dish(name, price, isAvailable), specialNote(note) {
        std::cout << "SpecialDish created: " << name << " - Note: " << specialNote << std::endl;
    }

    void displayInfo() const override {
        std::cout << "Special Dish: " << getName() << " - Price: $" << getPrice()
                  << " - Note: " << specialNote
                  << (getAvailability() ? " (Available)" : " (Not Available)") << std::endl;
    }

    ~SpecialDish() {
        std::cout << "SpecialDish \"" << getName() << "\" destroyed (in destructor)" << std::endl;
    }
};

class Restaurant {
private:
    std::string name;
    std::vector<std::unique_ptr<Dish>> menu; // Smart pointers pentru gestionarea memoriei

public:
    Restaurant(const std::string& name = "Unnamed Restaurant") : name(name) {
        std::cout << "Restaurant initialized: " << name << std::endl;
    }

    void addDish(const std::string& dishName, double price) {
        menu.push_back(std::unique_ptr<Dish>(new Dish(dishName, price)));
        std::cout << "Added Dish (using new): " << dishName << " - Price: $" << price << std::endl;
    }

    void addSpecialDish(const std::string& dishName, double price, const std::string& note) {
        menu.push_back(std::unique_ptr<Dish>(new SpecialDish(dishName, price, note)));
        std::cout << "Added Special Dish (using new): " << dishName << " - Note: " << note << std::endl;
    }

    void displayMenu() const {
        std::cout << "Menu of " << name << ":\n";
        for (const auto& dish : menu) {
            dish->displayInfo();
        }
    }

    ~Restaurant() {
        std::cout << "Destructor called for Restaurant: " << name << std::endl;
        // Smart pointers automatizează eliberarea memoriei
    }

    Restaurant(const Restaurant&) = delete;
    Restaurant& operator=(const Restaurant&) = delete;
};

int main() {
    // Creare restaurant
    Restaurant restaurant("Gourmet Bistro");

    // Adăugare feluri de mâncare
    restaurant.addDish("Pasta Carbonara", 15.50);
    restaurant.addSpecialDish("Truffle Risotto", 25.00, "Fresh truffles");

    // Afișare meniu
    restaurant.displayMenu();

    // Demonstrarea copierii și mutării
    Dish dish1("Soup", 6.50);
    Dish dish2 = dish1; // Copy constructor
    Dish dish3 = std::move(dish1); // Move constructor
    dish2 = Dish("Salad", 5.00); // Copy assignment operator
    dish3 = std::move(dish2); // Move assignment operator

    return 0;
}
