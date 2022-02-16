#include <queue>

union RecordType {
    char ch;
    int i;
    long l;
    float f;
    double d;
    int *int_ptr;
};


enum class WeatherDataType {
    Temperature, Wind
};

struct TempData {
    int StationId;
    time_t time;
    double current;
    double max;
    double min;
};

struct WindData {
    int StationId;
    time_t time;
    int speed;
    short direction;
};

struct Input {
    WeatherDataType type;
    union {
        TempData temp;
        WindData wind;
    };
};

// Functions that are specific to data types
void Process_Temp(TempData t);
void Process_Wind(WindData w);
void Initialize(std::queue<Input>& inputs);
