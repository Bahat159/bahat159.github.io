#include <iostream>
#include <vector>

void test_label(int x);
char *myStrCpy(char *Dest, const char *Source);


namespace ContosoData {
    class ObjectManager {
        public:
            void DoSomething() {}
    };
    void Func(ObjectManager) {}
}

/*
Use the fully qualified name:
-------------------------------
ContosoData::ObjectManager mgr;
mgr.DoSomething();
ContosoData::Func(mgr);

Use a using declaration to bring one identifier into scope:
--------------------------------------------
using ContosoData::ObjectManager;
ObjectManager mgr;
mgr.DoSomething();

Use a using directive to bring everything in the namespace into scope:
-----------------------------------------------------
using namespace ContosoData;

ObjectManager mgr;
mgr.DoSomething();
Func(mgr);

*/


#pragma once
namespace ContosoDataServer {
    void Foo();
    int Bar();
}

namespace Test {
    namespace old_ns {
        std::string Func() { return std::string("Hello from old"); }
    }
    inline namespace new_ns {
        std::string Func() { return std::string("Hello from new"); }
    }
}


namespace Parent {
    inline namespace new_ns {
        template <typename T>
        struct C {
            T member;
        };
    }
    template<> class C<int> {};
}


namespace Contoso {
    namespace v_10 {
        template <typename T>
        class Funcs {
            public:
                Funcs(void);
                T Add(T a, T b);
                T Subtract(T a, T b);
                T Mulitply(T a, T b);
                T Divide(T a, T b);
        };
    }
    inline namespace v_20 {
        template <typename T>
        class Funcs {
            public:
                Funcs(void);
                T Add(T a, T b);
                T Subtract(T a, T b);
                T Multiply(T a, T b);
                std::vector<double> Log(double);
                T Accumulate(std::vector<T> nums);
        };
    }
}
