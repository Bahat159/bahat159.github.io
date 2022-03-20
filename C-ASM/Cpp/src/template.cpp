#include "../include/template.h"


int main() {

    int a = 5;
    int b = 10;
    int i = minimum_t<int>(a, b);
    std::cout<<"Minimum returned: "<<i<<std::endl;
    return 0;
}
