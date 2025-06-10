#include<iostream>
#include <string.h>
#include <string>
class Demonstrator;
class Predavach;
using namespace std;
class Kurs {
private:
    char ime[100];
    int krediti;
public:
    Kurs(const char *ime = " ", int krediti = 0) {
        strcpy(this->ime, ime);
        this->krediti = krediti;
    }
    void print() {
        cout << ime <<" " << krediti << "ECTS";
    }
    friend Demonstrator;
};
class Student {
protected:
    int index;
    int *ocenki;
    int br_ocenki;
public:
    Student(int index = 0, int *ocenki = nullptr, int br_ocenki = 0) {
        this->index = index;
        this->ocenki = new int [br_ocenki];
        for (int i = 0; i < br_ocenki; ++i) {
            this->ocenki[i] = ocenki[i];
        }
        this->br_ocenki = br_ocenki;
    }
    Student(Student &other) {
        this->index = other.index;
        this->ocenki = new int [other.br_ocenki];
        for (int i = 0; i < other.br_ocenki; ++i) {
            this->ocenki[i] = other.ocenki[i];
        }
    }
    ~Student() {
        delete [] ocenki;
    }
    Student const &operator=(Student &other) {
       if (this != &other) {
           delete [] ocenki;
           this->index = other.index;
           this->ocenki = new int [other.br_ocenki];
           for (int i = 0; i < other.br_ocenki; ++i) {
               this->ocenki[i] = other.ocenki[i];
           }
       }
        return *this;
    }
    virtual int getBodovi() {
        if (br_ocenki == 0) return 0;
        double counter = 0;
        double result = 0;
        for (int i = 0; i < br_ocenki; ++i) {
            if (ocenki[i] > 5) {
                counter++;
            }
        }
        result = counter/br_ocenki*100;
        return result;
    }
    virtual void pecati() {
        cout<<index;
    }
};
class Predavach {
protected:
    char *ime;
    Kurs *kursevi;
    int br_kursevi;
public:
    Predavach(const char *ime = " ", Kurs *kursevi = nullptr, int br_kursevi = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->kursevi = new Kurs[br_kursevi];
        for (int i = 0; i < br_kursevi; ++i) {
            this->kursevi[i] = kursevi[i];
        }
        this->br_kursevi = br_kursevi;
    }
    Predavach(Predavach &other) {
        this->ime = new char[strlen(other.ime) + 1];
        strcpy(this->ime, other.ime);
        this->kursevi = new Kurs[other.br_kursevi];
        for (int i = 0; i < other.br_kursevi; ++i) {
            this->kursevi[i] = other.kursevi[i];
        }
        this->br_kursevi = other.br_kursevi;
    }
    Predavach const &operator=(Predavach &other) {
        if (this != &other) {
            delete [] ime;
            delete [] kursevi;
            this->ime = new char[strlen(other.ime) + 1];
            strcpy(this->ime, other.ime);
            this->kursevi = new Kurs[other.br_kursevi];
            for (int i = 0; i < other.br_kursevi; ++i) {
                this->kursevi[i] = other.kursevi[i];
            }
            this->br_kursevi = other.br_kursevi;
        }
    }
    ~Predavach() {
        delete [] ime;
        delete [] kursevi;
    }
    int get_br_kursevi() {
        return br_kursevi;
    }
    friend Student;
};
class NoCourseException : public exception {
private:
    int index;
public:
    NoCourseException(int index) {
        this->index = index;
    }
    void print() {
        cout << "Demonstratorot so indeks " << index << " ne drzi laboratoriski vezbi" << endl;
    }
};
class Demonstrator : public Student, public Predavach{
private:
    int br_casovi;
public:
    Demonstrator(int index = 0, int *ocenki = nullptr, int br_ocenki = 0,const char *ime = " ", Kurs *kursevi = nullptr, int br_kursevi = 0, int br_casovi = 0)
        : Student(index, ocenki, br_ocenki), Predavach(ime, kursevi, br_kursevi) {
        this->br_casovi = br_casovi;
    }
    int getBodovi() override {
        int bodovi = Student::getBodovi();
        if (br_kursevi == 0) {
            throw NoCourseException(index);
        }
        bodovi += (20 * br_casovi) / br_kursevi;
        return bodovi;
    }
    void pecati() override {
        Student::pecati();
        cout <<": "<< ime << " (";
        for (int i = 0; i < br_kursevi; ++i) {
            kursevi[i].print();
            if (i < br_kursevi - 1) {
                cout << ", ";
            }
        }
        cout << ")";
    }
    bool drziKurs(const char *kurs) {
        for (int i = 0; i < br_kursevi; ++i) {
            if (strcmp(kursevi[i].ime, kurs) == 0)
                return true;
        }
        return false;
    }
    friend Kurs;
};

