#include <iostream>
#include <cstring>
using namespace std;

class Momche {
private:
    char ime[20];
    char prezime[20];
    int godini;
public:
    Momche(){}
    Momche(char *_ime, char *_prezime, int _godini) {
        strcpy(ime, _ime);
        strcpy(prezime, _prezime);
        godini = _godini;
    }

    char *getName() {
        return ime;
    }
    char *getLastname() {
        return prezime;
    }
    int const getYears() {
        return godini;
    }
    void print() {
        cout<<"Momche: "<<ime<<" "<<prezime<<" "<<godini;
    }
};
class Devojche {
private:
    char ime[20];
    char prezime[20];
    int godini;
public:
    Devojche(){}
    Devojche(char *_ime, char *_prezime, int _godini) {
        strcpy(ime, _ime);
        strcpy(prezime, _prezime);
        godini = _godini;
    }
    char *getName() {
        return ime;
    }
    char *getLastname() {
        return prezime;
    }
    int getYears() {
        return godini;
    }
    void print() {
        cout<<" Devojche: "<<ime<<" "<<prezime<<" "<<godini;
    }
};
class sredba {
private:
    Momche momche;
    Devojche devojche;
public:
    sredba() {}
    sredba(const Momche _momche, const Devojche _devojche) {
        momche = _momche;
        devojche = _devojche;
    }
    void print() {
        cout<<"Sredba: ";
        momche.print();
        devojche.print();
        cout<<endl;
    }
    void daliSiOdovaraat() {
        if (abs(momche.getYears() - devojche.getYears()) <=5) {
            cout<<"Si odgovaraat"<<endl;
        }
        else {
            cout<<"Ne si odgovaraat"<<endl;
        }
    }
};
int main() {

    char ime[20], prezime[20];
    int godini;
    cin>>ime>>prezime>>godini;
    Momche m(ime, prezime,godini);
    char imed[20], prezimed[20];
    int godinid;
    cin>>imed>>prezimed>>godinid;
    Devojche d(imed, prezimed, godinid);
    sredba s(m,d);
    s.print();
    s.daliSiOdovaraat();
    return 0;
}