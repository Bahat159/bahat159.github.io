#include <iostream>
#include <vector>
#include "test.h"


#define SIZE 10

double Account = 15.37;            // Hides class name Account

int main() {
    std::vector<int> v{1,2,3};

    for (int i = 0; i < v.size(); ++i){
        std::cout << v[i] <<"\n";
    }

    for(auto& num : v){
        std::cout << num <<"\n";
    }

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


