class complex {
private:
    std::vector<double> pwer(std::vector<double>, int);
    std::vector<double> invert(std::vector<double>);
    double phase(std::vector<double>);
    double mag(std::vector<double>);
    complex unit(double);
public:
    std::vector<double> complexvector;
    complex(double , double);

    double phaseangle();
    double magnitude();
    complex Clog(double );
    complex operator * (complex);
    complex operator * (double );
    complex operator + (complex );
    complex operator / (complex);
    complex operator^(int );
}; 
