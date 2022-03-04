#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>


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
        void Protfunc() { std::cout << "Access allowed\n"; }
}x;

class Y : public XX {
public:
   void useProtfunc() { Protfunc(); }
} y;

// Without Constructor
struct TempData {
    int StationId;
    time_t timeSet;
    double current;
    double maxTemp;
    double minTemp;
};

// With Constructor  
struct TempData2 {
    TempData2(double minimum, double maximum, double cur, int id, time_t t) : stationId{id}, timeSet{t}, current{cur}, maxTemp{maximum}, minTemp{minimum} {}
    int stationId;
    time_t timeSet;
    double current;
    double maxTemp;
    double minTemp;
};

class class_a {
    public:
        class_a() {}
        class_a(std::string str) : m_string {str} {}
        class_a(std::string str, double dbl) : m_string{str}, m_double {dbl} {}
    double m_double;
    std::string m_string;
};

class class_d {
    public:
        float m_float;
        std::string m_string;
        wchar_t m_char;
};


class class_f {
    public:
        class_f() = delete;
        class_f(std::string x) : m_string { x} {}
        std::string m_string;
};

/* Constructor */
class Box {
    public:
        // Default constructor
        Box() {}
        // Initialize a Box with equal dimensions (i.e. a cube)
        explicit Box(int i) : m_width(i), m_length(i), m_height(i) {}
        // Initialize a Box with custom dimensions
        Box (int width, int length, int height) : m_width(width), m_length(length), m_height(height) {}
        int Volume() { return m_width * m_length * m_height; }
    private:
        /* 
            Will have value of 0 when default constructor is called.
            If we didn't zero-init here, default constructor would
            leave them uninitialized with garbage values.
        */
        int m_width{0};
        int m_length{0};
        int m_height{0};
};

/*
class BoxWithMove {
    public:
        BoxWithMove() { std::cout << "Default " <<std::endl; }
        BoxWithMove(int width, int height, int length) : m_width(width), m_height(height), m_length(length) {
            std::cout <<"int, int, int" <<std::endl;
        }
        BoxWithMove(BoxWithMove& other) : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length) {
            std::cout<< "Copy " << std::endl;
        }
        BoxWithMove(BoxWithMove&& other) : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length){
            m_contents = std::move(other.m_contents);
            std::cout <<"Move " <<std::endl;
        }
        int Volume() { return m_width * m_height * m_length; }
        void Add_Item(std::string item) { m_contents.push_back(item); }
        void Print_contents() {
            for (const auto& item : m_contents) {
                std::cout << item << " ";
            }
        }
    private:
        int m_width{0};
        int m_height{0};
        int m_length{0};
        vector<std::string>m_contents;
};

*/

/* Order of Constructor */

class Contained1 {
    public:
        Contained1() { std::cout <<"Contained1 ctor"<<std::endl; }
};

class Contained2 {
    public:
        Contained2() { std::cout <<"Contained2 ctor"<<std::endl; }
};

class Contained3 {
    public:
        Contained3() { std::cout<<"Contained3 ctor"<<std::endl; }
};

class BaseContainer {
    public:
        BaseContainer() { std::cout<<"BaseContainer ctor"<<std::endl; }
    private:
        Contained1 c1;
        Contained2 c2;
};

class DerivedContainer : public BaseContainer { 
    public:
        DerivedContainer() : BaseContainer() { std::cout <<"DerivedContainer ctor" <<std::endl; }
    private:
        Contained3 c3;
};
