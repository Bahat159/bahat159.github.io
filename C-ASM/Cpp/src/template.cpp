#include "../include/template.h"


int main() {

    int a = 5;
    int b = 10;
    int i = minimum_t<int>(a, b);
    std::cout<<"Minimum returned: "<<i<<std::endl;

    MyClass mc1 { 1, L"Hello"};
    MyClass mc2 { 2, L"goodbye"};

    My_X x(1, 'a');
    x.print();
    
    X_x<int>* xi;
    X_x<char>* xc;
    xi->print();
    xc->print();
    delete xi;
    delete xc;

    return 0;
}
