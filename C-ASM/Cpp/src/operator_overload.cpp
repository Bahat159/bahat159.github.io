#include <iostream>
#include "operator_overload.h"

int main() {
    Complex a = Complex(1.2, 3.4);
    Complex b = Complex(5.6, 7.8);
    Complex c = Complex(0.0, 0.0);

    c = a + b;
    c.Display();

    return 0;
}
