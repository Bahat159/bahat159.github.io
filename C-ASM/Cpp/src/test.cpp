#include <iostream>
#include <type_traits>
#include <vector>
#include "../include/test.h"
#include "../include/temp.h"


using namespace std;

#define SIZE 10

double Account = 15.37;            // Hides class name Account


int CMyClass::m_i = 0;
CMyClass myObject1;
CMyClass myObject2;

// Pass by Value
constexpr float exp(float x, int n){
    return n == 0 ? 1 : n % 2 == 0 ? exp(x *x, n /2) : exp(x *x, (n-1) / 2) * x;
}

// Pass by Reference
constexpr float exp2(const float& x, const int& n){
    return n == 0 ? 1 : n % 2 == 0 ? exp2(x *x, n / 2) : exp2(x*x, (n-1) / 2) * x;
}

// Compile-time computation of array length

template<typename T, int N>
constexpr int length(const T(&)[N]){
    return N;
}

// Recursive constexpr function

constexpr int fac(int n){
    return n == 1 ? 1 : n * fac(n-1);
}


int main() {

    std::cout <<"=============CPLUSPLUS EXAMPLE APPLICATION=================" <<"\n";

    cout << boolalpha;
    cout << "A is trivial is: " << is_trivial<A>() << endl; // false
    cout << "A is standard-layout is: " << is_standard_layout<A>() << endl;  // false

    cout << "C is trivial is: " << is_trivial<C>() << endl; // true
    cout << "C is standard-layout is: " << is_standard_layout<C>() << endl;  // false

    cout << "D is trivial is: " << is_trivial<D>() << endl;  // false
    cout << "D is standard-layout is: " << is_standard_layout<D>() << endl; // true

    cout << "POD is trivial is: " << is_trivial<POD>() << endl; // true
    cout << "POD is standard-layout is: " << is_standard_layout<POD>() << endl; // true

    std::cout <<"==============================" <<"\n";
    /*
    std::vector<int> v{1,2,3};

    for (int i = 0; i < v.size(); ++i){
        std::cout << v[i] <<"\n";
    }

    for(auto& num : v){
        std::cout << num <<"\n";
    }

    */

    constexpr int size = 10;
    std::cout <<"ConstExpr Size :"<< size <<"\n";

    char type = check_type();

    if(type){
        std::cout <<"Test Data: "<< type << "\n";
    }
    else {
        std::cout <<"This function is not returning";
    }

    std::cout <<"==============================" <<"\n";

    class Account Checking( Account ); // Qualifies Account as //  class name
    class Account *MY_Checking = new class Account( Account );
    std::cout << "Opening account with a balance of: "<< Checking.GetBalance() << "\n";
    std::cout << "Opening account with MY_Checking Pointer a balance of: "<< MY_Checking->GetBalance() << "\n";

    std::cout <<"==============================" <<"\n";

    for(int i = 0; i < 5; i++){
        showStat(i);
    }

    C_ c1;
    C_ c2;
    c1.Test(100);
    c2.Test(100);

    std::cout <<"==============================" <<"\n";
    constexpr Foo foo(5);

    constexpr float x = exp(5, 3);
    constexpr float y { exp(2, 5) };
    constexpr int val = foo.GetValue();
    constexpr int f5 = fac(5);
    const int nums[] { 1, 2, 3, 4 };
    const int nums2[length(nums) * 2] { 1, 2, 3, 4, 5, 6, 7, 8 };

    // Run time:
    cout << "The value of foo is: " << foo.GetValue() << endl;
    cout << "The Fac of [fac(5)] is: "<< f5 << endl;
    cout << "The Length is: "<< nums2 << endl;

    std::cout <<"==============================" <<"\n";

    PointConsumer pc{};
    pc.set_point({});
    pc.set_point({ 3, 4 });
    pc.set_points({ { 3, 4 }, { 5, 6 } });

    Point p1{1, 2};
    pc.set_point(Point{5, 6});

    int i = 5;
    MyClass mc1(i);
    MyClass* mc2 = new class MyClass(i);  // class initializer
    mc1.set_int(i);
    int i2 = mc1.get_int();
    std::cout << "Get Integer Value :" << i2 <<"\n";
    std::cout <<"==============================" <<"\n";
    try{
        throw MyException();
    }
    catch (MyException ex) {
        std::cout << "Exception Occured: "<<ex.what() << "\n";
    }

    std::cout <<"==============================" <<"\n";

    MyAggregate agg1{ 1, 'c' };
    MyAggregate2 agg2{2};
    std::cout << "agg1: " << agg1.myChar << ": " << agg1.myInt << endl;
    std::cout << "agg2: " << agg2.myChar << ": " << agg2.myInt << endl;

    MyUnion mu1{ 'a' };  // my_int = 97, my_char = 'a', my_bool = true, {myInt = 97, myChar = '\0'}
    MyUnion mu2{ 1 };   // my_int = 1, my_char = 'x1', my_bool = true, {myInt = 1, myChar = '\0'}
    MyUnion mu3{};      // my_int = 0, my_char = '\0', my_bool = false, {myInt = 0, myChar = '\0'}
    MyUnion mu4 = mu3;  // my_int = 0, my_char = '\0', my_bool = false, {myInt = 0, myChar = '\0'}

    Mystruct ms1{ 'a' };            // myInt = 97, myChar = '\0'
    Mystruct ms2{ 1 };              // myInt = 1, myChar = '\0'
    Mystruct ms3{};                 // myInt = 0, myChar = '\0'
    Mystruct ms4{1, 'a'};           // myInt = 1, myChar = 'a'
    Mystruct ms5 = { 2, 'b' };      // myInt = 2, myChar = 'b'

    std::cout <<"==============================" <<"\n";
    DB myD;
    myD.f(1);
    myD.g('a');

    higher();

    std::cout <<"==============================" <<"\n";
    Dest* myd = new Dest();
    flo(myd);
}

char check_type(){
    auto \u30AD = 42;
    if(\u30AD == 42){
        return true;
    }
    else {
        return false;
    }
}


void Func(double& d){}

void ConstCast() {
    const double pi = 3.14;
    Func(const_cast<double&>(pi));
}

void showStat(int curr) {
    static int nStatic;
    nStatic += curr;
    std::cout << "nStatic is: "<< nStatic << endl;
}


void func() {
    std::cout << "In func"<<"\n";
}

void higher() {
    std::cout << "In higher" <<"\n";
    XP::func();
    XP::g();
}

void gest() {
    int i;
    void floki(char);
    using Bina::floki;
}


void flo(Dest* pd) {
    pd->f(1);
    pd->f('a');
    pd->g(1);
    pd->g('a');
}

