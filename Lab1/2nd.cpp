#include <iostream>
#include <cstring>
using namespace std;

class BasketballPlayer {
private:
    char name[20];
    char lastname[20];
    int number;
    int points1;
    int points2;
    int points3;

public:
    BasketballPlayer() {}

    BasketballPlayer(char namee[], char lastnamee[], int numberr, int pointss1, int pointss2, int pointss3) {
        strcpy(name, namee);
        strcpy(lastname, lastnamee);
        number = numberr;
        points1 = pointss1;
        points2 = pointss2;
        points3 = pointss3;
    }

    void print() {
        cout<<"Player: "<<name<<" "<<lastname<<" with number: "<<number
             <<" has avg " << (points1 + points2 + points3) / 3.0<< " on average"<<endl;
    }
};

int main() {
    int points1, points2, points3, number;
    char name[20], lastname[20];

    cin>>name;
    cin>>lastname;
    cin>>number;
    cin>>points1>>points2>>points3;

    BasketballPlayer b(name, lastname, number, points1, points2, points3);

    b.print();

    return 0;
}