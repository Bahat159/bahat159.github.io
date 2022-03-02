#include <iostream>
#include <string>

class dog {
    public:
        dog() {
            _legs = 4;
            _bark = true;
        }
        void setDogSize(string dogSize) {
            _dogSize = dogSize;
        }
        virtual void setEars(string type) {
            _earType = type;
        }
    private:
        string _dogSize, _earType;
        int _legs;
        bool _bark;
};

class breed : public dog {
    public:
        breed(string color, string size) {
            _color = color;
            setDogSize(size);
        }
        string getColor() {
            return _color;
        }
        void setEars(string length, string type) {
            _earLength = length;
            _earType = type;
        }
    protected:
        string _color, _earLength, _earType;
};
