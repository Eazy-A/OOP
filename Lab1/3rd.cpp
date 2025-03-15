#include <iostream>
#include <cstring>
using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country() {
    }
    Country(char namee[], char capitall[], double areaa, double populationn){
        strcpy(name, namee);
        strcpy(capital, capitall);
        area = areaa;
        population = populationn;
    }
    void setname(char *namee) {
        strcpy(name, namee);
    }
    void setcapital(char *capitall) {
        strcpy(capital, capitall);
    }
    void setarea(double areaa) {
        area = areaa;
    }
    void setpopulation(double populationn) {
        population = populationn;
    }
    char *getname() {
        return name;
    }
    char *getcapital() {
        return capital;
    }
    double getarea() {
        return area;
    }
    double getpopulation() {
        return population;
    }
    void diplay() {
        cout<<"Country: "<<name<<endl;
        cout<<"Capital: "<<capital<<endl;
        cout<<"Area: "<<area<<endl;
        cout<<"Population: "<<population<<endl;
    }
};
void sortCountries(Country countries[], int n) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n-i-1; j++) {
            if (countries[j].getarea() > countries[j+1].getarea()) {
                swap(countries[j], countries[j+1]);
            }
        }
    }
}
int main() {
    int n;
    cin>>n;
    char name[100];
    char capital[100];
    double area;
    double population;
    Country countries[100];
    for (int i = 0; i<n; i++) {
        cin>>name>>capital>>area>>population;
        countries[i].setname(name);
        countries[i].setcapital(capital);
        countries[i].setarea(area);
        countries[i].setpopulation(population);
    }
    sortCountries(countries, n);
    for (int i = 0; i<n; i++) {
        cout<<countries[i].getname()<<" "<<countries[i].getcapital()<<" "<<countries[i].getarea()<<" "<<countries[i].getpopulation()<<endl;
    }
    countries->diplay();
    return 0;
}