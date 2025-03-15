#include <iostream>
#include <cmath>
using namespace std;

class triangle {
    int a,b,c;
public:
    triangle(int x, int y, int z) {
        a = x;
        b = y;
        c = z;
    }
    int perimeter() {
        return a+b+c;
    }
    float area() {
        float s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};
int main() {
    int a,b,c;
    cin>>a>>b>>c;
    triangle t(a,b,c);
    cout<<t.area()<<endl;
    cout<<t.perimeter()<<endl;
    return 0;
}