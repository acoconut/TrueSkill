#include <math.h>
#include <stdlib.h>;
#include "truncatedGaussianCorrectionFunctions.h";
#include "gaussian.h";
#include "constants.h";

double truncatedGaussianCorrectionFunctions::cumulativeTo (double x){
    return cumulativeTo (x, 0, 1);
}

double truncatedGaussianCorrectionFunctions::cumulativeTo (double x, double mean, double standardDeviation){
    const double invsqrt2 = 1/sqrt(2);
    double result = errorFunctionCumulativeTo(invsqrt2*x);
    return 0.5*result;
}

double truncatedGaussianCorrectionFunctions::at (double x){
     return truncatedGaussianCorrectionFunctions::at(x, 0, 1);
}

double truncatedGaussianCorrectionFunctions::at (double x, double mean, double standardDeviation){
     double multiplier = 1.0/(standardDeviation * sqrt(2*PI));
     double expPart = exp((-1.0*pow(x - mean, 2.0))/(2*(standardDeviation*standardDeviation)));
     return multiplier*expPart;
}

double truncatedGaussianCorrectionFunctions::errorFunctionCumulativeTo (double x){
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

/** V Functions, where the team performance difference is greater than the draw margin. **/

double truncatedGaussianCorrectionFunctions::vExceedsMargin (double teamPerformanceDifference, double drawMargin){
    double denominator = truncatedGaussianCorrectionFunctions::cumulativeTo(teamPerformanceDifference - drawMargin);
    if (denominator < 2.222758749e-162){
        return -teamPerformanceDifference + drawMargin;
    }
}

double truncatedGaussianCorrectionFunctions::vExceedsMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::vExceedsMargin(teamPerformanceDifference/c, drawMargin/c);
}


double truncatedGaussianCorrectionFunctions::wExceedsMargin (double teamPerformanceDifference, double drawMargin){
    double denominator = truncatedGaussianCorrectionFunctions::cumulativeTo(teamPerformanceDifference - drawMargin);
    if (denominator < 2.222758749e-162){
        if (teamPerformanceDifference < 0.0){
            return 1.0;
        }
        return 0.0;
    }
    double vWin = truncatedGaussianCorrectionFunctions::vExceedsMargin(teamPerformanceDifference, drawMargin);
    return vWin * (vWin + teamPerformanceDifference - drawMargin);
}

double truncatedGaussianCorrectionFunctions::wExceedsMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::wExceedsMargin(teamPerformanceDifference/c, drawMargin/c);
}

/** The additive correction of a double-sided truncated Gaussian with unit variance */
double truncatedGaussianCorrectionFunctions::vWithinMargin (double teamPerformanceDifference, double drawMargin){
    double teamPerformanceDifferenceAbsoluteValue = abs(teamPerformanceDifference);
    double denominator = truncatedGaussianCorrectionFunctions::cumulativeTo(drawMargin - teamPerformanceDifferenceAbsoluteValue) - truncatedGaussianCorrectionFunctions::cumulativeTo(-drawMargin - teamPerformanceDifferenceAbsoluteValue);
    if (denominator < 2.222758749e-162){
        if (teamPerformanceDifference < 0.0){
            return -teamPerformanceDifference - drawMargin;
        }
        return -teamPerformanceDifference + drawMargin;
    }

    double numerator = truncatedGaussianCorrectionFunctions::at(-drawMargin - teamPerformanceDifferenceAbsoluteValue) - truncatedGaussianCorrectionFunctions::at(drawMargin - teamPerformanceDifferenceAbsoluteValue);
    if (teamPerformanceDifference < 0.0)
        return -numerator/denominator;
    return numerator/denominator;
}

double truncatedGaussianCorrectionFunctions::vWithinMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::vWithinMargin(teamPerformanceDifference/c, drawMargin/c);
}

double truncatedGaussianCorrectionFunctions::wWithinMargin (double teamPerformanceDifference, double drawMargin){
    double teamPerformanceDifferenceAbsoluteValue = abs(teamPerformanceDifference);
    double denominator = truncatedGaussianCorrectionFunctions::cumulativeTo(drawMargin - teamPerformanceDifference) - truncatedGaussianCorrectionFunctions::cumulativeTo(-drawMargin - teamPerformanceDifference);
    if (denominator < 2.222758749e-162)
        return 1.0;
    
    double vt = truncatedGaussianCorrectionFunctions::vWithinMargin(teamPerformanceDifferenceAbsoluteValue, drawMargin);
    
    return vt*vt + (drawMargin - teamPerformanceDifferenceAbsoluteValue) * truncatedGaussianCorrectionFunctions::at(drawMargin - teamPerformanceDifferenceAbsoluteValue) - (-drawMargin - teamPerformanceDifferenceAbsoluteValue) * truncatedGaussianCorrectionFunctions::at(-drawMargin - teamPerformanceDifferenceAbsoluteValue)/denominator;
}

double truncatedGaussianCorrectionFunctions::wWithinMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::wWithinMargin(teamPerformanceDifference/c, drawMargin/c);
}
