#include <iostream>


struct PERSON {
    int age;
    long ss;
    float weight;
    char name[25];
}family_member;

struct CELL {
    unsigned short character    : 8;
    unsigned short foreground   : 3;
    unsigned short intensity    : 1;
    unsigned short background   : 3;
    unsigned short blink        : 1;
}screen[25][80];

