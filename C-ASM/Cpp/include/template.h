#include <iostream>

template <typename T> T minimum_t(const T& lhs, const T& rhs) {
    return lhs < rhs ? lhs : rhs;
}



int minimum(const int& lhs, const int& rhs) {
    return lhs < rhs ? lhs : rhs;
}

class MyClass {
    public:
        int num;
        std::wstring description;
};


template <typename T, size_t L> class MyArray {
    T arr[L];
    public:
        MyArray() {}
};

template <class T, int i> class MyStack {
    T* pStack;
    T StackBuffer[i];
    static const int cItems = i * sizeof(T);
    public:
        MyStack(void);
        void push(const T item);
        T& pop(void);
};

template <class T, int i> MyStack<T, i>::MyStack(void) {};
template <class T, int i> void MyStack<T, i>::push(const T item) {};
template <class T, int i> T& MyStack<T, i>::pop(void) {};


template <typename T> class X {
    public:
        template <typename U> void mf (const U &u);
};

template <typename T> template <typename U> void X<T>::mf (const U &u) {};

class My_X {
    template <class T> struct Y {
        T m_t;
        Y(T t) : m_t(t) {}
    };
    Y <int> yInt;
    Y <char> yChar;

    public:
        My_X (int i, char c) : yInt(i), yChar(c) {}
        void print() {
            std::cout <<yInt.m_t << " " <<yChar.m_t <<std::endl;
        }
};

template <class T> class X_x {
    template <class U> class Y {
        U* u;
        public:
            Y();
            U& Value();
            void print();
            ~Y();
    };
    Y<int> y;
    public:
        void print() { y.print(); }
};

template <class T>
template <class U> X_x<T>::Y<U>::Y() {
    std::cout<<"X<T>::Y<U>::Y()"<<std::endl;
    u = new U();
}

template <class T>
template <class U> U& X_x<T>::Y<U>::Value() {
    return *u;
}

template <class T>
template <class U> void X_x<T>::Y<U>::print() {
    std::cout<<this->Value() <<std::endl;
}

template <class T>
template <class U> X_x<T>::Y<U>::~Y() {
    std::cout<<"X<T>::Y<U>::~Y()" <<std::endl;
    delete u;
}
