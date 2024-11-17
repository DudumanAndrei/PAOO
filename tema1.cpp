#include <iostream>
#include <string>
#include <vector>
#include <utility> // pentru std::move

#include <iostream>
#include <string>

class Dish {
private:
    std::string name;
    double price;
    bool isAvailable;

public:
    // Constructor de inițializare
    Dish(const std::string& name = "Unnamed Dish", double price = 0.0, bool isAvailable = true)
        : name(name), price(price), isAvailable(isAvailable) {}

    // Constructor de copiere
    Dish(const Dish& other)
        : name(other.name), price(other.price), isAvailable(other.isAvailable) {}

    // Constructor de mutare
    Dish(Dish&& other);

    // Operator "=" de copiere
    Dish& operator=(const Dish& other);

    // Operator "=" de mutare
    Dish& operator=(Dish&& other);

    // Dezactivare funcții generate implicit de compilator
    Dish& operator=(std::nullptr_t) = delete;

    // Getter și Setter
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }

    void setPrice(double price) { this->price = price; }
    double getPrice() const { return price; }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }
    bool getAvailability() const { return isAvailable; }

    // Metode supraincarcate
    void displayInfo() const {
        std::cout << "Dish: " << name << " - Price: $" << price
                  << (isAvailable ? " (Available)" : " (Not Available)") << std::endl;
    }

    void displayInfo(const std::string& prefix) const {
        std::cout << prefix << name << " - Price: $" << price
                  << (isAvailable ? " (Available)" : " (Not Available)") << std::endl;
    }
};

// Definiții pentru constructorul de mutare
Dish::Dish(Dish&& other) 
    : name(std::move(other.name)), price(other.price), isAvailable(other.isAvailable) {
    std::cout << "Move constructor called for: " << name << std::endl;
    other.price = 0.0;
    other.isAvailable = false;
}

// Definiție pentru operator "=" de copiere
Dish& Dish::operator=(const Dish& other) {
    if (this == &other) return *this;
    name = other.name;
    price = other.price;
    isAvailable = other.isAvailable;
    std::cout << "Assignment operator called for: " << name << std::endl;
    return *this;
}

// Definiție pentru operator "=" de mutare
Dish& Dish::operator=(Dish&& other) {
    if (this == &other) return *this;
    name = std::move(other.name);
    price = other.price;
    isAvailable = other.isAvailable;
    std::cout << "Move assignment operator called for: " << name << std::endl;
    other.price = 0.0;
    other.isAvailable = false;
    return *this;
}


class Restaurant {
private:
    std::string name;
    std::vector<Dish*> menu;

public:
    Restaurant(const std::string& name = "Unnamed Restaurant") : name(name) {
        std::cout << "Restaurant initialized: " << name << std::endl;
    }

    // Adăugare feluri de mâncare
    void addDish(const std::string& dishName, double price) {
        Dish* newDish = new Dish(dishName, price);
        menu.push_back(newDish);
    }

    // Afișare meniu
    void displayMenu() const {
        std::cout << "Menu of " << name << ":\n";
        for (const auto& dish : menu) {
            dish->displayInfo();
        }
    }

    // Destructor pentru eliberarea memoriei
    ~Restaurant() {
        for (auto& dish : menu) {
            delete dish;
        }
        menu.clear();
        std::cout << "Memory freed for restaurant: " << name << std::endl;
    }

    // Dezactivarea copiei (Item 6)
    Restaurant(const Restaurant&) = delete;
    Restaurant& operator=(const Restaurant&) = delete;
};

int main() {
    // Creare restaurant
    Restaurant restaurant("Gourmet Bistro");

    // Adăugare feluri de mâncare
    restaurant.addDish("Pasta Carbonara", 15.50);
    restaurant.addDish("Margherita Pizza", 12.00);

    // Afișare meniu
    restaurant.displayMenu();

    // Constructor de copiere
    Dish dish1("Soup", 6.50);
    Dish dish2 = dish1;

    // Constructor de mutare
    Dish dish3 = std::move(dish1);

    // Operator "=" de copiere
    dish2 = Dish("Salad", 5.00);

    // Operator "=" de mutare
    dish3 = std::move(dish2);

    // Metode supraincarcate
    dish3.displayInfo();
    dish3.displayInfo("Special Offer: ");

    return 0;
}
