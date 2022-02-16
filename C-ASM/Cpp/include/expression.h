#include <iostream>

struct Alpha {
    virtual void test() {
        std::cout <<"In Alpha" <<"\n";
    }
};

struct Beta : Alpha {
    virtual void test() {
        std::cout << "In Beta" <<"\n";
    }
    void test2() {
        std::cout << "Test2 in Beta" <<"\n";
    }
};

struct Calm : Beta {
    virtual void test() {
        std::cout << "In C" <<"\n";
    }

    void test2(){
        std::cout<<"Test2 in Calm" <<"\n";
    }
};


void Globaltest(Alpha& a);

