#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>


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

class Box_x {
    public:
        Box_x(int width, int length, int height){
            m_width = width;
            m_length = length;
            m_height = height;
        }
    private:
        int m_width;
        int m_length;
        int m_height;
};

class StorageBox : public Box_x {
    public:
        StorageBox(int width, int length, int height, const std::string label) : Box_x(width, length, height) {
            m_label = label;
            std::cout<<m_label <<std::endl;
        }
    private:
        std::string m_label;
};

class BaseClass1 {
    public:
        BaseClass1() { std::cout << "BaseClass1 ctor" <<std::endl; }
};

class BaseClass2 {
    public:
        BaseClass2() { std::cout <<"BaseClass2 ctor "<<std::endl; }
};

class BaseClass3 {
    public:
        BaseClass3() { std::cout <<"BaseClass3 ctor"<< std::endl; }
};

class Dervied_Class : public BaseClass1, public BaseClass2, public BaseClass3 {
    public:
        Dervied_Class() {std::cout <<"Dervied_Class ctor" <<std::endl; }
};


class MemoryBlock {
    public:
        explicit MemoryBlock(size_t length) : _length(length), _data(new int[length]) {
            std::cout <<"In MemoryBlock(size_t). length = "<<_length<<"."<<std::endl;
        }
        ~MemoryBlock() {
            std::cout<<"In ~MemoryBlock(). length = "<<_length<<"."<<std::endl;
            if(_data != nullptr) {
                std::cout<<"Deleting resource.";
                delete[] _data;
            }
            std::cout<< std::endl;
        }
        MemoryBlock(const MemoryBlock& other) : _length(other._length), _data(new int[other._length]) {
            std::cout<<"In MempryBlock(const MemoryBlock&).length = "<<other._length<<". Copying resources."<<std::endl;
            std::copy(other._data, other._data+_length,_data);
        }
        MemoryBlock& operator=(const MemoryBlock& other) {
            std::cout<<"In operator=(const MemoryBlock& other).length = "<<other._length<<". Copying resource."<<std::endl;
            if(this != &other){
                delete[] _data;

                _length = other._length;
                _data = new int[_length];
                std::copy(other._data, other._data+_length, _data);
                std::cout<<std::endl;
            }
            return *this;
        }
        size_t Length() const {
            return _length;
        }
    private:
        size_t _length;
        int* _data;
};

class class_ctor {
    public:
        int max;
        int min;
        int middle;

        class_ctor() {}
        class_ctor(int my_max) {
            max = my_max > 0 ? my_max : 10; 
            std::cout << "My Max in class_ctor(int max) = " <<max <<std::endl;
        }
        class_ctor(int my_max, int my_min) {
            max = my_max > 0 ? my_max : 10;
            min = my_min > 0 && my_min < max ? my_min : 1;
            std::cout << "My Max in class_ctor(int my_max, int my_min) = " <<max <<std::endl;
            std::cout << "My Min in class_ctor(int my_max, int my_min) = " <<min <<std::endl;
        }
        class_ctor(int my_max, int my_min, int my_middle) {
            max = my_max > 0 ? my_max : 10;
            min = my_min > 0 && my_min < max ? my_min : 1;
            middle = my_middle < max && my_middle > min ? my_middle : 5;
            std::cout << "My Max in class_ctor(int my_max, int my_min, int my_middle) = " <<max <<std::endl;
            std::cout << "My Min in class_ctor(int my_max, int my_min, int my_middle) = " <<min <<std::endl;
            std::cout << "My Middle in class_ctor(int my_max, int my_min, int my_middle) = " <<middle <<std::endl;
        }
};

class class_a_ctor {
    public:
        class_a_ctor() {}
        class_a_ctor(std::string str) : m_string {str} {}
        class_a_ctor(std::string str, double dbl) : class_a_ctor(str) { m_double = dbl; }
        double m_double{1.0};
        std::string m_string {m_double < 10.0 ? "alpha" : "beta"};
};

/* Destructor */

class String {
    public:
        String(char *ch);
        ~String();
    private:
        char *_text;
        size_t sizeOfText;
};
/*
String::String(char *ch) {
    sizeOfText = strlen(ch) + 1;

    _text = new char[sizeOfText];

    if(_text) {
        strcpy_s(_text, sizeOfText, ch);
    }
}

String::~String() {
    delete[] _text;
}

*/

