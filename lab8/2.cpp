#include <iostream>
#include <cmath>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(int d = 0, int m = 0, int y = 0) {
        day = d;
        month = m;
        year = y;
    }

    static int date_difference(Date d1, Date d2) {
        int d1_total_days = d1.year * 365 + d1.month * 30 + d1.day;
        int d2_total_days = d2.year * 365 + d2.month * 30 + d2.day;
        return abs(d1_total_days - d2_total_days);
    }

    Date(const Date& o) {
        this->day = o.day;
        this->month = o.month;
        this->year = o.year;
    }

    Date& operator=(const Date& o) {
        if (this != &o) {
            this->day = o.day;
            this->month = o.month;
            this->year = o.year;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Date& d) {
        char sep;
        in >> d.day >> sep >> d.month >> sep >> d.year;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Date& d) {
        out << d.day << "/" << d.month << "/" << d.year;
        return out;
    }
};

int id_counter = 1;

class Sensor {
protected:
    string name;
    float baseReadingWeight;
    string id;
public:
    Sensor(string name = "", float baseReadingWeight = 0) {
        this->name = name;
        this->baseReadingWeight = baseReadingWeight;
        this->id = "S-" + to_string(id_counter++);
    }
    virtual float calculateReadingWeight() = 0;
    virtual void print() = 0;
    virtual ~Sensor() {}
};

class TemperatureSensor : public Sensor {
    float accuracy;
    bool isCalibrated;
public:
    TemperatureSensor(string name = "", float baseReadingWeight = 0, float accuracy = 0, bool isCalibrated = false)
        : Sensor(name, baseReadingWeight) {
        this->accuracy = accuracy;
        this->isCalibrated = isCalibrated;
    }

    float calculateReadingWeight() override {
        if (accuracy > 90 && isCalibrated) {
            return baseReadingWeight + 0.5;
        } else if (accuracy > 90) {
            return baseReadingWeight + 0.1;
        } else if (isCalibrated) {
            return baseReadingWeight + 0.3;
        }
        return baseReadingWeight;
    }

    void print() override {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Calculation: " << calculateReadingWeight() << endl;
    }
};

class MotionSensor : public Sensor {
    float range;
    Date* dates;
    int numDates;
public:
    MotionSensor(string name = "", float baseReadingWeight = 0, float range = 0, Date* dates = nullptr, int numDates = 0)
        : Sensor(name, baseReadingWeight) {
        this->range = range;
        this->numDates = numDates;
        this->dates = new Date[numDates];
        for (int i = 0; i < numDates; i++) {
            this->dates[i] = dates[i];
        }
    }

    MotionSensor(const MotionSensor& other) : Sensor(other.name, other.baseReadingWeight) {
        this->range = other.range;
        this->numDates = other.numDates;
        this->dates = new Date[numDates];
        for (int i = 0; i < numDates; i++) {
            this->dates[i] = other.dates[i];
        }
    }

    MotionSensor& operator=(const MotionSensor& other) {
        if (this != &other) {
            delete[] dates;
            this->name = other.name;
            this->baseReadingWeight = other.baseReadingWeight;
            this->range = other.range;
            this->numDates = other.numDates;
            this->dates = new Date[numDates];
            for (int i = 0; i < numDates; i++) {
                this->dates[i] = other.dates[i];
            }
        }
        return *this;
    }

    ~MotionSensor() {
        delete[] dates;
    }

    float calculateReadingWeight() override {
        float extra = 0;
        if (range < 10) extra += 0.2;
        if (numDates >= 2) {
            Date last = dates[numDates - 1];
            Date secondLast = dates[numDates - 2];
            if (Date::date_difference(last, secondLast) < 3)
                extra += 0.5;
        }
        return baseReadingWeight + extra;
    }

    void print() override {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Calculation: " << calculateReadingWeight() << endl;
        if (numDates > 0) {
            cout << "Last date of calibration: " << dates[numDates - 1] << endl;
        }
    }

    void addDate(Date d) {
        Date* tmp = new Date[numDates + 1];
        for (int i = 0; i < numDates; i++) {
            tmp[i] = dates[i];
        }
        tmp[numDates] = d;
        delete[] dates;
        dates = tmp;
        numDates++;
    }
};
Sensor* highestReadingWeight(Sensor** sensors, int n) {
    if (n == 0) return nullptr;
    Sensor* best = sensors[0];
    for (int i = 1; i < n; i++) {
        if (sensors[i]->calculateReadingWeight() > best->calculateReadingWeight())
            best = sensors[i];
    }
    return best;
}

int main() {
    int tc;
    cin >> tc;

    if (tc == 1) {
        cout << "Testing TemperatureSensor " << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int accuracy;
            bool isCalibrated;
            cin >> name >> baseReadingWeight >> accuracy >> isCalibrated;

            TemperatureSensor* ts = new TemperatureSensor(name, baseReadingWeight, accuracy, isCalibrated);
            ts->print();
            delete ts;
        }
    } else if (tc == 2) {
        cout << "Testing MotionSensor " << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int range;
            int m;
            cin >> name >> baseReadingWeight >> range >> m;

            Sensor* ms = new MotionSensor(name, baseReadingWeight, range, nullptr, 0);
            ms->print();
            delete ms;
        }
    } else if (tc == 3) {
        cout << "Testing Dynamic Allocation" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int range;
            int m;
            cin >> name >> baseReadingWeight >> range >> m;

            Sensor* ms = new MotionSensor(name, baseReadingWeight, range, new Date[0], 0);
            ms->print();
            delete ms;
        }
    }
    return 0;
}
