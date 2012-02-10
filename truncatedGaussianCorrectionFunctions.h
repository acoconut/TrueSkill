class truncatedGaussianCorrectionFunctions{
    private:
        double cumulativeTo(double);
        double cumulativeTo(double, double, double);
        double at(double);
        double at(double, double, double);
    public:
        double errorFunctionCumulativeTo(double); 
        double vExceedsMargin(double, double);
        double vExceedsMargin(double, double, double);
        double wExceedsMargin(double, double);
        double wExceedsMargin(double, double, double);
        double vWithinMargin(double, double);
        double vWithinMargin(double, double, double);
        double wWithinMargin(double, double);
        double wWithinMargin(double, double, double);
};
