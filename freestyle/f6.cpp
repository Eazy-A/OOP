#include <iostream>
#include <cstring>
using namespace std;

class email {
private:
    char to[100];
    char from[100];
    char subject[150];
    char body[1000];
public:
    email(char *_to, char *_from, char *_subject, char *_body) {
        strcpy(to, _to);
        strcpy(from, _from);
        strcpy(subject, _subject);
        strcpy(body, _body);
    }
    void setTo(char *n) {
        strcpy(to, n);
    }
    void setFrom(char *n) {
        strcpy(from, n);
    }
    void setSubject(char *n) {
        strcpy(subject, n);
    }
    void setBody(char *n) {
        strcpy(body, n);
    }
    void *getTo(){return to;}
    void *getFrom(){return from;}
    void *getSubject(){return subject;}
    void *getbody(){return body;}
    void print() {
        cout<<"From: "<<from<<endl;
        cout<<"Subject: "<<subject<<endl;
        cout<<"Body: "<<body<<endl;
    }
};
    bool isValidAdress(char *to) {
        int len = strlen(to);
        bool flag = false;
        for (int i=0; i<len; i++) {
            if (to[i] == '@') {
                flag = true;
                break;
            }
        }
        if (flag) return true;
        else return false;

    }

int main() {
    char to[100], from[100], subject[150], body[100];
        cout<<"To: ";
        cin>>to;
    if (isValidAdress(to)) {
        cout<<"From: ";
        cin>>from;
        cin.ignore();
        cout<<"Subject: ";
        cin.getline(subject,150);
        cout<<"Body: ";
        cin.getline(body,1000);
        email poraka (to, from, subject, body);
        poraka.print();
    }
    else {
            cout<<"Invalid adress!"<<endl;
        }
    return 0;
}