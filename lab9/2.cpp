#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class VehicleRegistration {
private:
    string registration_number;
    string manufacture_date;
    int mileage;
    int engine_power;
    int vehicle_age;
    double emission_level;

public:
    // Default constructor
    VehicleRegistration() : registration_number(""), manufacture_date(""), mileage(0), engine_power(0), vehicle_age(0), emission_level(0.0) {}

    // Parameterized constructor
    VehicleRegistration(string reg, string date, int m, int ep, int age, double em)
        : registration_number(reg), manufacture_date(date), mileage(m), engine_power(ep), vehicle_age(age), emission_level(em) {}

    // Copy constructor
    VehicleRegistration(const VehicleRegistration& other) {
        registration_number = other.registration_number;
        manufacture_date = other.manufacture_date;
        mileage = other.mileage;
        engine_power = other.engine_power;
        vehicle_age = other.vehicle_age;
        emission_level = other.emission_level;
    }

    // Assignment operator
    VehicleRegistration& operator=(const VehicleRegistration& other) {
        if (this != &other) {
            registration_number = other.registration_number;
            manufacture_date = other.manufacture_date;
            mileage = other.mileage;
            engine_power = other.engine_power;
            vehicle_age = other.vehicle_age;
            emission_level = other.emission_level;
        }
        return *this;
    }

    // Input operator
    friend istream& operator>>(istream& in, VehicleRegistration& v) {
        in >> v.registration_number >> v.manufacture_date >> v.mileage >> v.engine_power >> v.vehicle_age >> v.emission_level;
        return in;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const VehicleRegistration& v) {
        out << "Vehicle Reg: " << v.registration_number << " " << v.manufacture_date
            << " | Mileage " << v.mileage << "km Power " << v.engine_power << "hp Age "
            << v.vehicle_age << "y Emission " << v.emission_level << "g/km";
        return out;
    }

    string VehicleCategory() const {
        if (mileage > 250000 || vehicle_age > 20 || emission_level > 120.0 || engine_power < 60)
            return "Restricted";
        if (mileage > 150000 || vehicle_age > 15 || emission_level > 90.0 || engine_power < 80)
            return "Limited";
        return "Approved";
    }
};

VehicleRegistration* FilterByVehicleCategory(VehicleRegistration* vehicles, int n, const string& category, int& count) {
    count = 0;
    for (int i = 0; i < n; ++i) {
        if (vehicles[i].VehicleCategory() == category)
            ++count;
    }

    VehicleRegistration* filtered = new VehicleRegistration[count];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (vehicles[i].VehicleCategory() == category) {
            filtered[j++] = vehicles[i];
        }
    }
    return filtered;
}

int main() {
    ifstream fin("text.txt");
    if (!fin) {
        cerr << "Failed to open text.txt" << endl;
        return 1;
    }

    int test_case;
    fin >> test_case;

    if (test_case == 1) {
        int n;
        fin >> n;
        VehicleRegistration* vehicles = new VehicleRegistration[n];

        for (int i = 0; i < n; ++i) {
            fin >> vehicles[i];
        }

        string category;
        fin >> category;

        int filtered_count;
        VehicleRegistration* filtered = FilterByVehicleCategory(vehicles, n, category, filtered_count);

        for (int i = 0; i < filtered_count; ++i) {
            cout << filtered[i] << endl;
        }

        delete[] vehicles;
        delete[] filtered;
    }

    return 0;
}
