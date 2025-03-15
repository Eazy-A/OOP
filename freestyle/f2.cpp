#include <iostream>
using namespace std;

struct student {
    char name[100];
    char lastname [100];
    char index[10];
    int grades[100];
    int countGrades;
};
float gpa(student s) {
    float sum = 0;
    for (int i=0; i<s.countGrades; i++) {
        sum += s.grades[i];
    }
    float avg = sum / s.countGrades;
    return avg;
}
void bubbleSort(student *s, int n) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (gpa(s[j]) < gpa(s[j+1])) {
                swap(s[j], s[j+1]);
            }
        }
    }
}
void readStudent(student &s) {
    cin>>s.name>>s.lastname>>s.index>>s.countGrades;
    for (int i = 0; i<s.countGrades; i++) {
        cin>>s.grades[i];
    }
}
void printStudent(student s) {
    cout<<s.name<<" "<<s.lastname<<" "<<s.index<<" "<<gpa(s)<<endl;
}
int main() {
    student s[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        readStudent(s[i]);
    }
    bubbleSort(s, n);
    for (int i = 0; i<n; i++) {
        printStudent(s[i]);
    }
    return 0;
}