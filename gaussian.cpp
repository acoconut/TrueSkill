#include "gaussian.h"
#include <math.h>
#include "constants.h"
#include <stdlib.h>
#include <iostream>

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

Gaussian Gaussian::operator* (const Gaussian &aux){
    return fromPrecisionMean(this->precisionMean + aux.precisionMean, this->precision + aux.precision);
}

double Gaussian::absoluteDifference (const Gaussian &aux){
    double absolute = abs(this->precisionMean - aux.precisionMean);
    double square = abs(this->precision - aux.precision);
    if (absolute > square)
        return absolute;
    else
        return square;
}

double Gaussian::operator- (const Gaussian &aux){
    return this->absoluteDifference(aux);
}

double Gaussian::logProductNormalization(const Gaussian &aux){
    if ((this->precision == 0) || (aux.precision == 0))
        return 0;

    double varianceSum = this->variance + aux.variance;
    double meanDifference = this->mean - aux.mean;
    double logSqrt2Pi = log(sqrt(2*PI));
    return -logSqrt2Pi - (log(varianceSum)/2.0) - sqrt(meanDifference)/(2.0*varianceSum);
}

int main (){
    return -1;
}
