#include <iostream>
#include <type_traits>
#include <vector>
#include "test.h"
using namespace std;

#define SIZE 10

double Account = 15.37;            // Hides class name Account


int CMyClass::m_i = 0;
CMyClass myObject1;
CMyClass myObject2;

int main() {

    cout << boolalpha;
    cout << "A is trivial is: " << is_trivial<A>() << endl; // false
    cout << "A is standard-layout is: " << is_standard_layout<A>() << endl;  // false

    cout << "C is trivial is: " << is_trivial<C>() << endl; // true
    cout << "C is standard-layout is: " << is_standard_layout<C>() << endl;  // false

    cout << "D is trivial is: " << is_trivial<D>() << endl;  // false
    cout << "D is standard-layout is: " << is_standard_layout<D>() << endl; // true

    cout << "POD is trivial is: " << is_trivial<POD>() << endl; // true
    cout << "POD is standard-layout is: " << is_standard_layout<POD>() << endl; // true

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

    class Account Checking( Account ); // Qualifies Account as //  class name
    class Account *MY_Checking = new class Account( Account );
    std::cout << "Opening account with a balance of: "<< Checking.GetBalance() << "\n";
    std::cout << "Opening account with MY_Checking Pointer a balance of: "<< MY_Checking->GetBalance() << "\n";
    
    for(int i = 0; i < 5; i++){
        showStat(i);
    }

    /*
    cout << myObject1.m_i << endl;
    cout << myObject2.m_i << endl;

    myObject1.m_i = 1;
    cout << myObject1.m_i << endl;
    cout << myObject2.m_i << endl;

    myObject2.m_i = 2;
    cout << myObject1.m_i << endl;
    cout << myObject2.m_i << endl;

    CMyClass::m_i = 3;
    cout << myObject1.m_i << endl;
    cout << myObject2.m_i << endl;

    */

    C_ c1;
    C_ c2;
    c1.Test(100);
    c2.Test(100);
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
