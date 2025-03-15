#include <iostream>

using namespace std;

struct Student {
    char ime[100];
    char indeks[20];
    int kodovi[20];
    int kolkuKursevi;
};

struct Course {
    char ime[100];
    int kod;
    int brStudenti;
};

int najPopularen(Course *courses, int num) {
    int ind = -1, maxS = -1;

    for (int i = 0; i < num; i++) {
        if (courses[i].brStudenti > maxS) {
            maxS = courses[i].brStudenti;
            ind = i;
        }
    }

    return ind;
}

int main() {
    int n, t;
    cin >> n >> t;

    Course kursevi[20];
    Student studenti[20];

    for (int i = 0; i < t; i++) {
        cin >> kursevi[i].ime >> kursevi[i].kod;
        kursevi[i].brStudenti = 0;
    }

    for (int i = 0; i < n; i++) {
        cin >> studenti[i].ime >> studenti[i].indeks >> studenti[i].kolkuKursevi;
        for (int j = 0; j < studenti[i].kolkuKursevi; j++) {
            cin >> studenti[i].kodovi[j];
            for (int k = 0; k < t; k++) {
                if (studenti[i].kodovi[j] == kursevi[k].kod)
                    kursevi[k].brStudenti++;
            }
        }
    }

    int ind = najPopularen(kursevi, t);

    cout << "Najpopularen kurs e: " << kursevi[ind].ime;

    return 0;
}