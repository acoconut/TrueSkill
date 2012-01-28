#include <math.h>
#include "constants.h"
#include <iostream>
class Gaussian{
    private:
        double mean;
        double standardDeviation;
        double variance;
        double precision;
        double precisionMean;
    public:
        Gaussian(double, double);
        ~Gaussian();
        double normalizationConstant(double);
        Gaussian fromPrecisionMean(double, double);
        Gaussian operator * (Gaussian);
};

Gaussian::Gaussian(double mean, double standardDeviation){
    this->mean = mean;
    this->standardDeviation = standardDeviation;
    this->variance = sqrt(standardDeviation);
    this->precision = 1.0/variance;
    this->precisionMean = precision*mean;
} 

Gaussian::~Gaussian(){
    //TODO
}

double Gaussian::normalizationConstant(double standardDeviation){
    return 1.0/(sqrt(2*PI)*standardDeviation);
} 

/** Creates a Gaussian distribution from the precision mean value **/
Gaussian Gaussian::fromPrecisionMean(double precisionMean, double precision){
    double mean = precisionMean / precision;
    double variance = 1.0/precision;
    double standardDeviation = sqrt(variance);
    Gaussian gaussian(mean, standardDeviation);
    return gaussian;
}

Gaussian Gaussian::operator* (Gaussian aux){
    return fromPrecisionMean(this->precisionMean + aux.precisionMean, this->precision + aux.precision);
}

int main (){
    return -1;
}
