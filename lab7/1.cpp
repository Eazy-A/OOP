#include <iostream>
#include <cstring>
using namespace std;


int main() {
    int n;
    cin >> n;

    if (n == 1) {
        // Test Scientist (Basic)
        int numScientists;
        cin >> numScientists;

        Scientist* scientists = new Scientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years;
            cin >> name >> institutiontitution >> publications >> citons >> years;

            scientists[i] = Scientist(name, institutiontitution, publications, citons, years);
        }

        cout << "SCIENTISTS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numScientists; ++i) {
            scientists[i].print();
            cout << "-------------------------" << endl;
        }

        // Copy Constructor Test
        cout << "Testing Copy Constructor:" << endl;
        Scientist copiedScientist = scientists[0];
        copiedScientist.print();

        // Assignment Operator Test
        cout << "Testing Assignment Operator:" << endl;
        Scientist assignedScientist;
        assignedScientist = scientists[1];
        assignedScientist.print();

        delete[] scientists;
    }
    else if (n == 2) {
        // Test ResearchScientist
        int numScientists;
        cin >> numScientists;

        ResearchScientist* scientists = new ResearchScientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years, Q1publications, EUprojects;
            double funding;

            cin >> name >> institutiontitution >> publications >> citons >> years;
            cin >> Q1publications >> EUprojects >> funding;

            scientists[i] = ResearchScientist(name, institutiontitution, publications, citons, years, Q1publications, EUprojects, funding);
        }

        cout << "RESEARCH SCIENTISTS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numScientists; ++i) {
            scientists[i].print();
            cout << "-------------------------" << endl;
        }

        // Copy Constructor Test
        cout << "Testing Copy Constructor:" << endl;
        ResearchScientist copiedResearchScientist = scientists[0];
        copiedResearchScientist.print();

        // Assignment Operator Test
        cout << "Testing Assignment Operator:" << endl;
        ResearchScientist assignedResearchScientist;
        assignedResearchScientist = scientists[1];
        assignedResearchScientist.print();

        delete[] scientists;
    }
    else if (n == 3) {
        // Test printing scientist with highest impact
        int numScientists;
        cin >> numScientists;

        Scientist* scientists = new Scientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years;
            cin >> name >> institutiontitution >> publications >> citons >> years;

            scientists[i] = Scientist(name, institutiontitution, publications, citons, years);
        }

        printHighestImpact(scientists, numScientists);
        delete[] scientists;
    }

    return 0;
}