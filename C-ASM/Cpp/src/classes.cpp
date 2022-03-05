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

    std::cout <<"======================================="<<std::endl;

    time_t time_to_set;

    TempData td{ 45978, time(&time_to_set), 28.9, 37.0, 16.7 };
    TempData td_default{};
    TempData2 td2{ 16.7, 37.0, 28.9, 45978, time(&time_to_set)}; 

    class_a c1{};
    class_a c1_1;

    class_a c2{"ww"};
    class_a c2_1{"xx"};

    class_a c3{"yy", 4.4};
    class_a c3_1{"zz", 5.5};

    /* class_d d1{}; */
    class_d d1{4.5};
    class_d d2{4.5, "string"};
    class_d d3{4.5, "string", 'c'};

    class_f cf{"Hello"};

    std::cout <<"======================================="<<std::endl;

    Box b;
    Box b2{5};
    Box b3{5, 8, 12};
    Box b4(2, 4, 6);

    std::cout << "box.Volume: " << b.Volume() << std::endl; 
    std::cout << "box2.Volume: " << b2.Volume() << std::endl;
    std::cout << "box3.Volume: " << b3.Volume() << std::endl;
    std::cout << "box4.Volume: " << b4.Volume() << std::endl;

    std::cout <<"======================================="<<std::endl;

    DerivedContainer dc;
    std::cout <<"======================================="<<std::endl;
    
    const std::string aLabel = "aLabel";
    StorageBox sb(1, 2, 3, aLabel);
    std::cout <<"======================================="<<std::endl;

    Dervied_Class dcl;

    std::cout <<"======================================="<<std::endl;
    class_ctor m_ctor(5);
    class_ctor mi_ctor(5, 10);
    class_ctor min_ctor(5, 10, 15);
    std::cout <<"======================================="<<std::endl;
    MemoryBlock mbm(25);
    MemoryBlock mbmg(50);
    MemoryBlock mbmx(75);

    return 0;
}
