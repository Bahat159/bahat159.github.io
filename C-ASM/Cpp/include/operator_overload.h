#include <iostream> 


struct Complex {
    Complex(double r, double i) : re(r), im(i) {}
    Complex operator+(Complex &other);
    void Display() { std::cout << re << ", " << im << std::endl; }
    private:
        double re, im;
};

Complex Complex::operator+(Complex &other) {
    return Complex(re + other.re, im + other.im);
}

class Point {
    public:
        Point& operator++();
        Point operator++(int);
        Point& operator--();
        Point operator--(int);
        Point() { _x = _y = 0; }
        int x() { return _x; }
        int y() { return _y; }
    private:
        int _x, _y;
};

Point& Point::operator++() {
    _x++;
    _y++;

    return *this;
}

Point& Point::operator--() {
    _x--;
    _y--;

    return *this;
}

Point Point::operator--(int) {
    Point temp = *this;
    --*this;
    return temp;
}
