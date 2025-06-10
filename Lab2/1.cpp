#include <iostream>
#include <cstring>
using namespace std;
class MobilePhone {
private:
    char name[20];
    int model;
    int year;
public:
    MobilePhone(const char *name="", int model=1, int year=2008) {
        strcpy(this->name, name);
        this->model = model;
        this->year = year;
    }
    MobilePhone(const MobilePhone &other) {
        strcpy(this->name, other.name);
        this->model = other.model;
        this->year = other.year;
    }
    ~MobilePhone() {}
    void print() {
        cout<<name<<" "<<model<<" release year: "<<year<<endl;
    }
};
class Owner {
private:
    char name[20];
    char surname[20];
    MobilePhone mp;
public:
    Owner(const char *name="", const char *surname="", MobilePhone mp=MobilePhone()) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->mp = mp;
    }
    void print() {
        cout<<name<<" "<<surname<<endl;
        mp.print();
    }
};
int main() {
    MobilePhone mob1("iPhone", 12, 2023);
    Owner owner1("A", "Z", mob1);

    owner1.print(); // Пример за печатење на информациите

    return 0;
}