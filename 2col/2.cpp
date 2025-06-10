#include <iostream>
#include <cstring>
#include <ostream>
using namespace std;

class Vozac {
protected:
    char name[100];
    int vozrast;
    int trki;
    bool vet;
public:
    Vozac(const char *name = "", int vozrast = 0, int trki = 0, bool vet = false) {
        strcpy(this->name, name);
        this->vozrast = vozrast;
        this->trki = trki;
        this->vet = vet;
    }
    friend ostream & operator<<(ostream &os, const Vozac &obj) {
        os << obj.name << endl;
        os << obj.vozrast << endl;
        os << obj.trki << endl;
        if (obj.vet) {
            os << "VETERAN" << endl;
        }
        return os;
    }
    virtual double zarabotuvacka() = 0;
    virtual double danok() = 0;
    bool const &operator==(Vozac &other) {
        if (this->zarabotuvacka() == other.zarabotuvacka()) {
            return true;
        }
        return false;
    }
};
class Avtomobilist : public Vozac {
    double cena_avto;
public:
    Avtomobilist(const char *name = "", int vozrast = 0, int trki = 0, bool vet = false, double cena_avto = 0)
        : Vozac(name , vozrast, trki, vet) {
        this->cena_avto = cena_avto;
    }
    double zarabotuvacka() override {
        return cena_avto / 5;
    }
    double danok() override {
        if (trki > 10) {
            return zarabotuvacka() * 0.15;
        }
        return zarabotuvacka() * 0.10;
    }
};
class Motociklist : public Vozac {
     int mokjnost;
public:
    Motociklist(const char *name = "", int vozrast = 0, int trki = 0, bool vet = false, int mokjnost = 0)
        :Vozac(name, vozrast, trki, vet) {
        this->mokjnost = mokjnost;
    }
    double zarabotuvacka() override {
        return mokjnost * 20;
    }
    double danok() override {
        if (vet) {
            return zarabotuvacka() * 0.25;
        }
        return zarabotuvacka() * 0.2;
    }
};
int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (vozaci[i]->zarabotuvacka() == v->zarabotuvacka()) {
            counter++;
        }
    }
    return counter;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}