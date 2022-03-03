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
    Point sPoint;
    sPoint.PrintPrivate();
    ChangePrivate(sPoint);
    sPoint.PrintPrivate();

    std::cout <<"======================================="<<std::endl;

    YourClass yc1;
    YourOtherClass yoc1;
    yc1.printMember();
    yoc1.change( yc1, 5);
    yc1.printMember();

    std::cout <<"======================================="<<std::endl;

    x.setProtMemb( 0 );   // OK, uses public access function
    x.Display();
    y.setProtMemb( 5 );   // OK, uses public access function
    y.Display();
    y.useProtfunc();      // OK, uses public access function in derived class


    return 0;
}
