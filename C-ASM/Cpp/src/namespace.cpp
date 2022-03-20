#include <iostream>
#include <cstring>
#include "../include/namespace.h"

//using namespace std;

void test_label(int x) {
    if (x == 1){
        goto label1;
    }
    goto label2;

    label1:
        std::cout << "In Label1 "<<std::endl;
        return;
    label2:
        std::cout << "In Label2 "<<std::endl;
        return;
}

int main() {
    test_label(1);
    test_label(2);

    std::cout <<"============================" <<"\n";

    using namespace Test;
    using namespace std;

    string s = Func();
    std::cout << s << std::endl;

    return 0;
}


char *myStrCpy(char *Dest, const char *Source) {
    char *DestStart = Dest;

    while(*Dest++ = *Source++){
        ;
    }
    return DestStart;
}
