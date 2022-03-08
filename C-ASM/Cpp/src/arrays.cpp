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

int main(int argc, char *argv[]) {
    double MinCost;

    if(argv[1] == 0) {
        std::cout <<"You must specify the number of markets. "<<std::endl;
        exit(0);
    }
    MinCost = FindMinToMkt(*argv[1] - '0', TransportCosts, cFacts);
    std::cout <<"The minimum cost to Market: " << argv[1] << " is "<<MinCost <<std::endl;
}

double FindMinToMkt(int Mkt, double myTransportCosts[][cMkts], int mycFacts) {
    double MinCost = DBL_MAX;
    for(size_t i = 0; i < cFacts; ++i){
        MinCost = (MinCost < TransportCosts[i][Mkt]) ? MinCost : TransportCosts[i][Mkt];
    }
    return MinCost;
}
