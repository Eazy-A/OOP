#include <iostream>
#include <cstring>
#include <ostream>
using namespace std;

class Matrix {
    float elements[10][10];
    int n;
public:
    Matrix() {
    }
    Matrix(float **elements, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                this -> elements[i][j] = elements[i][j];
            }
        }
        this -> n = n;
    }
    //operator +
    Matrix operator*(const Matrix &m) {
        Matrix result;
        result.n = n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result.elements[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    result.elements[i][j] += elements[i][k] * m.elements[k][j];
                }
            }
        }
        return result;
    }
    //operator -
    Matrix operator-(const Matrix &m) {
        Matrix result;
        result.n = n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result.elements[i][j] = elements[i][j] - m.elements[i][j];
            }
        }
        return result;
    }
    //operator +
    Matrix operator+(const Matrix &m) {
        Matrix result;
        result.n = n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result.elements[i][j] = elements[i][j] + m.elements[i][j];
            }
        }
        return result;
    }
    //scalar
    Matrix operator+(float number) {
        Matrix result;
        result.n = n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result.elements[i][j] = elements[i][j] + number;
            }
        }
        return result;
    }
    //operator >>
    friend istream &operator>>(istream &in, Matrix &m) {
        in >> m.n;
        for (int i = 0; i < m.n; ++i)
            for (int j = 0; j < m.n; ++j)
                in >> m.elements[i][j];
        return in;
    }
    //operator <<
    friend ostream &operator<<(ostream &out, const Matrix &m) {
        for (int i = 0; i < m.n; ++i) {
            for (int j = 0; j < m.n; ++j) {
                out << m.elements[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
};
int main() {
    Matrix A, B, C;
    int n;
    cin >> A;
    cin >> B;
    cin >> C;
    cout<<A-(B*C)+2;
}