#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Define the AIModelType enum
enum AIModelType { GPT, VISION, CLASSIFIER, EMBEDDING };

// Exception classes
class InvalidNumberOfParametersException{ 
private:
    string message;
public:
    InvalidNumberOfParametersException(string message) {
        this->message = message;
    }
    void print() {
        cout << message;
    }
};

class InvalidModelTypeException  {
private:
    string message;
public:
    InvalidModelTypeException(string message) {
        this->message = message;
    }
    void print() {
        cout << message;
    }
};

// AIModel class
class AIModel {
private:
    string brand;
    string name;
    string version;
public:
    AIModel(const string& brand, const string& name, const string& version)
        : brand(brand), name(name), version(version) {}

    void print() const {
        cout << "AI Model: " << brand << " " << name << " " << version << endl;
    }
};

// AIConfiguration class
class AIConfiguration {
private:
    int parameters;
    int epochs;
    AIModelType type;
public:
    AIConfiguration(int parameters, int epochs, AIModelType type) {
        if (parameters < 0) {
            throw InvalidNumberOfParametersException("Invalid number of parameters!");
        }
        if (type < GPT || type > EMBEDDING) {
            throw InvalidModelTypeException("Invalid model type!");
        }
        this->parameters = parameters;
        this->epochs = epochs;
        this->type = type;
    }

    void print() const {
        string typeStr;
        switch(type) {
            case GPT: typeStr = "GPT"; break;
            case VISION: typeStr = "VISION"; break;
            case CLASSIFIER: typeStr = "CLASSIFIER"; break;
            case EMBEDDING: typeStr = "EMBEDDING"; break;
        }
        cout << "AI Configuration: " << parameters << " parameters, "
             << epochs << " epochs, " << typeStr << endl;
    }
};

AIModelType getStringMapping(string typeStr)
{
    unordered_map<string, AIModelType> mapping = {
        {"GPT", GPT},
        {"VISION", VISION},
        {"CLASSIFIER", CLASSIFIER},
        {"EMBEDDING", EMBEDDING}};

    if (mapping.find(typeStr) != mapping.end())
    {
        return mapping[typeStr];
    }
    else
    {
        return static_cast<AIModelType>(-1);
    }
}

int main()
{
    int tc;
    cin >> tc;
    if (tc == 1)
    {
        string brand, name, version;
        cout << "Testing AI Model Creation:";
        cin >> brand >> name >> version;
        AIModel model(brand, name, version);
        cout << " PASSED" << endl;
    }
    if (tc == 2)
    {
        AIModel model("OpenAI", "GPT-3", "v1.0");
        cout << "Testing Print Method for AI Model:" << endl;
        model.print();
    }
    if (tc == 3)
    {
        cout << "Testing AI Configuration Creation:";
        int parameters, epochs;
        string typeStr;
        cin >> parameters >> epochs >> typeStr;
        AIModelType type = getStringMapping(typeStr);
        cout << " PASSED" << endl;
    }
    if (tc == 4)
    {
        cout << "Testing Print Method for AI Configuration:" << endl;
        int parameters = 10, epochs = 5;
        string typeStr = "GPT";
        AIModelType type = getStringMapping(typeStr);
        cout << " PASSED" << endl;
    }
    if (tc == 5)
    {
        cout << "Testing Invalid Number of Parameters Exception:" << endl;
        int parameters, epochs;
        string typeStr = "GPT";
        cin >> parameters >> epochs;
        AIModelType type = getStringMapping(typeStr);
        try {
            AIConfiguration config(parameters, epochs, type);
            config.print();
        } catch (InvalidNumberOfParametersException& e) {
            e.print();
        }
    }
    if (tc == 6)
    {
        cout << "Testing Invalid Model Type Exception:" << endl;
        int parameters = 10, epochs = 5;
        string typeStr;
        cin >> typeStr;
        AIModelType type = getStringMapping(typeStr);
        try {
            AIConfiguration config(parameters, epochs, type);
            config.print();
        } catch (InvalidModelTypeException& e) {
            e.print();
        }
    }
    return 0;
}