#include <iostream>
#include <string>

using namespace std;

// Максимален број на состојки
const int MAX_INGREDIENTS = 10;

// Класа за пица
class Pizza {
protected:
    string size;
    double price;
    string ingredients[MAX_INGREDIENTS]; // Низа за состојки
    int ingredientCount; // Број на состојки

    // Метод за поставување на цена врз основа на големина
    void setPriceBasedOnSize() {
        if (size == "Small") price = 270;
        else if (size == "Medium") price = 360;
        else if (size == "Large") price = 480;
        else price = 0; // Доколку големината е невалидна
    }

public:
    // Конструктори
    Pizza() : size("Medium"), ingredientCount(0) {
        setPriceBasedOnSize();
    }
    Pizza(string size) : size(size), ingredientCount(0) {
        setPriceBasedOnSize();
    }

    // Set и Get методи
    void setSize(string s) {
        size = s;
        setPriceBasedOnSize(); // Ажурирај ја цената при промена на големина
    }
    string getSize() const { return size;}

    double getPrice() const { return price; }

    // Додавање на состојки
    void addIngredient(string ingredient) {
        if (ingredientCount < MAX_INGREDIENTS) {
            ingredients[ingredientCount++] = ingredient;
            price += 20; // Зголеми ја цената за 20 за секоја дополнителна состојка
        } else {
            cout << "Cannot add more ingredients. Maximum limit reached." << endl;
        }
    }

    // Метод за печатење на детали
    virtual void printDetails() const {
        cout << "Size: " << size << ", Price: $" << price << endl;
        cout << "Ingredients: ";
        for (int i = 0; i < ingredientCount; ++i) {
            cout << ingredients[i];
            if (i < ingredientCount - 1) cout << ", ";
        }
        cout << endl;
    }

    // Методи за подготовка на пица
    void prepare() const {
        cout << "Preparing the pizza..." << endl;
    }

    void bake() const {
        cout << "Baking the pizza..." << endl;
    }

    void cut() const {
        cout << "Cutting the pizza into slices..." << endl;
    }

    void box() const {
        cout << "Boxing the pizza..." << endl;
    }

    // Деструктор
    virtual ~Pizza() {
        cout << "Pizza object destroyed." << endl;
    }
};

// Класа за CheesePizza
class CheesePizza : public Pizza {
public:
    // Конструктори
    CheesePizza() : Pizza("Medium") {
        addIngredient("Cheese");
        addIngredient("Tomato Sauce");
    }
    CheesePizza(string size) : Pizza(size) {
        addIngredient("Cheese");
        addIngredient("Tomato Sauce");
    }

    // Деструктор
    ~CheesePizza() {
        cout << "CheesePizza object destroyed." << endl;
    }
};

// Класа за PepperoniPizza
class PepperoniPizza : public Pizza {
public:
    // Конструктори
    PepperoniPizza() : Pizza("Medium") {
        addIngredient("Pepperoni");
        addIngredient("Cheese");
        addIngredient("Tomato Sauce");
    }
    PepperoniPizza(string size) : Pizza(size) {
        addIngredient("Pepperoni");
        addIngredient("Cheese");
        addIngredient("Tomato Sauce");
    }

    // Деструктор
    ~PepperoniPizza() {
        cout << "PepperoniPizza object destroyed." << endl;
    }
};

// Класа за пицерија
class Pizzeria {
private:
    string name;
    Pizza* currentPizza;

public:
    // Конструктор
    Pizzeria(string name) : name(name), currentPizza(nullptr) {}

    // Метод за додавање на пица
    void addPizza(Pizza* pizza) {
        if (currentPizza == nullptr) {
            currentPizza = pizza;
            cout << "Added a new pizza to " << name << "." << endl;
        } else {
            cout << "Cannot add a new pizza. The previous one is not yet delivered." << endl;
        }
    }

    // Метод за подготовка на пица
    void preparePizza() {
        if (currentPizza != nullptr) {
            currentPizza->prepare();
            currentPizza->bake();
            currentPizza->cut();
            currentPizza->box();
            cout << "Pizza is ready!" << endl;
            cout << "Final price: $" << currentPizza->getPrice() << endl; // Печатење на конечната цена
            delete currentPizza; // Ослободување на меморија
            currentPizza = nullptr;
        } else {
            cout << "No pizza to prepare." << endl;
        }
    }

    // Деструктор
    ~Pizzeria() {
        if (currentPizza != nullptr) {
            delete currentPizza;
        }
        cout << "Pizzeria object destroyed." << endl;
    }
};

// Функција за внес на пица од корисникот
Pizza* createPizza() {
    string size, ingredient;
    int choice;

    cout << "Enter pizza size (Small, Medium, Large): ";
    cin >> size;

    cout << "Choose pizza type:\n1. Cheese Pizza\n2. Pepperoni Pizza\nEnter your choice: ";
    cin >> choice;

    Pizza* pizza = nullptr;

    if (choice == 1) {
        pizza = new CheesePizza(size);
    } else if (choice == 2) {
        pizza = new PepperoniPizza(size);
    } else {
        cout << "Invalid choice. Creating a default Cheese Pizza." << endl;
        pizza = new CheesePizza(size);
    }

    // Додавање дополнителни состојки
    cout << "Do you want to add extra ingredients? (1 for Yes, 0 for No): ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter ingredients (type 'done' to finish):" << endl;
        while (true) {
            cin >> ingredient;
            if (ingredient == "done") break;
            pizza->addIngredient(ingredient);
        }
    }

    return pizza;
}

// Главна функција за тестирање
int main() {
    // Креирање на пицерија
    Pizzeria pizzeria("Pizza Hut");

    // Креирање на пица од корисникот
    Pizza* pizza = createPizza();
    pizzeria.addPizza(pizza);
    pizzeria.preparePizza();

    return 0;
}