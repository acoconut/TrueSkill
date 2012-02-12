#include "trueSkillMath.nsp.h"
#include <stdlib.h>;
#include "truncatedGaussianCorrectionFunctions.h";
#include "gaussian.h";

/** V Functions, where the team performance difference is greater than the draw margin. **/

double truncatedGaussianCorrectionFunctions::vExceedsMargin (double teamPerformanceDifference, double drawMargin){
    double denominator = trueSkillMath::cumulativeTo(teamPerformanceDifference - drawMargin);
    if (denominator < 2.222758749e-162){
        return -teamPerformanceDifference + drawMargin;
    }
}

double truncatedGaussianCorrectionFunctions::vExceedsMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::vExceedsMargin(teamPerformanceDifference/c, drawMargin/c);
}


double truncatedGaussianCorrectionFunctions::wExceedsMargin (double teamPerformanceDifference, double drawMargin){
    double denominator = trueSkillMath::cumulativeTo(teamPerformanceDifference - drawMargin);
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
    double denominator = trueSkillMath::cumulativeTo(drawMargin - teamPerformanceDifferenceAbsoluteValue) - trueSkillMath::cumulativeTo(-drawMargin - teamPerformanceDifferenceAbsoluteValue);
    if (denominator < 2.222758749e-162){
        if (teamPerformanceDifference < 0.0){
            return -teamPerformanceDifference - drawMargin;
        }
        return -teamPerformanceDifference + drawMargin;
    }

    double numerator = trueSkillMath::at(-drawMargin - teamPerformanceDifferenceAbsoluteValue) - trueSkillMath::at(drawMargin - teamPerformanceDifferenceAbsoluteValue);
    if (teamPerformanceDifference < 0.0)
        return -numerator/denominator;
    return numerator/denominator;
}

double truncatedGaussianCorrectionFunctions::vWithinMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::vWithinMargin(teamPerformanceDifference/c, drawMargin/c);
}

double truncatedGaussianCorrectionFunctions::wWithinMargin (double teamPerformanceDifference, double drawMargin){
    double teamPerformanceDifferenceAbsoluteValue = abs(teamPerformanceDifference);
    double denominator = trueSkillMath::cumulativeTo(drawMargin - teamPerformanceDifference) - trueSkillMath::cumulativeTo(-drawMargin - teamPerformanceDifference);
    if (denominator < 2.222758749e-162)
        return 1.0;
    
    double vt = truncatedGaussianCorrectionFunctions::vWithinMargin(teamPerformanceDifferenceAbsoluteValue, drawMargin);
    
    return vt*vt + (drawMargin - teamPerformanceDifferenceAbsoluteValue) * trueSkillMath::at(drawMargin - teamPerformanceDifferenceAbsoluteValue) - (-drawMargin - teamPerformanceDifferenceAbsoluteValue) * trueSkillMath::at(-drawMargin - teamPerformanceDifferenceAbsoluteValue)/denominator;
}

double truncatedGaussianCorrectionFunctions::wWithinMargin (double teamPerformanceDifference, double drawMargin, double c){
    return truncatedGaussianCorrectionFunctions::wWithinMargin(teamPerformanceDifference/c, drawMargin/c);
}
