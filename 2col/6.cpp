#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Game {
protected:
    char name[100];
    double price;
    bool onSale;
public:
    Game(const char *name = " ", double price = 0, bool onSale = false) {
        strcpy(this->name, name);
        this->price = price;
        this->onSale = onSale;
    }
    Game(Game &other) {
        strcpy(this->name, other.name);
        this->price = other.price;
        this->onSale = other.onSale;
    }
    friend ostream& operator<<(ostream &os, const Game &obj) {
        os << "Game: " << obj.name << ", regular price: $" << obj.price;
        if (obj.onSale) {
            os << ", bought on sale";
        }
        return os;
    }

    friend istream& operator>>(istream &is, Game &obj) {
        is.ignore();
        is.getline(obj.name, 100);
        is >> obj.price >> obj.onSale;
        return is;
    }

    bool operator==(const Game &other) const {
        return strcmp(this->name, other.name) == 0;
    }

    virtual ~Game() {}
    friend class User;
};

class SubscriptionGame : public Game {
    double monthlyFee;
    int month;
    int year;
public:
    SubscriptionGame(const char *name = " ", double price = 0, bool onSale = false, double monthlyFee = 0, int month = 1, int year = 2000)
        : Game(name, price, onSale) {
        this->monthlyFee = monthlyFee;
        this->month = month;
        this->year = year;
    }
    SubscriptionGame(SubscriptionGame &other) : Game(other){
        this->monthlyFee = other.monthlyFee;
        this->month = other.month;
        this->year = other.year;
    }
    friend ostream& operator<<(ostream &os, const SubscriptionGame &obj) {
        os << "Game: " << obj.name << ", regular price: $" << obj.price;
        if (obj.onSale) {
            os << ", bought on sale, ";
        } else {
            os << ", ";
        }
        os << "monthly fee: $" << obj.monthlyFee << ", purchased: " << obj.month << "-" << obj.year << endl;
        return os;
    }

    friend istream& operator>>(istream &is, SubscriptionGame &obj) {
        is.ignore();
        is.getline(obj.name, 100);
        is >> obj.price >> obj.onSale >> obj.monthlyFee >> obj.month >> obj.year;
        return is;
    }

    bool operator==(const SubscriptionGame &other) const {
        return strcmp(this->name, other.name) == 0;
    }

    friend class User;
};

class ExistingGame : public exception {
    string msg;
public:
    ExistingGame(string msg = "") {
        this->msg = msg;
    }
    void message() {
        cout << msg << endl;
    }
};

class User {
    char username[100];
    Game **boughtGames;
    int n;
public:
    User(const char *username = " ", Game **boughtGames = nullptr, int n = 0) {
        strcpy(this->username, username);
        this->boughtGames = new Game*[n];
        for (int i = 0; i < n; ++i) {
            this->boughtGames[i] = boughtGames[i];
        }
        this->n = n;
    }

    User(const User &other) {
        strcpy(this->username, other.username);
        this->boughtGames = new Game*[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->boughtGames[i] = other.boughtGames[i];
        }
        this->n = other.n;
    }

    User& operator+=(Game &newGame) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(boughtGames[i]->name, newGame.name) == 0) {
                throw ExistingGame("The game is already in the collection");
            }
        }
        Game **temp = new Game*[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = boughtGames[i];
        }
        temp[n] = &newGame;
        delete[] boughtGames;
        boughtGames = temp;
        n++;
        return *this;
    }

    double total_spent() {
        double total = 0;
        for (int i = 0; i < n; ++i) {
            double gamePrice = boughtGames[i]->price;
            if (boughtGames[i]->onSale) {
                gamePrice = gamePrice * 0.3;
            }
            total += gamePrice;

            SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(boughtGames[i]);
            if (sg) {
                total = total + ((2018 - sg->year) * 12 + (5 - sg->month)) * sg->monthlyFee;
            }
        }
        return total;
    }

    friend ostream& operator<<(ostream &os, const User &obj) {
        os << endl;
        os << "User: " << obj.username << endl;
        for (int i = 0; i < obj.n; ++i) {
            SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(obj.boughtGames[i]);
            if (sg) {
                os << "- " << *sg << endl;
            } else {
                os << "- " << *obj.boughtGames[i] << endl;
            }
        }
        return os;
    }

    ~User() {
        delete[] boughtGames;
    }
};
int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}