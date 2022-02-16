#include <stdio.h>

#ifndef TEMP_STRUCT_B
#define TEMP_STRUCT_B

struct B_struct {
    virtual void f(int) {
        std::cout << "In B_struct::f(int)" << "\n";
    }

    virtual void f(char) {
        std::cout << "In B_struct::f(char)" << "\n";
    }

    void g(int){
        std::cout << "In B_struct::g"<< "\n";
    }

    void h(int);
};
#endif

struct Dest : B_struct {
    using B_struct::f;
    void f(int) {       // ok: D::f(int) overrides B::f(int)
        std::cout << "In Dest::f(int)" <<"\n";
    }

    using B_struct::g;
    void g(char) {       // ok: there is no B::g(char)
        std::cout << "In Dest::g(char)" << "\n";
    }

    using B_struct::h;
    void h(int) {}      // Note: D::h(int) hides non-virtual B::h(int)
};


void flo(Dest* pd);
