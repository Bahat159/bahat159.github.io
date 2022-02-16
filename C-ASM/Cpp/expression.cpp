#include <iostream>

using namespace std;


void print(const char *string, const char *terminator = "\n");
//void printt();


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
}

void print(const char *string, const char *terminator) {
    if(string != NULL) {
        std::cout << string;
    }
    if(terminator != NULL) {
        std::cout << terminator;
    }
}

