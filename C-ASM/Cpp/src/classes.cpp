#include "classes.h"

int main() {
    dog mongrel;
    breed labrador("yellow", "large");
    mongrel.setEars("pointy");
    labrador.setEars("long", "floppy");
    std::cout << "Cody is a "<< labrador.getColor() << " Labrador" <<std::endl;

    return 0;
}
