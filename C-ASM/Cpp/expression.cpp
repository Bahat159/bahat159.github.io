#include <iostream>
#include "expression.h"

using namespace std;


void print(const char *string, const char *terminator = "\n");


void printt() {
    std::cout << endl;
}

template <typename T> void printt(const T& t) {
    std::cout << t << endl;
}

template <typename First, typename... Rest> void printt(const First& first, const Rest&... rest) {
    std::cout << first <<", ";
    printt(rest...);
}


int main() {
    print("hello, ");
    print("world!");

    print("good morning", ", ");
    print("sunshine.");

    std::cout<<"======================================"<<"\n";

    printt();
    printt(1);

    printt(10, 20);
    printt(100, 200, 300);
    printt("first", 2, "third", 3.14159);

    std::cout<<"======================================"<<"\n";

    Alpha *pa = new Calm;
    Alpha *pa2 = new Beta;

    pa->test();

    Beta * pb = dynamic_cast<Beta *>(pa);
    if(pb) {
        pb->test2();
    }
    Calm * pc = dynamic_cast<Calm *>(pa2);
    if(pc) {
        pc->test2();
    }
    Calm ConStack;
    Globaltest(ConStack);

    Beta BonStack;
    Globaltest(BonStack);
}

void print(const char *string, const char *terminator) {
    if(string != NULL) {
        std::cout << string;
    }
    if(terminator != NULL) {
        std::cout << terminator;
    }
}

void Globaltest(Alpha& a) {
    try{
        Calm &c = dynamic_cast<Calm&> (a);
        std::cout << "In GlobalTest"<< "\n";
    }
    catch(std::bad_cast) {
        std::cout <<"Cant cast to Calm" <<"\n";
    }
}
