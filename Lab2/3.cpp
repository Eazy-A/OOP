#include <iostream>
#include <cstring>
using namespace std;

class Item {
    char name[50];
    double price;
public:
    Item(const char *name = "", double price = 0.0) {
        strcpy(this->name, name);
        this->price = price;
    }

    double getPrice() const {
        return price;
    }
};

class Receipt {
    Item items[100];
    int n;
public:
    Receipt(int n = 0, Item items[] = nullptr) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->items[i] = items[i];
        }
    }

    double totalSum() const {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += items[i].getPrice();
        }
        return sum;
    }
};

int main() {
    Item items[] = {
        Item("Milk", 1.5),
        Item("Bread", 0.8),
        Item("Cheese", 2.3)
    };

    Receipt receipt(3, items);

    cout << "Total price: " << receipt.totalSum() << endl;

    return 0;
}
