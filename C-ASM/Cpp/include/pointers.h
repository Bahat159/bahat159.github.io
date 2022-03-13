#include <iostream>
#include <string>
#include <malloc.h>
#include <memory.h>


#define BIG_NUMBER 100000000

class MyClass {
    public:
        int num;
        std::string name;
        void print() {
            std::cout<<name<<" : "<<num <<std::endl;
        }
};

void func_A(MyClass* mc) {
    mc->num = 3;
}

void func_B(MyClass mc) {
    mc.num = 21;
    std::cout <<"Local copy of mc: ";
    mc.print();
}

void func(int *arr, int length) {
    size_t test = sizeof(arr);
    for(int i = 0; i < length; ++i) {
        std::cout<<arr[i] << " "<<std::endl;
    }
}

void Func(void* data, int length) {
    char* c = (char*)(data);
    for(int i=0; i < length; ++i) {
        *c = 0x41;
        ++c;
    }
}


std::string base {"Hello, World!"};

std::string append(std::string s) {
    return base.append(" ").append(s);
}

std::string prepend(std::string s) {
    return s.append(" ").append(base);
}
/*s
std::string combine(std::string s, std::string(*g)(string a)) {
    return (*g)(s);
}
*/


class Blanks {
    public:
        Blanks() {}
        void *operator new(size_t stAllocateBlock, char chInit);
};

void *Blanks::operator new(size_t stAllocateBlock, char chInit) {
    void *pvTemp = malloc(stAllocateBlock);
    if(pvTemp != 0) {
        memset(pvTemp, chInit, stAllocateBlock);
    }
    return pvTemp;
}


class My_other_Class {
    public:
        void * operator new[] (size_t) {
            return 0;
        }
        void operator delete[] (void *) {}
};


int fLogMemory = 0;
int cBlocksAllocated = 0;

void *operator new(size_t stAllocateBlock) {
    static int fInOpNew = 0;

    if(fLogMemory && !fInOpNew) {
        fInOpNew = 1;
        std::clog << "Memory block " <<++cBlocksAllocated <<" Allocated for " <<stAllocateBlock <<" bytes" <<std::endl;
        fInOpNew = 0;
    }
    return malloc(stAllocateBlock);
}

void operator delete(void *pvMem) {
    static int fInOpDelete = 0;
    if(fLogMemory && !fInOpDelete) {
        fInOpDelete = 1;
        std::clog<<"Memory block " <<cBlocksAllocated <<" Deallocated"<<std::endl;
        fInOpDelete = 0;
    }
    free(pvMem);
}
