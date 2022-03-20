#include <iostream>
#include "../include/unions.h"

using namespace std;


int main() {

    RecordType t;
    t.i = 5;
    t.f = 7.25;

    std::cout <<"Union RecordType T holds Integer value: "<<t.i <<"\n";
    std::cout <<"Union RecordType T holds Floats value: "<<t.f <<"\n";

    queue<Input> inputs;
    Initialize(inputs);
    while(!inputs.empty()){
        Input const i = inputs.front();
        switch(i.type) {
            case WeatherDataType::Temperature:
                Process_Temp(i.temp);
                break;
            case WeatherDataType::Wind:
                Process_Wind(i.wind);
                break;
            default:
                break;
        }
        inputs.pop();
    }

    union NumericType Values = {10};
    std::cout <<"Union Integer Value: "<< Values.iValue << endl;

    Values.dValue = 3.1416;
    std::cout <<"Union Float Value: " <<Values.dValue <<endl;

    return 0;
}

void Process_Temp(TempData t) {}
void Process_Wind(WindData w) {}

void Initialize(std::queue<Input>& inputs) {
    Input first;
    first.type = WeatherDataType::Temperature;
    first.temp = { 101, 1418855664, 91.8, 108.5, 67.2};
    inputs.push(first);

    Input second;
    second.type = WeatherDataType::Wind;
    second.wind = { 204, 1418859354, 14, 27 };
    inputs.push(second);
}
