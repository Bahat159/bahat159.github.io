#include <limits>
#include <iostream>
#include <cfloat>


const int cMkts = 4, cFacts = 2;

// Declare a float that represents the transportation costs
double TransportCosts[][cMkts] = {
   { 32.19, 47.29, 31.99, 19.11 },
   { 11.29, 22.49, 33.47, 17.29 },
   { 41.97, 22.09,  9.76, 22.55 }
};

const int cFactories = sizeof(TransportCosts) / sizeof(double[cMkts]);

double FindMinToMkt(int Mkt, double myTransportCosts[][cMkts], int mycFacts);

struct Person {
    char* Name;
    short Age;
};


int main(int argc, char *argv[]) {
    double MinCost;

    if(argv[1] == 0) {
        std::cout <<"You must specify the number of markets. "<<std::endl;
        exit(0);
    }
    MinCost = FindMinToMkt(*argv[1] - '0', TransportCosts, cFacts);
    std::cout <<"The minimum cost to Market: " << argv[1] << " is "<<MinCost <<std::endl;

    std::cout<<"====================================="<<std::endl;

    Person mySelf;
    Person& rFriend = mySelf;

    mySelf.Name = "Busari Habibullaah";
    rFriend.Age   = 30;

    std::cout<<rFriend.Name <<" is "<<mySelf.Age <<" Years, as at 2022"<<std::endl;

    return 0;
}

double FindMinToMkt(int Mkt, double myTransportCosts[][cMkts], int mycFacts) {
    double MinCost = DBL_MAX;
    for(size_t i = 0; i < cFacts; ++i){
        MinCost = (MinCost < TransportCosts[i][Mkt]) ? MinCost : TransportCosts[i][Mkt];
    }
    return MinCost;
}



// initializing_arrays


class WindowColors {
    public:
        static const char *rgszWindowPartList[7];
};

const char *WindowColors::rgszWindowPartList[7] = {
    "Active Title Bar", "Inactive Title Bar", "Title Bar Text",
    "Menu Bar", "Menu Bar Text", "Window Background", "Frame"
};
