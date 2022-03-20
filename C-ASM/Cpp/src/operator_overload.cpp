#include <iostream>
#include "../include/operator_overloading.h"

int main() {
    Complex a = Complex(1.2, 3.4);
    Complex b = Complex(5.6, 7.8);
    Complex c = Complex(0.0, 0.0);

    c = a + b;
    c.Display();

    std::cout << "================================"<<"\n";

    Int i;
    i.operator++(25);

    Point_x pt1, pt2;
    pt1 = pt2;

    return 0;
}

Int Int::operator++(int n) {
    Int result = *this;
    if (n != 0) {
        _i += n;
    }
    else {
        _i++;
        return result;
    }
}

Point_x& Point_x::operator=(const Point_x& otherPoint) {
    _x = otherPoint._x;
    _y = otherPoint._y;
    return *this;
}
