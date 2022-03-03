#include <iostream>
#include <string>

class dog {
    public:
        dog() {
            _legs = 4;
            _bark = true;
        }
        void setDogSize(std::string dogSize) {
            _dogSize = dogSize;
        }
        virtual void setEars(std::string type) {
            _earType = type;
        }
    private:
        std::string _dogSize, _earType;
        int _legs;
        bool _bark;
};

class breed : public dog {
    public:
        breed(std::string color, std::string size) {
            _color = color;
            setDogSize(size);
        }
        std::string getColor() {
            return _color;
        }
        void setEars(std::string length, std::string type) {
            _earLength = length;
            _earType = type;
        }
    protected:
        std::string _color, _earLength, _earType;
};


class TestRun {
    public:
        TestRun() = default;
        TestRun(const TestRun&) = delete;
        TestRun(std::string name);
        void DoSomething();
        int Calculate(int a, double b);
        virtual ~TestRun();
        enum class State { Active, Suspended};
    protected:
        virtual void Initiailize();
        virtual void Suspend();
        State GetState();
    private:
        State _state{ State::Suspended};
        std::string _testName{ ""};
        int _index{ 0 };
        static int _instances;
};

int TestRun::_instances { 0 };


class CanInit {
    public:
        long num{17};   // OK in C++11
        int k = 9;      // OK in C++11

        CanInit() {}    // initializes num to 7 and k to 9
        CanInit(int val) : num(val) {}  // override original intiailized value of num.
};

class CanInit2 {
    public:
        CanInit2() {}

        long num{7};
        static int i;
        static int j;
};

int CanInit2::i = 15;
int CanInit2::j  = i;


class Point_s {
    public:
        Point_s(int, int);
        Point_s();
        int &x(int);
        int &y(int);
    private:
        int _x;
        int _y;
    protected:
        Point_s ToWindowCoords();
};

/* Member Access Control */

class BaseClass {
    public:
        int PublicFunc();
    protected:
        int ProtectedFunc();
    private:
        int PrivateFunc();
};

class DerivedClass1 : public BaseClass {
    void foo() {
        PublicFunc();
        ProtectedFunc();
        /* PrivateFunc(); */    // function is inaccessible
    }
};

class DerivedClass2 : private BaseClass {
    void foo() {
        PublicFunc();
        ProtectedFunc();
        /*PrivateFunc(); */     // function is inaccessible
    }
};


class Base {
    public:
        int Print();
        static int CountOf();
};

class Derived1 : private Base{};

class Derived2 : public Base {
    int ShowCount();
};


class VFuncBase {
    public:
        virtual int GetState() { return _state; }
    protected:
        int _state;
};

class VFuncDerived : public VFuncBase {
    private:
        int GetState() { return _state; }
};


/* Friend */

namespace NS{
    class M {
        friend class F;
    };
}

class F {};
namespace NS {
    class MS {
        friend F;
    };
}


template <typename T> class my_class {
    friend T;
};

class Foo {};
typedef Foo Fp4;

class G {
    friend Fp4;
    friend class Fst;
};


class Point {
    friend void ChangePrivate( Point &);
    public:
        Point (void) : m_i(0) {}
        void PrintPrivate(void) {std::cout << m_i << std::endl; }
    private:
        int m_i;
};

void ChangePrivate(Point &i) { i.m_i++; }


class B;

class A {
    public:
        int Func1(B& b);
    private:
        int Func2(B& b);
};

class B {
    private:
        int _b;
        friend int A::Func1(B&);
};

int A::Func1(B& b) { return b._b; }


class YourClass {
    friend class YourOtherClass;
    public:
        YourClass() {};
        void printMember() { std::cout << topSecret << std::endl; }
    private:
        int topSecret;
};

class YourOtherClass {
    public:
        void change(YourClass& yc, int x) { yc.topSecret = x; }
};


/* Private */
/*
class Base_class {
    public:
        int pubFunc() { return privMem; }
    private:
        void privMem;
};


class Derived_class : public Base_class {
    public:
        // C2248: privMem not accessible from derived class
        
        void usePrivate(int i) { privMem = i; }
        
};

class Derived_class2 : private Base_class {
    public:
        int usePublic() { return pubFunc(); }
};

*/


/* Protected */

class XX {
    public:
        void setProtMemb(int i) { m_protMemb = i; }
        void Display() { std::cout << m_protMemb << std::endl; }
    protected:
        int m_protMemb;
        void Protfunc() { std::cout << "\nAccess allowed\n"; }
}x;

class Y : public XX {
public:
   void useProtfunc() { Protfunc(); }
} y;
