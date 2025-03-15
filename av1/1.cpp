#include <iostream>
using namespace std;

struct date {
    int year;
    int month;
    int day;
};
int compare(date &d1, date &d2) {
        // if (d1.year < d2.year) { //d1 is always greater now
        //     date temp = d2;   //not necessary when using abs
        //     d2 = d1;
        //     d1 = temp;
        // }
        return abs((d1.year - d2.year)*365 + (d1.month - d2.month)*30 + (d1.day - d2.day));
    }
void read(date &d) {
    cin>>d.day>>d.month>>d.year;
}
void print(date d) {
    cout<<d.day<<" "<<d.month<<" "<<d.year<<endl;
}
int main() {
    date d1, d2;
    read(d1);
    read(d2);
    cout<<compare(d1, d2);
    return 0;
}