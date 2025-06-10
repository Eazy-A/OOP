#include <iostream>
#include <cstring>
using namespace std;

class Tour {
    char destination[100];
    int duration;
    double price;
    static int totalTours;
    int passengers;
public:
    Tour() {
        strcpy(destination, "");
        duration = 0;
        price = 0;
        passengers = 0;
    }
    Tour(char *destination, int duration, double price, int passengers) {
        strcpy(this->destination, destination);
        this->duration = duration;
        this->price = price;
        this->passengers = passengers;
        totalTours++;
    }
    Tour(Tour const &other) {
        strcpy(this->destination, other.destination);
        this->duration = other.duration;
        this->price = other.price;
        this->passengers = other.passengers;
        totalTours++;
    }
    void display() {
        cout << "Destination: " << destination << ", Duration: " << duration
             << " days, Price: " << price << ", Passengers: " << passengers << endl;
    }
    double profitByTour() {
        return passengers * price;
    }
    static int getNumTours() {
        return totalTours;
    }
    friend class Agency;
};

int Tour::totalTours = 0;

class Agency {
    char name[20];
    Tour tours[10];
    int numtours;
public:
    Agency() {
        strcpy(name, "");
        numtours = 0;
    }
    Agency(char *name, Tour *tours, int numtours) {
        strcpy(this->name, name);
        this->numtours = (numtours > 10) ? 10 : numtours;
        for (int i = 0; i < this->numtours; ++i) {
            this->tours[i] = tours[i];
        }
    }
    void display() {
        cout << "Travel Agency: " << name << endl;
        for (int i = 0; i < numtours; ++i) {
            tours[i].display();
        }
    }
    void addTour(Tour tour) {
        if (numtours < 10) {
            tours[numtours++] = tour;
        }
    }
    void setName(char *name) {
        strcpy(this->name, name);
    }
    double calculateTotalProfit() {
        double total = 0;
        for (int i = 0; i < numtours; ++i) {
            total += tours[i].profitByTour();
        }
        return total;
    }
    friend void findBestAgency(Agency *agencies, int numAgencies);
};

void findBestAgency(Agency *agencies, int numAgencies) {
    if (numAgencies == 0) return;

    int bestIndex = 0;
    double maxProfit = agencies[0].calculateTotalProfit();

    for (int i = 1; i < numAgencies; ++i) {
        double currentProfit = agencies[i].calculateTotalProfit();
        if (currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestIndex = i;
        }
    }

    cout << "Best agency: " << endl;
    agencies[bestIndex].display();
    cout << "Total profit: " << maxProfit << endl;
}
int main() {


    int test_case_n;

    char name[50];
    char dest[50];
    int dur;
    double pr;
    int pass;

    cin>>test_case_n;

    if (test_case_n == 0) {
        cout << "Testing Tour c-tors, display function:"<<endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        Tour t2 = Tour(t1);
        t1.display();
        t2.display();
    } else if (test_case_n == 1) {
        cout << "Testing Tour profitByTour function:"<<endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        cout<<t1.profitByTour()<<endl;
    } else if (test_case_n == 2) {
        cout << "Testing Agency c-tor, display function:"<<endl;

        Agency agency;

        cin>>name;
        agency.setName(name);
        int numTours;
        cin>>numTours;
        for (int j = 0; j < numTours; ++j) {
            cin>>dest>>dur>>pr>>pass;
            agency.addTour(Tour(dest, dur, pr, pass));
        }

        agency.display();


    } else if (test_case_n == 3) {
        cout << "Testing static field in Tour:" <<endl;

        Agency agency [10];
        int n;
        cin >> n;

        for (int i = 0; i < n ; ++i) {
            cin>>name;
            agency[i].setName(name);
            int numTours;
            cin>>numTours;
            for (int j = 0; j < numTours; ++j) {
                cin>>dest>>dur>>pr>>pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }
        cout<<"Total number of tours: "<<Tour::getNumTours()<<endl;

    } else if (test_case_n == 4) {
        Agency agency [10];
        int n;
        cin >> n;
        for (int i = 0; i < n ; ++i) {
            cin>>name;
            agency[i].setName(name);
            int numTours;
            cin>>numTours;
            for (int j = 0; j < numTours; ++j) {
                cin>>dest>>dur>>pr>>pass; agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }
        findBestAgency(agency, n);
    }
    return 0;
}