#include <iostream>
#include <vector>



#define SIZE 10

int main() {
    std::vector<int> v{1,2,3};

    for (int i = 0; i < v.size(); ++i){
        std::cout << v[i] <<"\n";
    }

    for(auto& num : v){
        std::cout << num <<"\n";
    }

    constexpr int size = 10;
    std::cout <<"ConstExpr Size :"<< size <<"\n";
}
