    #include <iostream>
#include <cstring>
using namespace std;

class DocumentSigner {
    char name[50];
    char lastname[50];
    char embg[14];
public:
    DocumentSigner(const char *name = "", const char *lastname = "", const char *embg = "") {
        strcpy(this->name, name);
        strcpy(this->lastname, lastname);
        strcpy(this->embg, embg);
    }

    const char* getEmbg() const {
        return embg;
    }
};

class Response {
    DocumentSigner signers[100];
    int n;
public:
    Response(int n = 0, DocumentSigner signers[] = nullptr) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->signers[i] = signers[i];
        }
    }

    bool hasDuplicateEmbg() const {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (strcmp(signers[i].getEmbg(), signers[j].getEmbg()) == 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    DocumentSigner signers[] = {
        DocumentSigner("John", "Doe", "1234567890123"),
        DocumentSigner("Jane", "Smith", "9876543210987"),
        DocumentSigner("Alice", "Johnson", "1234567890123")
    };

    Response response(3, signers);

    if (response.hasDuplicateEmbg()) {
        cout << "Duplicate EMBG found." << endl;
    } else {
        cout << "No duplicate EMBG found." << endl;
    }

    return 0;
}
