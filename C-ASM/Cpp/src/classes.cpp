#include "classes.h"

int main() {
    dog mongrel;
    breed labrador("yellow", "large");
    mongrel.setEars("pointy");
    labrador.setEars("long", "floppy");
    std::cout << "Cody is a "<< labrador.getColor() << " Labrador" <<std::endl;

    std::cout <<"======================================="<<std::endl;

    DerivedClass1 derived_class1;
    DerivedClass2 derived_class2;

    /* 
    derived_class1.PublicFunc();
    derived_class2.PublicFunc();    // function is inaccessible
    */

    VFuncDerived vfd;
    VFuncBase *pvfb = &vfd;
    VFuncDerived *pvdf = &vfd;
    int State;

    /*
    State = pvdf->GetState(); 
    State = pvdf->GetState();
    */

    return 0;
}
