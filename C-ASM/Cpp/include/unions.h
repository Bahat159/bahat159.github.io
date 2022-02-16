#include <queue>

/*
#include <crtdbg.h>
#include <new>
#include <utility>

// for sample objects and output
#include <string>
#include <vector>
#include <iostream>

*/


union RecordType {
    char ch;
    int i;
    long l;
    float f;
    double d;
    int *int_ptr;
};


enum class WeatherDataType {
    Temperature, Wind
};

struct TempData {
    int StationId;
    time_t time;
    double current;
    double max;
    double min;
};

struct WindData {
    int StationId;
    time_t time;
    int speed;
    short direction;
};

struct Input {
    WeatherDataType type;
    union {
        TempData temp;
        WindData wind;
    };
};

// Functions that are specific to data types
void Process_Temp(TempData t);
void Process_Wind(WindData w);
void Initialize(std::queue<Input>& inputs);


/* Unrestricted union (C++11) */
/*
struct A {
    A() = default;
    A(int i, const string& str) : num(i), name(str) {}

    int num;
    string name;
};

struct B {
    B() = default;
    B(int i, const string& str) : num(i), name(str) {}

    int num;
    string name;
    vector<int> vec;
};

enum class Kind { None, A, B, Integer};

#pragma warning(push)
#pragma warning(disable:4624)

class MyVariant {
    public:
        MyVariant() : kind_(Kind::None) {}
        MyVariant(Kind kind) : kind_(kind) {
            switch(kind){
                case Kind::None:
                    break;
                case Kind::A:
                    new (&a_) A();
                    break;
                case Kind::B:
                    new (&b_) B();
                    break;
                case Kind::Integer:
                    i_ = 0;
                    break;
                default:
                    _ASSERT(false);
                    break;
            }
        }
        ~MyVariant() {
            switch(kind_) {
                case Kind::None:
                    break;
                case Kind::A:
                    a_.~A();
                case Kind::B:
                    b_.~B();
                case Kind::Integer:
                    break;
                default:
                    _ASSERT(false);
                    break;
            }
            kind_ = Kind::None;
        }
        MyVariant(const MyVariant& other) : kind_(other.kind_) {
            switch(kind_) {
                case Kind::None:
                    break;
                case Kind::A:
                    new (&a_) A(other.a_);
                    break;
                case Kind::B:
                    new (&b_) B(other.b);
                    break;
                case Kind::Integer:
                    i_ = other.i_;
                    break;
                default:
                    _ASSERT(false);
                    break;
            }
        }
        MyVariant(MyVariant&& other) : kind_(other.kind_){
            switch (kind_){
                case Kind::None:
                    break;
                case Kind::A:
                    new (&a_) A(move(other.a_));
                    break;
                case Kind::B:
                    new (&b_) B(move(other.b_));
                    break;
                case Kind::Integer:
                    i_ = other.i_;
                    break;
                default:
                    _ASSERT(false);
                    break;
            }
            other.kind_ = Kind::None;
        }
        MyVariant& operator=(const MyVariant& other){
            if (&other != this){
                switch (other.kind_){
                    case Kind::None:
                        this->~MyVariant();
                        break;
                    case Kind::A:
                        *this = other.a_;
                        break;
                    case Kind::B:
                        *this = other.b_;
                        break;
                    case Kind::Integer:
                        *this = other.i_;
                        break;
                    default:
                        _ASSERT(false);
                        break;
                }
            }
            return *this;
        }

        MyVariant& operator=(MyVariant&& other){
            _ASSERT(this != &other);
            switch (other.kind_){
                case Kind::None:
                    this->~MyVariant();
                    break;
                case Kind::A:
                    *this = move(other.a_);
                    break;
                case Kind::B:
                    *this = move(other.b_);
                    break;
                case Kind::Integer:
                    *this = other.i_;
                    break;
                default:
                    _ASSERT(false);
                    break;
            }
            other.kind_ = Kind::None;
            return *this;
        }

        MyVariant(const A& a) : kind_(Kind::A), a_(a){}
        
        MyVariant(A&& a): kind_(Kind::A), a_(move(a)){}
        
        MyVariant& operator=(const A& a){
            if (kind_ != Kind::A){
                this->~MyVariant();
                new (this) MyVariant(a);
            }
            else{
                a_ = a;
            }
            return *this;
        }
        
        MyVariant& operator=(A&& a){
            if (kind_ != Kind::A){
                this->~MyVariant();
                new (this) MyVariant(move(a));
            }
            else{
                a_ = move(a);
            }
            return *this;
        }
        
        MyVariant(const B& b) : kind_(Kind::B), b_(b){}
        
        MyVariant(B&& b) : kind_(Kind::B), b_(move(b)){}
        
        MyVariant& operator=(const B& b){
            if (kind_ != Kind::B){
                this->~MyVariant();
                new (this) MyVariant(b);
            }
            else{
                b_ = b;
            }
            return *this;
        }
        
        MyVariant& operator=(B&& b){
            if (kind_ != Kind::B){
                this->~MyVariant();
                new (this) MyVariant(move(b));
            }
            else{
                b_ = move(b);
            }
            return *this;
        }
        
        MyVariant(int i) : kind_(Kind::Integer), i_(i){}
        
        MyVariant& operator=(int i){
            if (kind_ != Kind::Integer){
                this->~MyVariant();
                new (this) MyVariant(i);
            }
            else{
                i_ = i;
            }
            return *this;
        }
        
        Kind GetKind() const{
            return kind_;
        }
        
        A& GetA(){
            _ASSERT(kind_ == Kind::A);
            return a_;
        }
        
        const A& GetA() const{
            _ASSERT(kind_ == Kind::A);
            return a_;
        }
        
        B& GetB(){
            _ASSERT(kind_ == Kind::B);
            return b_;
        }
        
        const B& GetB() const{
            _ASSERT(kind_ == Kind::B);
            return b_;
        }
        
        int& GetInteger(){
            _ASSERT(kind_ == Kind::Integer);
            return i_;
        }
        
        const int& GetInteger() const{
            _ASSERT(kind_ == Kind::Integer);
            return i_;
        }
        
    private:
        Kind kind_;
        union{
            A a_;
            B b_;
            int i_;
        };
}

*/

// Initialize a union

union NumericType {
    short  iValue;
    long   LValue;
    double dValue;
};
