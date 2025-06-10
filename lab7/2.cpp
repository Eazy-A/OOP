#include <iostream>
#include <cstring>
using namespace std;

class Membership {
protected:
    char name[50];
    char date[12];
    int monthly_fee;
public:
    Membership(const char *name = "", const char *date="2025-05-05", int monthly_membership = 0) {
        strcpy(this->name, name);
        strcpy(this->date, date);
        this->monthly_fee = monthly_membership;
    }
    Membership(const Membership &other) {
        strcpy(this->name, other.name);
        strcpy(this->date, other.date);
        this->monthly_fee = other.monthly_fee;
    }
    Membership const &operator=(const Membership &other) {
        if (this != &other) {
            strcpy(this->name, other.name);
            strcpy(this->date, other.date);
            this->monthly_fee = other.monthly_fee;
        }
        return *this;
    }
    virtual int getMonthlyFee() {
        return monthly_fee;
    }
    virtual void print() {
        cout << name << " - " << date;
    }
};
class BasicMembership : public Membership {
    bool isMorningMembership;
public:
    BasicMembership(Membership &m, bool isMorningMembership = false)
        :Membership(m) {
        this->isMorningMembership = isMorningMembership;
    }
    int getMonthlyFee() override {
        if (isMorningMembership) {
            return monthly_fee * 0.75;
        }
        return monthly_fee;
    }
    void print() override {
        Membership::print();
        cout << getMonthlyFee();
        cout << " - " << isMorningMembership ;
    }
};
class VIPMembership : public Membership{
    bool isUsingSpa;
    int trainerHours;
public:
    VIPMembership(Membership &m, bool isUsingSpa = false, int trainerHours = 0)
    : Membership(m) {
        this->isUsingSpa = isUsingSpa;
        this->trainerHours = trainerHours;
    }
    int getMonthlyFee() override {
        if (isUsingSpa) {
            return monthly_fee + 1000 + trainerHours * 150;
        }
        return monthly_fee + trainerHours * 150;
    }
    void print() override {
        Membership::print();
        cout << getMonthlyFee();
        cout << isUsingSpa << " - "<< trainerHours * 150;
    }
};


int main()
{
    int n;
    cin >> n;
    char name[50];
    char dateJoined[11];
    int membershipPrice;

    for (int i = 0; i < n; i++)
    {
        cin >> name;
        cin >> dateJoined;
        cin >> membershipPrice;

        Membership m = Membership(name, dateJoined, membershipPrice);

        if (i % 2)
        {
            bool isMorningMembership;
            cin >> isMorningMembership;
            BasicMembership bm = BasicMembership(m, isMorningMembership);
            bm.print();
        }
        else
        {
            bool usesSpa;
            int numOfHoursWithTrainer;
            cin >> usesSpa >> numOfHoursWithTrainer;
            VIPMembership vm = VIPMembership(m, usesSpa, numOfHoursWithTrainer);
            vm.print();
        }
    }

    return 0;
}