Student& vratiNajdobroRangiran(Student ** studenti, int n ) {
    int max_index = 0;
    int max_bodovi = studenti[0]->getBodovi();
    for (int i = 0; i < n; ++i) {
        int bodovi;
        try {
            bodovi = studenti[i]->getBodovi();
        } catch (NoCourseException &e) {
            e.print();
            bodovi = 0;
        }
        if (bodovi > max_bodovi){
            max_bodovi = bodovi;
            max_index = i;
        }
    }
    return *studenti[max_index];
}
void pecatiDemonstratoriKurs (char* kurs, Student** studenti, int n) {
    for (int i = 0; i < n; ++i) {
        Demonstrator *d = dynamic_cast<Demonstrator*>(studenti[i]);
        if (d && d->drziKurs(kurs)) {
            d->pecati();
            cout << endl;
        }
    }
}
int main(){

Kurs kursevi[10];
int indeks,brojKursevi, ocenki[20],ocenka,brojOcenki,tip,brojCasovi,krediti;
char ime[20],imeIPrezime[50];

cin>>tip;

if (tip==1) //test class Demonstrator
{
    cout<<"-----TEST Demonstrator-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
cout<<"Objekt od klasata Demonstrator e kreiran";

} else if (tip==2) //funkcija pecati vo Student
{
    cout<<"-----TEST pecati-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }

Student s(indeks,ocenki,brojOcenki);
s.pecati();

} else if (tip==3) //funkcija getVkupnaOcenka vo Student
{
     cout<<"-----TEST getVkupnaOcenka-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
Student s(indeks,ocenki,brojOcenki);
cout<<"Broj na bodovi: "<<s.getBodovi()<<endl;

} else if (tip==4) //funkcija getVkupnaOcenka vo Demonstrator
{
  cout<<"-----TEST getVkupnaOcenka-----"<<endl;
  cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
cout<<"Broj na bodovi: "<<d.getBodovi()<<endl;

} else if (tip==5) //funkcija pecati vo Demonstrator
{
  cout<<"-----TEST pecati -----"<<endl;
 cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
d.pecati();

} else if (tip==6) //site klasi
{
    cout<<"-----TEST Student i Demonstrator-----"<<endl;
 cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Student *s=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
s->pecati();
cout<<"\nBroj na bodovi: "<<s->getBodovi()<<endl;
delete s;


} else if (tip==7) //funkcija vratiNajdobroRangiran
{
    cout<<"-----TEST vratiNajdobroRangiran-----"<<endl;
int k, opt;
cin>>k;
Student **studenti=new Student*[k];
for (int j=0;j<k;j++){
    cin>>opt; //1 Student 2 Demonstrator
      cin>>indeks>>brojOcenki;
   for (int i=0;i<brojOcenki;i++)
      {
         cin>>ocenka;
         ocenki[i]=ocenka;
      }
   if (opt==1){
    studenti[j]=new Student(indeks,ocenki,brojOcenki);
   }else{
   cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++)
      {
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
      }
      cin>>brojCasovi;
   studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
   }
}
Student& najdobar=vratiNajdobroRangiran(studenti,k);
cout<<"Maksimalniot broj na bodovi e:"<<najdobar.getBodovi();
cout<<"\nNajdobro rangiran:";
najdobar.pecati();

for (int j=0;j<k;j++) delete studenti[j];
 delete [] studenti;

} else if (tip==8) //funkcija pecatiDemonstratoriKurs
{
cout<<"-----TEST pecatiDemonstratoriKurs-----"<<endl;
int k, opt;
cin>>k;
Student **studenti=new Student*[k];
for (int j=0;j<k;j++){
    cin>>opt; //1 Student 2 Demonstrator
      cin>>indeks>>brojOcenki;
   for (int i=0;i<brojOcenki;i++)
      {
         cin>>ocenka;
         ocenki[i]=ocenka;
      }
   if (opt==1){
    studenti[j]=new Student(indeks,ocenki,brojOcenki);
   }else{
   cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++)
      {
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
      }
      cin>>brojCasovi;
   studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
   }
}
char kurs[20];
cin>>kurs;
cout<<"Demonstratori na "<<kurs<<" se:"<<endl;
pecatiDemonstratoriKurs (kurs,studenti,k);
for (int j=0;j<k;j++) delete studenti[j];
 delete [] studenti;

}


return 0;
}