#include <iostream>
#include <cstring>
using namespace std;

class ekipa {
private:
    char ime[20];
    int godina;
    char grad[20];
public:
    ekipa(){}
    ekipa(char *_ime, int _godina, char *_grad) {
        strcpy(ime, _ime);
        godina = _godina;
        strcpy(grad, _grad);
    }
    char *getName() {
        return ime;
    }
    int getYear() {
        return godina;
    }
    char *getCity() {
        return grad;
    }
    void print() {
        cout << ime << " " << godina << " " << grad << endl;
    }
};

class natprevar {
private:
    ekipa domakin;
    ekipa gostin;
    int goloviDomakin;
    int goloviGostin;
public:
    natprevar(){}
    natprevar(ekipa _domakin, ekipa _gostin, int _goloviDomakin, int _goloviGostin) {
        domakin = _domakin;
        gostin = _gostin;
        goloviDomakin = _goloviDomakin;
        goloviGostin = _goloviGostin;
    }
    ekipa getDomakin() {
        return domakin;
    }
    ekipa getGostin() {
        return gostin;
    }
    int getGoloviDomakin() {
        return goloviDomakin;
    }
    int getGoloviGosti() {
        return goloviGostin;
    }
};

bool revans(natprevar &n1, natprevar &n2) {
    return (strcmp(n1.getDomakin().getName(), n2.getGostin().getName()) == 0 &&
            strcmp(n1.getGostin().getName(), n2.getDomakin().getName()) == 0);
}

int duel(natprevar &n1, natprevar &n2) {
    if (!revans(n1, n2)) return -1; // Not a valid rematch

    int golovi_ekipa1 = n1.getGoloviDomakin() + n2.getGoloviGosti();
    int golovi_ekipa2 = n1.getGoloviGosti() + n2.getGoloviDomakin();

    if (golovi_ekipa1 > golovi_ekipa2) {
        cout << "The winner is " << n1.getDomakin().getName() << endl;
        return 1;
    } else if (golovi_ekipa2 > golovi_ekipa1) {
        cout << "The winner is " << n1.getGostin().getName() << endl;
        return 2;
    }
    return 0;
}

int main() {
    ekipa e1("Real", 1950, "Madrid");
    ekipa e2("Barca", 1966, "Barcelona");
    natprevar n1(e1, e2, 1, 2);
    natprevar n2(e2, e1, 1, 0);

    int result = duel(n1, n2);
    if (result == -1) {
        cout << "Not a valid rematch!" << endl;
    } else if (result == 0) {
        cout << "It's a draw!" << endl;
    }
    return 0;
}
