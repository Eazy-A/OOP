#include <iostream>
#include <string.h>
using namespace std;

class Datum {
private:
    int den, mesec, godina;
public:
    Datum() : den(0), mesec(0), godina(0){}
    Datum(int denn, int mesecc, int godinaa) : den(denn), mesec(mesecc), godina(godinaa){}

    void set_den(){ cin>>den; }
    void set_mesec(){ cin>>mesec; }
    void set_godina(){ cin>>godina; }

    int get_den(){ return den; }
    int get_mesec(){ return mesec; }
    int get_godina(){ return godina; }
};
class Vraboten {
private:
    char ime[20];
    int plata;
    Datum raganje;
public:
    Vraboten() : plata(0) {}
    Vraboten(char imee[], int plataa, Datum raganjee) : plata(plataa), raganje(raganjee) {
        strcpy(ime, imee);
    }
    void set_ime(){ cin>>ime; }
    void set_plata(){ cin>>plata; }
    void set_raganje() {
        int d, m, g;
        cin >> d >> m >> g;
        raganje = Datum(d, m, g);
    }
    char get_ime(){ return ime; }
};


int main() {

}