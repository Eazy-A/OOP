#include <iostream>
#include <cstring>
using namespace std;

class MusicalInstrument {
public:
    MusicalInstrument(){}
    virtual void displayInstrumentInfo() = 0;
    virtual void displaySoundQuality() = 0;
    virtual int calculateLearningDifficulty() = 0;
};
class StringInstrument : public MusicalInstrument {
    bool isElectric;
    int numberOfStrings;
public:
    StringInstrument(bool isElectric = false, int numberOfStrings = 0) {
        this->isElectric = isElectric;
        this->numberOfStrings = numberOfStrings;
    }
    void displayInstrumentInfo() override {
        cout << "This is a string instrument with " << numberOfStrings << " strings ";
        if (isElectric) {
            cout << " and electric amplification" << endl;
        }
    }
    void displaySoundQuality() override {
        cout << "The sound quality of this string instrument is rated ";
        if (isElectric) {
            cout << "9";
        }
        else {
            cout << "7";
        }
        cout << " out of 10" << endl;
    }
    int calculateLearningDifficulty() override {
        if (isElectric) return 40 + numberOfStrings*5 + 15;
        return 40 + numberOfStrings*5;
    }
};
class WindInstrument : public MusicalInstrument {
    bool isBrass;
    int complexityLevel;
public:
    WindInstrument(bool isBrass = false, int complexityLevel = 0) {
        this->isBrass = isBrass;
        this->complexityLevel = complexityLevel;
    }
    void displayInstrumentInfo() override {
        cout << "This is a wind instrument that requires breath control ";
        if (isBrass) {
            cout << "and is made of brass";
        }
        cout << endl;
    }
    void displaySoundQuality() override {
        cout << "The sound quality of this wind instrument is rated ";
        if (isBrass) {
            cout << "8";
        }
        else {
            cout << "6";
        }
        cout << " out of 10" << endl;
    }
    int calculateLearningDifficulty() override {
        if (isBrass) return 30 + complexityLevel*10 + 20;
        return 30 + complexityLevel*10;
    }
};


int main() {
    MusicalInstrument* instruments[5];
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "TEST CASE 1: TESTING STRING INSTRUMENT CLASS" << endl;

        for (int i = 0; i < 5; i++) {
            int strings;
            cin >> strings;
            instruments[i] = new StringInstrument(false, strings);
            instruments[i]->displayInstrumentInfo();
            instruments[i]->displaySoundQuality();
            cout << "Learning difficulty: " << instruments[i]->calculateLearningDifficulty() << " out of 100." << endl;
        }
    } else if (testCase == 2) {
        cout << "TEST CASE 2: TESTING WIND INSTRUMENT CLASS" << endl;

        for (int i = 0; i < 5; i++) {
            int complexity;
            cin >> complexity;
            instruments[i] = new WindInstrument(false, complexity);
            instruments[i]->displayInstrumentInfo();
            instruments[i]->displaySoundQuality();
            cout << "Learning difficulty: " << instruments[i]->calculateLearningDifficulty() << " out of 100." << endl;
        }
    } else {
        cout << "TEST CASE 3: TESTING BOTH CLASSES" << endl;

        for (int i = 0; i < 5; i++) {
            if (i % 2) {
                bool isBrass;
                int complexity;
                cin >> isBrass >> complexity;
                instruments[i] = new WindInstrument(isBrass, complexity);
            }
            else {
                bool isElectric;
                int strings;
                cin >> isElectric >> strings;
                instruments[i] = new StringInstrument(isElectric, strings);
            }
            instruments[i]->displayInstrumentInfo();
            instruments[i]->displaySoundQuality();
            cout << "Learning difficulty: " << instruments[i]->calculateLearningDifficulty() << " out of 100." << endl;
        }
    }

    return 0;
}