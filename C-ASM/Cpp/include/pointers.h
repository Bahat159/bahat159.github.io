#include <iostream>
#include <string>

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
