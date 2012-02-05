class truncatedGaussianCorrectionFunctions{
    public:
        double cumulativeTo(double);
        double cumulativeTo(double, double, double);
        double errorFunctionCumulativeTo(double); 
        double vExceedsMargin(double, double, double);
        double vExceedsMargin(double, double);
        double wExceedsMargin(double, double, double);
        double wExceedsMargin(double, double);
};
