#include <iostream>
#include <string>
#include "../include/pointers.h"


 
void func(int arr[], int length);

int main(int argc, char *argv[]) {
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

    Blanks *a5 = new(0xa5) Blanks;
    return a5 != 0;

    int *pI = new int[BIG_NUMBER];
    if( pI == 0x0 ) {
        std::cout << "Insufficient memory" << std::endl;
        return -1;
    }

    fLogMemory = 1;
    if(argc > 1) {
        for (int i = 0; i < atoi(argv[1]); ++i) {
            char *pMem = new char[10];
            delete[] pMem;
        }
        fLogMemory = 0;
        return cBlocksAllocated;
    }
    
}
