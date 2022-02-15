

char check_type();

struct S {
    std::string name;
    float num;
    S(std::string s, float f) : name(s), num(f) {}
};

// Declare class Account at global scope.
class Account{
    public:
        Account( double InitialBalance ){ balance = InitialBalance; }
        double GetBalance(){ return balance; }
    private:
        double balance;
};
