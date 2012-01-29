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
        Gaussian operator * (const Gaussian &);
        double absoluteDifference (const Gaussian &);
        double operator - (const Gaussian &);
        double logProductNormalization (const Gaussian &);
        Gaussian operator / (const Gaussian &);
        double logRatioNormalization(const Gaussian &);
        double at(double);
        double at(double, double, double);
        double cumulativeTo(double);
        double cumulativeTo(double, double, double);
        double errorFunctionCumulativeTo(double); 
};
