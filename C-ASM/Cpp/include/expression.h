#include <iostream>
#include <typeinfo>
#include <iostream>


/* Dynamic cast */

struct Alpha {
    virtual void test() {
        std::cout <<"In Alpha" <<"\n";
    }
};

struct Beta : Alpha {
    virtual void test() {
        std::cout << "In Beta" <<"\n";
    }
    void test2() {
        std::cout << "Test2 in Beta" <<"\n";
    }
};

struct Calm : Beta {
    virtual void test() {
        std::cout << "In Calm" <<"\n";
    }

    void test2(){
        std::cout<<"Test2 in Calm" <<"\n";
    }
};


void Globaltest(Alpha& a);


class Shape {
    public:
        virtual void virtualfunc () const {}
};

class Circle : public Shape {
    public:
        virtual void virtualfunc() const {}
};


/* Const_cast */

class CCTest {
    public:
        void setNumber(int);
        void printNumber() const;
    private:
        int number;
};
