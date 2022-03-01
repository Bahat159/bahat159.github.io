#include <iostream>


struct Complex {
    Complex(double r, double i) : re(r), im(i) {}
    Complex operator+(Complex &other);
    void Display() { std::cout << re << ", " << im << std::endl; }
    private:
        double re, im;
};

Complex Complex::operator+(Complex &other) {
    return Complex(re + other.re, im + other.im);
}
