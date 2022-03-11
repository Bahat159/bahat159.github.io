#include <iostream>
#include <string>
#include "pointers.h"


 
void func(int arr[], int length);

int main() {
    MyClass* pmc = new MyClass{108, "Nick"};
    std::cout<<pmc <<std::endl;

    MyClass mc = *pmc;
    MyClass* pcopy = &mc;

    pmc->print();
    MyClass* pmc2 = pmc;

    pmc2->name = "Habibullaah";
    pmc->print();
    pmc2->print();

    func_A(pmc);
    pmc->print();
    pmc2->print();

    func_B(*pmc);
    pmc->print();

    delete(pmc);
    std::cout<<"=================================" <<std::endl;

    int i[5]{2,4,6,8,10};
    int j = sizeof(i) / sizeof(i[0]);
    func(i,j);

    std::cout<<"=================================" <<std::endl;

    
}

