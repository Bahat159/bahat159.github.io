#include <type_traits>
#include <string>
#include <tuple>
#include <stdarg.h>

int sum(int a, int b);
int foo(int i, std::string s);
constexpr float exp(float x, int n);

#if ECS == gnu
#include <cstring>
#define ECString string
using namespace std;
#else
#include <bstring.h>
#define ECString string
#endif

#pragma GCC system_header

/*
//Declare printf with C linkage.
extern "C" int printf( const char *fmt, ... );

inline double Account::GetBalance();

template <typename T> T copy_object(T& obj) noexcept(std::is_pod<T>);
template<typename Lhs, typename Rhs> auto Add2(const Lhs& lhs, const Rhs& rhs);

// Default Arguments 
int DoSomething(int num,string str,Allocator& alloc = defaultAllocator);
int DoSomethingElse(int num, string str = string{ "Working" }, Allocator& alloc = defaultAllocator);

//Trailing return types 

template<typename Lhs, typename Rhs> auto Add(const Lhs& lhs, const Rhs& rhs) -> decltype(lhs + rhs);
//Type deduction in return types (C++14) 
template<typename F, typename Tuple = tuple<T...>, int... I> decltype(auto) apply_(F&& f, Tuple&& args, index_sequence<I...>);
template<typename F, typename Tuple = tuple<T...>,typename Indices = make_index_sequence<tuple_size<Tuple>::value >>decltype( auto) \
 apply(F&& f, Tuple&& args);

*/
struct Simp {
    string name;
    int num;
};

Simp ggg();


tuple<int, string, double>f();

struct Subt {
    string name;
    int  num;
};

Subt g();

void ShowVar( char *szTypes, ... );


// Function overloading
// Prototype three print functions.
int print(std::string s);             // Print a string.
int print(double dvalue);            // Print a double.
int print(double dvalue, int prec);  // Print a double with a given precision.


class Over {
    public:
        Over() { std::cout << "Over default constructor\n";}
        Over(Over &co) { std::cout << "Over&\n"; }
        Over(const Over &co) { std::cout << "Const Over&\n"; }
        Over(volatile Over &vo) { std::cout << "Volatile Over&\n"; }
};


class UDC {
    public:
        operator int() {
            return 0;
        }
        operator long();
};

void Printish(int i);


class Csm {
    public:
        Csm() {}
        vector<unsigned> get_data() & {
            std::cout <<"Lvalue from class Csm()" <<"\n";
            return _data;
        }
        vector<unsigned> get_data() && {
            std::cout <<"Rvalue from class Csm()"<<"\n";
            return std::move(_data);
        }
        vector<unsigned> print_outro() {
            std::cout <<"Fucntion overloading with example" <<"\n";
            return _data;
        }
    private:
        vector<unsigned> _data;
};

class Account {
    public:
        Account() {}
        double Deposit(double dAmount, char *szPassword);
    private:
        double Deposit(double dAmount){
            return 0.0;
        }
        int Validate(char *szPassword){
            return 0;
        }
};
