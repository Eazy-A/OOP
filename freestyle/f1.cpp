#include <iostream>
using namespace std;

struct date {
    int day;
    int month;
    int year;
};
int compareDates(date d1, date d2) {
    if (d1.year > d2.year) return 1;
    else  if (d1.year < d2.year) return 2;
    else {
        if (d1.month > d2.month) return 1;
        else if(d1.month < d2.month) return 2;
        else {
            if (d1.day > d2.day) return 1;
            else if(d1.day < d2.day) return 2;
            else return 0;
        }
    }
}
int toDays(date d){
    int days = 0;
    days = d.year*365 + d.month*31 + d.day;
    return days;
}
int difference(date d1, date d2) {
    int diff = 0;
    int days1 = toDays(d1), days2 = toDays(d2);
    if (compareDates(d1, d2) == 1) {
        diff = days1 - days2;
    }
    else if (compareDates(d1, d2) == 2) {
        diff = days2 - days1;
    }
    return diff;
}
void readDate(date *d) {
    cin>>d->day>>d->month>>d->year;
}
void printDate(date *d) {
    cout<<d->day<<" "<<d->month<<" "<<d->year<<endl;
}
int main() {
    date d1, d2;
    readDate(&d1);
    readDate(&d2);
    cout<<difference(d1, d2);
}