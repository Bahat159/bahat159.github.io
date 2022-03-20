#include <iostream>

template <typename T> T minimum_t(const T& lhs, const T& rhs) {
    return lhs < rhs ? lhs : rhs;
}



int minimum(const int& lhs, const int& rhs) {
    return lhs < rhs ? lhs : rhs;
}