class Account_t {
    public:
        double Deposit(double HowMuch) {
            balance += HowMuch;
            return balance;
        }
    private:
        double balance;
};

class Account {
    public:
        Account(double d) { _balance = d; }
        virtual ~Account() {}
        virtual double GetBalance() { return _balance; }
        virtual void PrintBalance() { std::cerr<<"Error. Balance not available for the base type."<<std::endl;}
    private:
        double _balance;
};

class CheckingAccount : public Account {
    public:
        CheckingAccount(double d) : Account(d) {}
        void PrintBalance() { std::cout <<"Checking account balance: "<< GetBalance() << std::endl; } 
};

class SavingsAccount : public Account {
    public:
        SavingsAccount(double d) : Account(d) {}
        void PrintBalance() { std::cout <<"Savings account balance: " <<GetBalance() <<std::endl; }
};


/* Virtual Fucntion */

class BaseAgain {
    public:
        virtual void NameOf();
        void InvokingClass();
};


void BaseAgain::NameOf() {
    std::cout<< "BaseAgain::NameOf"<< std::endl;
}

void BaseAgain::InvokingClass() {
    std::cout <<"Invoked by BaseAgain" <<std::endl;
}

class DerivedAgain : public BaseAgain {
    public:
        void NameOf();
        void InvokingClass();
};

void DerivedAgain::NameOf() {
    std::cout<<"DerivedAgain::NameOf()" <<std::endl;
}

void DerivedAgain::InvokingClass() {
    std::cout<<"Invoked by DerivedAgain" <<std::endl;
}

/* Single Inhertiance */

class Document {
    public:
        char *Name;
        void PrintNameOf();
};

void Document::PrintNameOf() {
    std::cout <<Name <<std::endl;
}

class Book : public Document {
    public:
        Book(char *name, long pagecount);
    private:
        long pageCount;
};

Book::Book(char *name, long pagecount) {
    Name = new char[strlen(name) + 1];
    strcpy(Name, Name);
    pageCount = pagecount;
};


/* Multiple Base class */

class Queue {};
class CashierQueue : virtual public Queue {};
class LunchQueue : virtual public Queue {};
class LunchCashierQueue : public LunchQueue, public CashierQueue {};


class Alpha {
    public:
        unsigned a;
        unsigned b();
};

class Beta {
    public:
        unsigned a();
        int b();
        char c;
};

class Cida : public Alpha, public Beta{};


/* Explicit Override */

extern "C" int printf_s(const char *, ...);
/*
__interface IMyInt1 {
    void mf1();
    void mf1(int);
    void mf2();
    void mf2(int);
};

__interface IMyInt2 {
    public:
        void mf1();
        void mf1(int);
        void mf2();
        void mf2(int);
};

class CMyClass : public IMyInt1, public IMyInt2 {
    public:
        void IMyInt1::mf1() {
            printf_s("In CMyClass::IMyInt1::mf1()\n");
        }
};



struct B1 {
    void mf1() {}
};

struct B2 {
    void mf(short) {}
    void mf(char) {}
};

struct D : B1, B2 {
    void mf(short) {
        __super::mf(1);
        __super::mf('s');
    }
};

*/

class BufferedOutput {
    public:
        short ByteWritten() {
            return bytecount;
        }
        static void ResetCount() {
            bytecount = 0;
        }

        static long bytecount;
};

long BufferedOutput::bytecount;


class Money {
    public:
        Money() : amount{0.0} {};
        Money(double _amount) : amount { _amount } {};
        double amount;
};

void display_balance(const Money balance);


/* Mutable Data Members (C++) */

class X_m {
    public:
        bool GetFlag() const {
            m_accessCount++;
            return m_flag;
        }
        private:
            bool m_flag;
            mutable int m_accessCount;
};


class BufferedIO {
    public:
        enum IOError { None, Access, General };

        class BufferedInput {
            public:
                int read();
                int good();
            private:
                IOError _inputerror;
        };
        class BufferedOutput {};
};

int BufferedIO::BufferedInput::good() {
    return _inputerror == None;
}


class C_typedDef {
    public:
        typedef class U u_t;
        typedef class V {} v_t;
};
