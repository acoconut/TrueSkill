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
