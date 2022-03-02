#include <iostream>
#include <string>

class dog {
    public:
        dog() {
            _legs = 4;
            _bark = true;
        }
        void setDogSize(std::string dogSize) {
            _dogSize = dogSize;
        }
        virtual void setEars(std::string type) {
            _earType = type;
        }
    private:
        std::string _dogSize, _earType;
        int _legs;
        bool _bark;
};

class breed : public dog {
    public:
        breed(std::string color, std::string size) {
            _color = color;
            setDogSize(size);
        }
        std::string getColor() {
            return _color;
        }
        void setEars(std::string length, std::string type) {
            _earLength = length;
            _earType = type;
        }
    protected:
        std::string _color, _earLength, _earType;
};


class TestRun {
    public:
        TestRun() = default;
        TestRun(const TestRun&) = delete;
        TestRun(std::string name);
        void DoSomething();
        int Calculate(int a, double b);
        virtual ~TestRun();
        enum class State { Active, Suspended};
    protected:
        virtual void Initiailize();
        virtual void Suspend();
        State GetState();
    private:
        State _state{ State::Suspended};
        std::string _testName{ ""};
        int _index{ 0 };
        static int _instances;
};

int TestRun::_instances { 0 };
