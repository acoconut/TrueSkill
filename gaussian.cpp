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

double Gaussian::logProductNormalization (const Gaussian &aux){
    if ((this->precision == 0) || (aux.precision == 0))
        return 0;

    double varianceSum = this->variance + aux.variance;
    double meanDifference = this->mean - aux.mean;

    double logSqrt2Pi = log(sqrt(2*PI));

    return -logSqrt2Pi - (log(varianceSum)/2.0) - sqrt(meanDifference)/(2.0*varianceSum);
}

Gaussian Gaussian::operator/ (const Gaussian &aux){
    return fromPrecisionMean(this->precisionMean - aux.precisionMean, this->precision - aux.precision);
}

double Gaussian::logRatioNormalization (const Gaussian &aux){
    if ((this->precision == 0) || (aux.precision == 0))
        return 0;

    double varianceDifference = this->variance - aux.variance;
    double meanDifference = this->mean - aux.mean;

    double logSqrt2Pi = log(sqrt(2*PI));

    return log(this->variance) + logSqrt2Pi - log(varianceDifference)/2.0 + (meanDifference*meanDifference) / (2*varianceDifference);
}

double Gaussian::at (double x){
    return at(x, 0, 1);
}

double Gaussian::at (double x, double mean, double standardDeviation){
    double multiplier = 1.0/(standardDeviation * sqrt(2*PI));
    double expPart = exp((-1.0*pow(x - mean, 2.0))/(2*(standardDeviation*standardDeviation)));
    return multiplier*expPart;
}

double Gaussian::cumulativeTo (double x){
    return cumulativeTo (x, 0, 1);
}

double Gaussian::cumulativeTo (double x, double mean, double standardDeviation){
    const double invsqrt2 = 1/sqrt(2);
    double result = errorFunctionCumulativeTo(invsqrt2*x);
    return 0.5*result;
}

double Gaussian::errorFunctionCumulativeTo (double x){
    //Numerical Recipes 265 3rd edition
    double z = abs(x);

    double t = 2.0/(2.0 + z);
    double ty = 4*t - 2;

    double coefficients [] = {-1.3026537197817094, 6.4196979235649026e-1,
                             1.9476473204185836e-2, -9.561514786808631e-3, 
                             -9.46595344482036e-4, 3.66839497852761e-4,
                             4.2523324806907e-5, -2.0278578112534e-5,
                             -1.624290004647e-6, 1.303655835580e-6, 
                             1.5626441722e-8, -8.5238095915e-8,
                             6.529054439e-9, 5.059343495e-9,
                             -9.91364156e-10, -2.27365122e-10,
                             9.6467911e-11, 2.394038e-12,
                             -6.886027e-12, 8.94487e-13,
                             3.13092e-13, -1.12708e-13,
                             3.81e-16, 7.106e-15,
                             -1.523e-15, -9.4e-17,
                             1.21e-16, -2.8e-17};
    
    int size = sizeof coefficients / sizeof(double); //Gets length of array
    double d = 0.0;
    double dd = 0.0;

    for (int j = size -1; j > 0; j--){
        double tmp = d;
        d = ty*d - dd + coefficients[j];
        dd = tmp;
    }

    double ans = t*exp(-z*z + 0.5*(coefficients[0] + ty*d) - dd);
    return x >= 0.0 ? ans : (2.0 - ans);
} 


int main (){
    return -1;
}
