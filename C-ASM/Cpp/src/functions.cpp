#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "functions.h"

using namespace std;

Simp ggg() {
    string t{"Hello"};
    int u{42};
    return {t, u};
}


int main(int argc, char *argv[]) {
    Simp s = ggg();
    std::cout << s.name << " " << s.num <<endl;

    std::cout <<"========================="<< "\n";
    auto t = f();
    cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;

    std::cout <<"========================="<< "\n";

    auto[x, y, z] = f(); // init from tuple
    cout <<"Init from tuple: " << x << " " << y << " " << z << endl;

    auto[a, b] = g(); // init from POD struct
    cout <<"Init from POD struct: "<< a << " " << b << endl;

    std::cout <<"==========FUCNTION OVERLOADING==============="<< "\n";

    const double d = 893094.2987;
    if (argc < 2){
        // These calls to print invoke print( char *s ).
        print("This program requires one argument");
        print("The argument specifies the number of");
        print("digits precision for the second number");
        print("printed.");
    }
    else {
        print("Gotcha!!!");
    }
    return 0;
}

tuple<int, string, double>f() {
    int i{108};
    string s{"Some Text"};
    double d{.01};
    return {i, s, d};
}

Subt g() {
    string t{"hello"};
    int u{42};
    return { t, u};
}

void Showvar(char *szTypes, ...){
    va_list vl;
    int i;

    va_start(vl, szTypes);

    for(i = 0; szTypes[i] != '\0'; ++i) {
        union Printable_t {
            int i;
            float f;
            char c;
            char *s;
        }Printable;

        switch(szTypes[i]) {
            case 'i':
                Printable.i = va_arg(vl, int);
                std::cout << Printable.i << "\n";
                break;
            case 'f':
                Printable.f = va_arg(vl, double);
                std::cout << Printable.f <<"\n";
                break;
            case 'c':
                Printable.c = va_arg(vl, int);
                std::cout << Printable.c <<"\n";
                break;
            case 's':
                Printable.s = va_arg(vl, char *);
                std::cout << Printable.s <<"\n";
                break;
            default:
                break;
        }
    }
    va_end(vl);
}


/* Function Overloading */
int print(string s) {
    std::cout<< s <<endl;
    return std::cout.good();
}

int print(double dvalue) {
    std::cout << dvalue << endl;
    return std::cout.good();
}

int print(double dvalue, int prec) {
    // Use table-lookup for rounding/truncation.
    static const double rgPow10[] = {10E-7, 10E-6, 10E-5, 10E-4, 10E-3, 10E-2, 10E-1, 10E0, 10E1,  10E2,  10E3,  10E4, 10E5,  10E6 };
    const int iPowZero = 6;

    // If precision out of range, just print the number.
    if (prec < -6 || prec > 7){
        return print(dvalue);
    }
    // Scale, truncate, then rescale.
    dvalue = floor(dvalue / rgPow10[iPowZero - prec]) * rgPow10[iPowZero - prec];
    std::cout << dvalue << endl;
    return std::cout.good();
}
