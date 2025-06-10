#include <iostream>
#include <cstring>
#include <ostream>
class FINKI_bookstore;
using namespace std;

enum typeC {
  standard, loyal, vip
};

class Customer {
private:
  char name[50];
  char email[50];
  typeC typec;
  static int loyalDiscount; // loyal customers discount
  int bonusDiscount;
  int numProducts;

public:
  Customer(const char *name = "", const char *email = "", typeC typec = standard,
    int numProducts = 0, int discount = 0, int bonusDiscount = 0) {
    strcpy(this->name, name);
    strcpy(this->email, email);
    this->typec = typec;
    this->bonusDiscount = 20; // bonus for vips
    this->numProducts = numProducts;
  }

  friend ostream & operator<<(ostream &os, const Customer &o) {
    os << o.name << endl;
    os << o.email << endl;
    os << o.numProducts << endl;

    if (o.typec == standard) {
      os << "standard 0" << endl;
    }
    else if (o.typec == loyal) {
      os << "loyal " << loyalDiscount << endl;
    }
    else if (o.typec == vip) {
      os << "vip " << loyalDiscount + o.bonusDiscount << endl;
    }
    return os;
  }

  void setDiscount1(int discount){
    loyalDiscount = discount;
  }

  friend class FINKI_bookstore;
};

int Customer::loyalDiscount = 10;

class UserExistsException : public exception {
  string msg;
public:
  UserExistsException(string msg = "") {
    this->msg = msg;
  }
  void print() {
    cout << msg << endl;
  }
};

class FINKI_bookstore {
  Customer *registeredCustomers;
  int numCustomers;

public:
  FINKI_bookstore(Customer *registeredCustomers = nullptr, int numCustomers = 0) {
    this->numCustomers = numCustomers;
    if (numCustomers > 0 && registeredCustomers != nullptr) {
      this->registeredCustomers = new Customer[numCustomers];
      for (int i = 0; i < numCustomers; ++i) {
        this->registeredCustomers[i] = registeredCustomers[i];
      }
    } else {
      this->registeredCustomers = nullptr;
    }
  }

  FINKI_bookstore(const FINKI_bookstore &other) {
    this->numCustomers = other.numCustomers;
    if (numCustomers > 0) {
      this->registeredCustomers = new Customer[numCustomers];
      for (int i = 0; i < numCustomers; ++i) {
        this->registeredCustomers[i] = other.registeredCustomers[i];
      }
    } else {
      this->registeredCustomers = nullptr;
    }
  }

  FINKI_bookstore& operator=(const FINKI_bookstore &other) {
    if (this != &other) {
      delete[] registeredCustomers;
      this->numCustomers = other.numCustomers;
      if (numCustomers > 0) {
        this->registeredCustomers = new Customer[numCustomers];
        for (int i = 0; i < numCustomers; ++i) {
          this->registeredCustomers[i] = other.registeredCustomers[i];
        }
      } else {
        this->registeredCustomers = nullptr;
      }
    }
    return *this;
  }

  FINKI_bookstore& operator+=(Customer &newCustomer) {
    // if customer already exist
    for (int i = 0; i < numCustomers; ++i) {
      if (strcmp(newCustomer.email, registeredCustomers[i].email) == 0) {
        throw UserExistsException("The user already exists in the list!");
      }
    }
    // add new customer
    Customer *temp = new Customer[numCustomers + 1];
    for (int i = 0; i < numCustomers; ++i) {
      temp[i] = registeredCustomers[i];
    }
    temp[numCustomers] = newCustomer;
    delete[] registeredCustomers;
    registeredCustomers = temp;
    numCustomers++;
    return *this;
  }

  ~FINKI_bookstore() {
    delete[] registeredCustomers;
  }

  void update() {
    for (int i = 0; i < numCustomers; ++i) {
      // Standard customers with 5+ products become loyal
      if (registeredCustomers[i].typec == standard && registeredCustomers[i].numProducts >= 5) {
        registeredCustomers[i].typec = loyal;
      }
      // Loyal customers with 10+ products become VIP
      else if (registeredCustomers[i].typec == loyal && registeredCustomers[i].numProducts >= 10) {
        registeredCustomers[i].typec = vip;
      }
    }
  }

  void setCustomers(Customer *registeredCustomers, int numCustomers) {
    delete[] this->registeredCustomers;
    this->numCustomers = numCustomers;
    if (numCustomers > 0) {
      this->registeredCustomers = new Customer[numCustomers];
      for (int i = 0; i < numCustomers; ++i) {
        this->registeredCustomers[i] = registeredCustomers[i];
      }
    } else {
      this->registeredCustomers = nullptr;
    }
  }

  friend ostream & operator<<(ostream &os, const FINKI_bookstore &o) {
    for (int i = 0; i < o.numCustomers; ++i) {
      os << o.registeredCustomers[i];
    }
    return os;
  }
};

int MAX = 50;

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;

  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;
  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << fc << endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    try {
      Customer c(name, email, (typeC) tC, numProducts);
      fc+=c;
    }
    catch (UserExistsException &e) {
      e.print();
    }

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;
}