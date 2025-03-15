#include <iostream>
using namespace std;

struct city {
    char name[100];
    long population;
};
struct president {
    char name[100];
    char lastname[100];
    char party[100];
};
struct country {
    char name[100];
    president P;
    city cap;
};

void readCountry(country &c, city &g, president &p ) {
    cin>>c.name>>p.name>>p.lastname>>g.name>>g.population;
}
void printPresident(president p) {
    cout<<p.name<<" "<<p.lastname<<" "<<p.party<<endl;
}
int main() {
    int n;
    country drzava[100];
    city grad[100];
    president pretsedatel[100];
    cin>>n;
    int max = 0;
    char maxgrad;
    for (int i = 0; i<n; i++) {
        readCountry(drzava[i], grad[i], pretsedatel[i]);
        if (grad[i].population > max) {
            max = grad[i].population;
            maxgrad = i;
        }
    }
    printPresident(pretsedatel[maxgrad]);
    return 0;
}