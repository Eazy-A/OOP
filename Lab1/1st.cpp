#include <iostream>
using namespace std;

struct Engine {
    int horsepower;
    int torque;
};

struct Car {
    char brand[20];
    int year_of_production;
    Engine engine;
};

void printCars(Car car[], int n) {
    int min1 = 0, min2 = 1;
    if (car[min2].engine.horsepower < car[min1].engine.horsepower) { //min1 e najmal
        swap(min1, min2);
    }
    for (int i = 2; i<n; i++) {
        if (car[i].engine.horsepower < car[min1].engine.horsepower) {
            min2 = min1;
            min1 = i;
        }else if (car[i].engine.horsepower < car[min2].engine.horsepower) {
            min2 = i;
        }
    }
    if (car[min1].engine.torque > car[min2].engine.torque) {
        cout<<car[min1].brand<<" "<<car[min1].year_of_production<<" "<<car[min1].engine.horsepower<<" "<<car[min1].engine.torque<<endl;
    }
    else {
        cout<<car[min2].brand<<" "<<car[min2].year_of_production<<" "<<car[min2].engine.horsepower<<" "<<car[min2].engine.torque<<endl;
    }
}

int main() {
    int n;
    cin>>n;

    if (n > 100) {
        cout<<"Too many cars! Maximum allowed is 100."<<endl;
        return 1;
    }

    Car car[100];

    for (int i = 0; i<n; i++) {
        cin>>car[i].brand>>car[i].year_of_production>>car[i].engine.horsepower>>car[i].engine.torque;
    }

    printCars(car, n);

    return 0;
}