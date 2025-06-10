#include <iostream>
#include <cstring>
using namespace std;

class Lekar {
protected:
    int faksimil;
    char name[10];
    char lastname[10];
    double base_salary;
public:
    Lekar(int faksimil = 0, char *name = " ", char *lastname = " ", double base_salary = 0) {
        this -> faksimil = faksimil;
        strcpy(this -> name, name);
        strcpy(this -> lastname, lastname);
        this -> base_salary = base_salary;
    }
    void pecati() {
        cout << faksimil << " " << name << " " << lastname << endl;
    }
    virtual double getPlata() {
        return base_salary;
    }

};

class MaticenLekar : public Lekar{
    int num_patients;
    double *fees;
public:
    MaticenLekar() {
        num_patients = 0;
        fees = nullptr;
    }
    MaticenLekar(const Lekar &l, int num_patients, double *fees) : Lekar(l) {
        this -> num_patients = num_patients;
        this -> fees = new double[num_patients];
        for (int i = 0; i < num_patients; ++i) {
            this -> fees[i] = fees[i];
        }
    }
    ~MaticenLekar() {
        delete [] fees;
    }
    double sum_fees() {
        double sum = 0;
        for (int i = 0; i < num_patients; ++i) {
            sum += fees[i];
        }
        return sum;
    }
    double avg_fee() {
        return sum_fees() / num_patients;
    }
    void pecati() {
        Lekar::pecati();
        cout << avg_fee() << endl;
    }
    double getPlata() override {
        return base_salary + avg_fee() * 0.3;
    }
};


int main() {
    int n;
    cin >> n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime[20];
    char prezime[20];
    double osnovnaPlata;

    Lekar *lekari = new Lekar[n];
    MaticenLekar *maticni = new MaticenLekar[n];

    for (int i = 0; i < n; i++) {
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil, ime, prezime, osnovnaPlata);
    }

    for (int i = 0; i < n; i++) {
        cin >> pacienti;
        for (int j = 0; j < pacienti; j++) {
            cin >> kotizacii[j];
        }
        maticni[i] = MaticenLekar(lekari[i], pacienti, kotizacii);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "===TESTIRANJE NA KLASATA LEKAR===" << endl;
        for (int i = 0; i < n; i++) {
            lekari[i].pecati();
            cout << "Osnovnata plata na gorenavedeniot lekar e: " << lekari[i].getPlata() << endl;
        }
    }
    else {
        cout << "===TESTIRANJE NA KLASATA MATICENLEKAR===" << endl;
        for (int i = 0; i < n; i++) {
            maticni[i].pecati();
            cout << "Platata na gorenavedeniot maticen lekar e: " << maticni[i].getPlata() << endl;
        }
    }

    delete[] lekari;
    delete[] maticni;

    return 0;
}