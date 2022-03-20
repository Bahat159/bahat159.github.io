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
