#include <iostream>
using namespace std;

int main() {
    double prvkol, vtorkol, krajna;
    char completedLab;
    int ocena;

    cout<<"Poeni od prv kolokvium: ";
    cin>>prvkol;
    cout<<"Poeni od vtor kolokvium: ";
    cin>>vtorkol;

    if (prvkol + vtorkol >= 100 && prvkol >= 30 && vtorkol >= 30) {
        krajna = (prvkol * 0.45) + (vtorkol * 0.45);
        cout<<"Dali gi zavrsi site labs uspesno?? (d/n): ";
        cin>>completedLab;
        if (completedLab == 'd' || completedLab == 'D') {
            krajna += 10;
        }
        if (krajna >= 90) {
            ocena = 10;
        } else if (krajna >= 80) {
            ocena = 9;
        } else if (krajna >= 70) {
            ocena = 8;
        } else if (krajna >= 60) {
            ocena = 7;
        } else if (krajna >= 50) {
            ocena = 6;
        } else {
            ocena = 5;
        }
        cout<<"Krajna ocena: "<<ocena<<endl;
        cout<<"Poeni: "<<krajna<<endl;
    } else {
        cout<<"Na ispit."<<endl;
    }
    return 0;
}