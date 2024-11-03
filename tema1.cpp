#include <iostream>
#include <string>
#include <vector>

class Dish {
private:
    std::string name;
    double price;
    bool isAvailable;

public:
    // Constructor de inițializare
    Dish(const std::string& name, double price, bool isAvailable = true) 
        : name(name), price(price), isAvailable(isAvailable) {}

    // Constructor de copiere (supraincarcare constructor)
    Dish(const Dish& other) 
        : name(other.name), price(other.price), isAvailable(other.isAvailable) {}

    // Setters și getters pentru encapsulare
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }

    void setPrice(double price) { this->price = price; }
    double getPrice() const { return price; }

    void setAvailability(bool isAvailable) { this->isAvailable = isAvailable; }
    bool getAvailability() const { return isAvailable; }

    // Supraincarcare operator "="
    Dish& operator=(const Dish& other) {
        if (this == &other) return *this; // protecție la auto-atribuire
        name = other.name;
        price = other.price;
        isAvailable = other.isAvailable;
        return *this;
    }

    // Metode cu același nume, dar semnături diferite (overloading)
    void displayInfo() const {
        std::cout << "Dish: " << name << " - Price: $" << price << (isAvailable ? " (Available)" : " (Not Available)") << std::endl;
    }

    void displayInfo(const std::string& prefix) const {
        std::cout << prefix << name << " - Price: $" << price << (isAvailable ? " (Available)" : " (Not Available)") << std::endl;
    }
};

class Restaurant {
private:
    std::string name;
    std::vector<Dish*> menu;  // Folosim pointeri pentru obiectele Dish pe heap

public:
    // Constructor pentru Restaurant cu lista de inițializare
    Restaurant(const std::string& name) : name(name) {}

    // Adăugare fel de mâncare la meniu
    void addDish(const std::string& dishName, double price) {
        Dish* newDish = new Dish(dishName, price);  // alocare pe heap
        menu.push_back(newDish);
    }

    // Metodă pentru afișarea meniului
    void displayMenu() const {
        std::cout << "Menu of " << name << ":\n";
        for (const auto& dish : menu) {
            dish->displayInfo();
        }
    }

    // Destructor pentru eliberarea memoriei alocate pe heap
    ~Restaurant() {
        for (auto& dish : menu) {
            delete dish;
        }
        menu.clear();
        std::cout << "Memory freed for restaurant: " << name << std::endl;
    }
};

int main() {
    // Creare restaurant
    Restaurant restaurant("Gourmet Bistro");

    // Adăugare feluri de mâncare
    restaurant.addDish("Pasta Carbonara", 15.50);
    restaurant.addDish("Margherita Pizza", 12.00);

    // Afișare meniu
    restaurant.displayMenu();

    // Supraincarcare constructor de copiere
    Dish dish1("Soup", 6.50);
    Dish dish2 = dish1;  // Constructor de copiere

    // Supraincarcare operator "="
    dish2 = Dish("Salad", 5.00);  // Operatorul "="

    // Folosim metodele supraincarcate
    dish2.displayInfo();
    dish2.displayInfo("Special Offer: ");

    return 0;
}
