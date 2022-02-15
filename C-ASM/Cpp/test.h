

char check_type();

#ifndef STRUCT_S
#define STRUCT_S
struct S {
    std::string name;
    float num;
    S(std::string s, float f) : name(s), num(f) {}
};

#endif

#ifndef ACCOUNT_CLASS
#define ACCOUNT_CLASS
// Declare class Account at global scope.
class Account{
    public:
        Account( double InitialBalance ){ balance = InitialBalance; }
        double GetBalance(){ return balance; }
    private:
        double balance;
};

#endif
