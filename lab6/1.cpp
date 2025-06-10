#include <iostream>
using namespace std;

class Kvadrat {
protected:
   double side;
public:
    Kvadrat() {
        side = 0;
    }
    Kvadrat(double side ) {
        this -> side = side;
    }

    Kvadrat(const Kvadrat &other) {
        this -> side = other.side;
    }

    virtual double perimetar() {
        return side * 4;
    }
    virtual double plostina() {
        return side * side;
    }
    virtual void pecati() {
        cout << "Kvadrat " << side << " " << perimetar() << " " << plostina() << endl;
    }
};

class Pravoagolnik : public Kvadrat{ //da se vmetni nasleduvanjeto
private:
    double x; // prosiruvanje na dvete paralelni strani
    double y; // prosiruvanje na drugite dve pralelni stani
public:
    Pravoagolnik() {
        x = 0;
        y = 0;
    }
    Pravoagolnik (const Kvadrat &k, double x, double y) : Kvadrat(k){
        this -> x = x;
        this -> y = y;
    }
    Pravoagolnik(const Pravoagolnik &other) : Kvadrat(other) {
        this -> x = other.x;
        this -> y = other.y;
    }
    double perimetar() override {
        return (side + x) * 2 + (side + y) * 2;
    }
    double plostina() override {
        return (side + x) * (side + y);
    }
    void pecati() override {
        if (x == y) {
            Kvadrat::pecati();
        }
        else {
            cout << "Pravoagolnik " << side + x << " " << side + y << " " <<perimetar() << " " << plostina() << endl;
        }
    }

};
int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}