#include <cstring>
#include <iostream>
#include <ostream>
using namespace std;

class Pizza {
protected:
  char name[20];
  char ingredients[100];
  double inPrice;
public:
  Pizza(const char *name = " ", const char *ingredients = " ", double inPrice = 0) {
    strcpy(this->name, name);
    strcpy(this->ingredients, ingredients);
    this->inPrice = inPrice;
  }
  virtual double price() = 0;
  bool operator<(Pizza &other) {
    return this->price() < other.price();
  }
  char *getName() {
    return name;
  }
  char *getIngredients() {
    return ingredients;
  }
  double getPrice() {
    return inPrice;
  }
  virtual ~Pizza(){}
};
enum Size {
  small, large, family
};
class FlatPizza : public Pizza {
protected:
  Size size;
public:
  FlatPizza(const char *name = " ", const char *ingredients = " ", double inPrice = 0, Size size = small)
    :Pizza(name, ingredients, inPrice) {
    this->size = size;
  }
  double price() override {
    double base = inPrice;
    if (size == small) return base * 1.1;
    else if (size == large) return base * 1.2;
    else if (size == family) return base * 1.3;
    return base;
  }

  friend ostream & operator<<(ostream &os, FlatPizza &obj) {
    os << obj.name << ": " << obj.ingredients << ", ";
    if (obj.size == 0) {
        os << "small ";
    }
    else if (obj.size == 1) {
      os << "large ";
    }
    else if (obj.size == 2) {
      os << "family ";
    }
    os << "- " << obj.price() << endl;
    return os;
  }
  Size getSize() {
    return size;
  }
};
class FoldedPizza : public Pizza {
protected:
  bool whiteFlour;
public:
    FoldedPizza(const char *name = " ", const char *ingredients = " ", double inPrice = 0,
      bool whiteFlour = true) : Pizza(name, ingredients, inPrice) {
      this->whiteFlour = whiteFlour;
    }
  double price() override {
      return inPrice * (whiteFlour ? 1.1 : 1.3);
    }
  void setWhiteFlour(bool whiteFlour) {
        this->whiteFlour = whiteFlour;
      }
  friend ostream & operator<<(ostream &os, FoldedPizza &obj) {
    os << obj.name << ": " << obj.ingredients << ", ";
    if (obj.whiteFlour) {
      os << "wf - ";
    }
    else {
      os << "nwf - ";
    }
    os << obj.price() << endl;
    return os;
  }
};
  void expensivePizza(Pizza **pizzas, int n) {
    double max_price = -1;
    int max_index = 0;
    for (int i = 0; i < n; ++i) {
      if (pizzas[i]->price() > max_price) {
        max_price = pizzas[i]->price();
        max_index = i;
      }
    }
    if (FlatPizza *fp = dynamic_cast<FlatPizza*>(pizzas[max_index])) {
      // FlatPizza f(pizzas[max_index]->getName(), pizzas[max_index]->getIngredients(), pizzas[max_index]->getPrice(), pizzas[max_index].FlatPizza::getSize());
        cout << *fp;
    }
    else if (FoldedPizza *fp = dynamic_cast<FoldedPizza*>(pizzas[max_index])) {
        cout << *fp;
    }


  }
// Testing

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
