#include <iostream>
#include <cstring>
using namespace std;

enum position {
    employee, manager, owner
};

class vraboten {
private:
    char name[50];
    int salary;
    position pos;
public:
    vraboten() {}
    vraboten(char ime[], int plata, position p) {
        strcpy(name, ime);
        salary = plata;
        pos = p;
    }
    ~vraboten(){};
    void setname(char ime[]) {
         strcpy(name, ime);
    }
    void setsalary(int plata) {
        salary = plata;
    }
    void setposition(position p) {
        pos = p;
    }
    char *getname() {
        return name;
    }
    int getsalary() {
        return salary;
    }
    position getposition() {
        return pos;
    }
};
void selection_sort(vraboten v[], int n) {
    vraboten p;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i; j < n; ++j) {
            if (v[i].getsalary() < v[j].getsalary()) {
                p = v[j];
                v[j] = v[i];
                v[i] = p;
            }
        }
    }
}
int main() {
    int n;
    vraboten vraboteni[100];
    char name[100];
    float salary;
    int pos;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>name;
        cin>>salary;
        cin>>pos;
        vraboteni[i].setname(name);
        vraboteni[i].setsalary(salary);
        vraboteni[i].setposition((position)pos);
    }
    selection_sort(vraboteni,n);
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << vraboteni[i].getname() << "\t"
             << vraboteni[i].getsalary() << "\t"
             << vraboteni[i].getposition() << endl;
    }
    return 0;
}