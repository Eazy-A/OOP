#include <iostream>
#include <cstring>
using namespace std;

struct student {
    char ime[20];
    char prezime[20];
    char index[20];
    int poeni[4];
    int sum_poeni = 0;

};
void read_student(student &s) {
    cin>>s.ime>>s.prezime>>s.index;
    cin.ignore();
    for (int i = 0; i<4; i++) {
        cin>>s.poeni[i];
        s.sum_poeni += s.poeni[i];
    }
}
void print_student(student s) {
    s.prezime[0] = toupper(s.prezime[0]);
    s.ime[0] = toupper(s.ime[0]);
    cout<<s.prezime<<" "<<s.ime<<" "<<s.index<<" "<<s.sum_poeni<<endl;
}
void sort(student s[], int n) {
    for (int i = 0; i<n-1; i++) {
        for (int j = 0; j<n-i-1; j++) {
            if (s[j].sum_poeni < s[j+1].sum_poeni) {
                swap(s[j], s[j+1]);
            }
        }
    }
}
int main() {
    student s[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        read_student(s[i]);
    }
    sort(s, n);
    for (int i = 0; i<n; i++) {
        print_student(s[i]);
    }
    return 0;
}