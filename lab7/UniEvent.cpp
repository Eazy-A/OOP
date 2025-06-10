#include <iostream>
#include <cstring>
using namespace std;
class UniversityEvent {
protected:
    char *name;
    char *universityHost;
    char *date;
    int entryFee;
public:
    UniversityEvent(const char *name="", const char *universityHost="", const char *date="", int entryFee = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->universityHost = new char[strlen(universityHost) + 1];
        strcpy(this->universityHost, universityHost);
        this->date = new char[strlen(date) + 1];
        strcpy(this->date, date);
        this->entryFee = entryFee;
    }
    UniversityEvent(const UniversityEvent &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->universityHost = new char[strlen(other.universityHost) + 1];
        strcpy(this->universityHost, other.universityHost);
        this->date = new char[strlen(other.date) + 1];
        strcpy(this->date, other.date);
        this->entryFee = other.entryFee;
    }
    virtual ~UniversityEvent() {
        delete[] name;
        delete[] universityHost;
        delete[] date;
    }
    UniversityEvent &operator=(const UniversityEvent &other) {
        if (this != &other) {
            delete[] name;
            delete[] universityHost;
            delete[] date;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->universityHost = new char[strlen(other.universityHost) + 1];
            strcpy(this->universityHost, other.universityHost);
            this->date = new char[strlen(other.date) + 1];
            strcpy(this->date, other.date);
            this->entryFee = other.entryFee;
        }
        return *this;
    }

    virtual int getEntryFee() {
        return entryFee;
    }
    virtual void registerEvent() = 0;
    virtual void print() {
        cout << "Event: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Entry Fee: " << entryFee << "den." << endl;
    }

};
class OnSiteEvent : public UniversityEvent {
    int participants;
    int capacity;
public:
    OnSiteEvent(const char *name="", const char *universityHost="", const char *date="", int entryFee = 0, int capacity = 0)
    : UniversityEvent(name, universityHost, date, entryFee) {
        this->participants = 0;
        this->capacity = capacity;
    }
    OnSiteEvent(const OnSiteEvent &other) : UniversityEvent(other){
        this->participants = other.participants;
        this->capacity = other.capacity;
    }
    ~OnSiteEvent() override = default;
    OnSiteEvent &operator=(const OnSiteEvent &other){
        if (this != &other) {
            UniversityEvent::operator=(other);
            this->capacity = other.capacity;
            this->participants = other.participants;
        }
        return *this;
    }
    void registerEvent() override {
        if (participants < capacity) {
            participants++;
            cout << "You have successfully registered on the OnSiteEvent , you have to pay " << entryFee << " den." << endl;
        }
        else {
            cout << "We are sorry, but unfortunately, the capacity is full." << endl;
        }
    }
    void print() override {
        UniversityEvent::print();
        cout << "Participants: " << participants << endl;
    }
};
class OnlineEvent : public UniversityEvent {
    char *bbbLink;
public:
    OnlineEvent(const char *name="", const char *universityHost="", const char *date="", int entryFee = 0 , const char *bbbLink = "")
    : UniversityEvent(name, universityHost, date, entryFee) {
        this->bbbLink = new char[strlen(bbbLink) + 1];
        strcpy(this->bbbLink, bbbLink);
    }
    OnlineEvent(const OnlineEvent &other) : UniversityEvent(other) {
        this->bbbLink = new char[strlen(other.bbbLink) + 1];
        strcpy(this->bbbLink, other.bbbLink);
    }
    ~OnlineEvent() {
        delete[] bbbLink;
    }
    OnlineEvent &operator=(const OnlineEvent &other) {
        if (this != &other) {
            UniversityEvent::operator=(other);
            delete [] bbbLink;
            this->bbbLink = new char[strlen(other.bbbLink) + 1];
            strcpy(this->bbbLink, other.bbbLink);
        }
        return *this;
    }
    int getEntryFee() override {
        return entryFee * 0.5;
    }
    void registerEvent() override {
        cout << "You have successfully registered on the OnlineEvent , you have to pay " << getEntryFee() << "den.";
    }
    void print() override {
        UniversityEvent::print();
        cout << "Link: " << bbbLink << endl;
    }
};

int main() {
    int n;
    cin >> n;

    UniversityEvent** events = new UniversityEvent*[n];

    char name[100];
    char universityHost[100];
    char date[100];
    int entryFee;

    for (int i = 0; i < n; i++) {
        cin >> name;
        cin >> universityHost;
        cin >> date;
        cin >> entryFee;

        if (i % 2 == 0) {
            int capacity;
            cin >> capacity;
            events[i] = new OnSiteEvent(name, universityHost, date, entryFee, capacity);
        } else {
            char bbbLink[200];
            cin >> bbbLink;
            events[i] = new OnlineEvent(name, universityHost, date, entryFee, bbbLink);
        }
    }

    for (int i = 0; i < n; i++) {
        events[i]->print();
        events[i]->registerEvent();
        cout << "-------------------------\n";
    }

    // Test OnSiteEvent.registerEvent() edge cases using first event dynamically
    cout << "\n--- Dynamic OnSiteEvent Capacity Test ---\n";
    OnSiteEvent* testEvent = dynamic_cast<OnSiteEvent*>(events[0]);
    for (int i = 0; i < 10; ++i) {
        testEvent->registerEvent();
    }

    cout << "\n--- OnSiteEvent print() after dynamic test ---\n";
    testEvent->print();

    // Test operator=
    cout << "\n--- OnSiteEvent Operator= Test (dynamic) ---\n";
    OnSiteEvent assignedEvent;
    assignedEvent = *testEvent;
    assignedEvent.print();

    // Cleanup
    for (int i = 0; i < n; i++) delete events[i];
    delete[] events;

    return 0;
}