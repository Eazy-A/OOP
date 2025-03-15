#include <iostream>
#include <cmath>
using namespace std;


class Triangle {
private:
    int a, b, c;
public:
    Triangle() {
      a=b=c=7;
    }
    Triangle(int aa, int bb, int cc) {
        a = aa;
        b = bb;
        c = cc;
    }
    int perimeter() {
        return a+b+c;
    }
    double plostina() {
        float s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};
int main() {
    int a,b,c;
    cin>>a>>b>>c;
    Triangle t(a, b, c);
    cout<<t.perimeter()<<endl;
    cout<<t.plostina()<<endl;
    return 0;
}