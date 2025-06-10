#include <iostream>
#include <cstring>
using namespace std;

class Ingredient {
private:
    char *name;
    int quantity;
    int calories;

public:
    Ingredient() {
        this->name = new char[1];
        this->name[0] = '\0';
        this->quantity = 0;
        this->calories = 0;
    }

    Ingredient(char *name, int quantity, int calories) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->quantity = quantity;
        this->calories = calories;
    }

    Ingredient(const Ingredient &i) {
        name = new char[strlen(i.name) + 1];
        strcpy(name, i.name);
        quantity = i.quantity;
        calories = i.calories;
    }

    ~Ingredient() {
        delete[] name;
    }

    int getBrKalorii() const {
        return quantity * calories;
    }

    Ingredient &operator=(const Ingredient &i) {
        if (this != &i) {
            delete[] name;
            name = new char[strlen(i.name) + 1];
            strcpy(name, i.name);
            quantity = i.quantity;
            calories = i.calories;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Ingredient &i) {
        out << i.name << ": " << i.quantity << "g/ml";
        return out;
    }
};

class Dish {
private:
    Ingredient *ingridients;
    char *dishName;
    int ingredientCount;

public:
    Dish(char *dishName) {
        this->ingridients = nullptr;
        this->dishName = new char[strlen(dishName) + 1];
        strcpy(this->dishName, dishName);
        this->ingredientCount = 0;
    }

    Dish(const Dish &d) {
        dishName = new char[strlen(d.dishName) + 1];
        strcpy(dishName, d.dishName);
        this->ingredientCount = d.ingredientCount;
        this->ingridients = new Ingredient[ingredientCount];
        for (int i = 0; i < ingredientCount; i++) {
            ingridients[i] = d.ingridients[i];
        }
    }

    ~Dish() {
        delete[] ingridients;
        delete[] dishName;
    }

    int getTotalCalories() const {
        int totalCalories = 0;
        for (int i = 0; i < ingredientCount; i++) {
            totalCalories += ingridients[i].getBrKalorii();
        }
        return totalCalories;
    }

    Dish operator+(const Dish &d) const {
        Dish newDish(d.dishName);
        for (int i = 0; i < d.ingredientCount; i++) {
            newDish += d.ingridients[i];
        }
        for (int i = 0; i < ingredientCount; i++) {
            newDish += ingridients[i];
        }
        return newDish;
    }

    Dish &operator+=(const Ingredient &newIngredient) {
        Ingredient *temp = new Ingredient[ingredientCount + 1];
        for (int i = 0; i < ingredientCount; i++) {
            temp[i] = ingridients[i];
        }
        temp[ingredientCount] = newIngredient;
        delete[] ingridients;
        ingridients = temp;
        ingredientCount++;
        return *this;
    }

    bool operator==(const Dish &d) const {
        return getTotalCalories() == d.getTotalCalories();
    }

    friend ostream &operator<<(ostream &out, const Dish &d) {
        out << "Dish: " << d.dishName << endl;
        for (int i = 0; i < d.ingredientCount; i++) {
            out << "- " << d.ingridients[i] << endl;
        }
        out << "Total Calories: " << d.getTotalCalories() << endl;
        return out;
    }
};

int main() {
    char name[50];
    cin >> name;

    Ingredient tomato(name, 200, 20);
    cin >> name;
    Ingredient onion(name, 100, 30);
    cin >> name;
    Ingredient cheese(name, 50, 50);

    cin >> name;
    Dish salad(name);
    salad += tomato;
    salad += onion;

    cin >> name;
    Dish pizza(name);
    pizza += tomato;
    pizza += cheese;

    Dish combinedDish = salad + pizza;
    cout << combinedDish;

    cout << "--------------" << endl;

    Ingredient ingredient = tomato;
    cout << ingredient << endl;

    cout << "--------------" << endl;

    if (salad == pizza) {
        cout << "Salad and Pizza have the same calories." << endl;
    } else {
        cout << "Salad and Pizza have different calories." << endl;
    }


    return 0;
}
