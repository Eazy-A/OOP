#include <iostream>
using namespace std;

struct Student {
    char name[30];
    int index;
    int num_courses;
    int codes_of_student[30];
};
struct Course {
    char name[30];
    int code;
    int num_students;
};
int get_most_popular_course(struct Course courses[], int num_courses) {
    int max = -1; int index = -1;
    for (int i = 0; i < num_courses; ++i) {
        if (courses[i].num_students > max) {
            max = courses[i].num_students;
            index = i;
        }
    }
    return index;
}
int main() {
    int br_studenti, br_kursevi;
    cin>>br_studenti>>br_kursevi;
    Course courses[100];
    Student students[100];
    for (int i = 0; i < br_kursevi; ++i) {
        cin>>courses[i].name>>courses[i].code;
    }
    for (int i = 0; i < br_studenti; ++i) {
        cin.ignore();
        cin.getline(students[i].name, 30);
        cin>>students[i].index>>students[i].num_courses;
        for (int j = 0; j < students[i].num_courses; ++j) {
            cin>>students[i].codes_of_student[j];
            for (int k = 0; k < br_kursevi; ++k) {
                if (students[i].codes_of_student[j] == courses[k].code) {
                    courses[k].num_students++;
                }
            }
        }
    }
    int popular = get_most_popular_course(courses, br_kursevi);
    cout<<"The most popular course is: "<<courses[popular].name;
    return 0;
}