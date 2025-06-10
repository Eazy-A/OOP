#include <iostream>
#include <cstring>
#include <ostream>
using namespace std;

class Book {
protected:
	char ISBN[20];
	char title[50];
	char author[30];
	double price;
public:
	Book(const char *ISBN="", const char *title="", const char *author="", double price = 0) {
		strcpy(this->ISBN, ISBN);
		strcpy(this->title, title);
		strcpy(this->author, author);
		this->price = price;
	}
	Book(const Book &other) {
		strcpy(this->ISBN, other.ISBN);
		strcpy(this->title, other.title);
		strcpy(this->author, other.author);
		this->price = other.price;
	}
	Book const &operator=(Book const &other) {
		if (this != &other) {
			strcpy(this->ISBN, other.ISBN);
			strcpy(this->title, other.title);
			strcpy(this->author, other.author);
			this->price = other.price;
		}
		return *this;
	}
	void setISBN(char *ISBN) {
		strcpy(this->ISBN, ISBN);
	}
	friend ostream & operator<<(ostream &os,  Book &obj) {
		//007-6092006565: Thinking in C++, Bruce Eckel 59.8
		os << obj.ISBN << ": " << obj.title << ", " << obj.author << " " << obj.bookPrice() << endl;
		return os;
	}
	bool operator>(Book &b) {
		if (this->price > b.price) {
			return true;
		}
		return false;
	}
	virtual double bookPrice()  = 0;
};

class OnlineBook : public Book{
	char *url;
	int size;
public:
	OnlineBook(const char *ISBN="", const char *title="", const char *author="", double price = 0, const char *url="", int size = 0)
		:Book(ISBN, title, author, price) {
		this->url = new char[strlen(url)+1];
		strcpy(this->url, url);
		this->size = size;
	}
	OnlineBook(const OnlineBook &other) : Book(other){
		url = new char[strlen(other.url)+1];
		strcpy(this->url, other.url);
		this->size = other.size;
	}
	OnlineBook const &operator=(OnlineBook const &other) {
		if (this != &other) {
			Book::operator=(other);
			delete [] url;
			url = new char[strlen(other.url)+1];
			strcpy(this->url, other.url);
			this->size = other.size;
		}
		return *this;
	}
	// ~OnlineBook() {
	// 	delete [] url; //segmentation fault
	// }
	double bookPrice() override{
		if (size > 20) {
			return price * 1.2;
		}
		return price;
	}
};

class PrintBook : public Book {
	double weight;
	bool inStock;
public:
	PrintBook(const char *ISBN="", const char *title="", const char *author="", double price = 0, double weight = 0, bool inStock = false)
		:Book(ISBN, title, author, price) {
		this->weight = weight;
		this->inStock = inStock;
	}
	double bookPrice() override{
		if (weight > 0.7) {
			return price * 1.15;
		}
		return price;
	}
};
void mostExpensiveBook (Book** books, int n) {
	int max_index = 0;
	int online_counter = 0;
	int printed_counter = 0;
	Book *max_obj = books[0];
	for (int i = 0; i < n; ++i) {
		if (dynamic_cast<OnlineBook*>(books[i])) {
			online_counter ++;
		}
		else {
			printed_counter ++;
		}
		if (max_obj->bookPrice() < books[i]->bookPrice()) {
			max_obj = books[i];
		}
		// if (books[max_index]->bookPrice() < books[i]->bookPrice()) {
		// 	max_index = i;
		// }
	}
	cout << "FINKI-Education" << endl;
	cout << "Total number of online books: " << online_counter << endl;
	cout << "Total number of print books: " << printed_counter << endl;
	cout << "The most expensive book is: " << endl;
	cout << *max_obj;
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
