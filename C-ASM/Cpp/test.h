#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

using namespace std;

char check_type();

#ifndef STRUCT_S
#define STRUCT_S
struct S {
    std::string name;
    float num;
    S(std::string s, float f) : name(s), num(f) {}
};

#endif

#ifndef ACCOUNT_CLASS
#define ACCOUNT_CLASS
// Declare class Account at global scope.
class Account{
    public:
        Account( double InitialBalance ){ balance = InitialBalance; }
        double GetBalance(){ return balance; }
    private:
        double balance;
};

#endif

struct x_ {
    char a;
    int b;
    short c;
    char d;
}bar[3];



// Trivial Type
#ifndef TRIVIAL_STRUCT
#define TRIVIAL_STRUCT

struct Trivial {
    int i;
    private:
    int j;
};

struct Trivial2 {
    int i;
    Trivial2(int a, int b) : i(a), j(b) {}
    Trivial2() = default;
    private:
    int j;      // Different access control
};

#endif

// Standard Layout Type
#ifndef SL_T
#define SL_T

struct SL {
    int i;
    int j;
    SL(int a, int b) : i(a), j(b) {}  // User-defined constructor OK
};

struct Base {
    int i;
    int j;
    void Foo() {}
};

struct Derived : public Base {
    int x;
    int y;
};

#endif

// POD Type

#ifndef PO_D
#define PO_D

struct B {
    protected:
        virtual void Foo() {}
};

// Neither trivial nor standard layout

struct A : B {
    int a;
    int b;
    void Foo() override {}  // virutal function
};

// Trivial but not standard - layout

struct C {
    int a;
    private:
    int b;    // Different access control
};

struct D {
    int a;
    int b;
    D () {}  // User-defined constructor
};

struct POD {
    int a;
    int b;
};

#endif

enum suits { Spades = 1, Clubs, Hearts,Diamonds };

void Func(double& d);
void ConstCast();
void showStat(int curr);


class CMyClass{
    public:
        static int m_i;
};

#ifndef STRUCT_C
#define STRCUT_C

struct C_ {
    void Test(int value) {
        static int var = 0;
        if(var == value) {
            std::cout << "var == value" << endl;
        }
        else {
            std::cout << "var != value" << endl;
        }
        var = value;
    }
};

#endif


thread_local float f = 42.0;

#ifndef STRUC_S
#define STRCU_S

struct S_L {
    thread_local static int i;
    thread_local static char buf[10];
};

#endif

class Date {
    public:
        Date (int mn, int dy, int yr);
        int getMonth() const;
        void setMonth(int mn);
    private:
        int month;
};


class Foo {
    public:
        constexpr explicit Foo(int i) : _i(i) {}
        constexpr int GetValue() const {
            return _i;
        }
    private:
    int _i;
};
