#include <iostream>
#include <stdio.h>
#include <vector>
#include <SDL.h>
#include <cmath>

class complex {
private:
    std::vector<double> pwer(std::vector<double> c, int power) {
        double imaginary;
        double real;
        for (int x = 0; x <= power; x++) {
            real = pow(c[0], 2) - pow(c[1], 2);
            imaginary = c[1] * c[0] + c[0] * c[1];
            c[0] = real;
            c[1] = imaginary;
        } return c;
    }
    std::vector<double> invert(std::vector<double> c) {
        double re = c[0];
        double im = c[1];
        re = c[0] / (pow(c[0], 2) + pow(c[1], 2));
        im = (-c[1]) / (pow(c[0], 2) + pow(c[1], 2));
        return std::vector<double> {re, im};
    }
    double phase(std::vector<double> c) {
        return atan(c[1] / c[0]);
    }
    double mag(std::vector<double> c) {
        return pow(c[0], 2) + pow(c[1], 2);
    }
    complex unit(double p) {
        return complex(cos(p), sin(p));
    }
public:

    std::vector<double> complexvector;
    complex(double r, double im) {
        complexvector = { r,im };
    }

    double phaseangle() {
        return phase(complexvector);
    }
    double magnitude() {
        return mag(complexvector);
    }
    complex Clog(double n) {
        return complex(log(magnitude()) / log(n), phaseangle() / log(n));
    }
    complex operator * (complex comp) {
        complex result(0, 0);
        result.complexvector[0] = complexvector[0] * comp.complexvector[0] - complexvector[1] * comp.complexvector[1];
        result.complexvector[1] = complexvector[1] * comp.complexvector[0] + complexvector[0] * comp.complexvector[1];
        return result;
    }
    complex operator * (double r) {
        complex result(0, 0);
        result.complexvector[0] = complexvector[0] * r;
        result.complexvector[1] = complexvector[1] * r;
        return result;
    }
    complex operator + (complex comp) {
        complex result(0, 0);
        result.complexvector[0] = complexvector[0] + comp.complexvector[0];
        result.complexvector[1] = complexvector[1] + comp.complexvector[1];
        return result;
    }
    complex operator / (complex comp) {
        complex result(0, 0);
        result.complexvector[0] = (complexvector[0] * comp.complexvector[0] + complexvector[1] * comp.complexvector[1]) / (pow(comp.complexvector[0], 2) + pow(comp.complexvector[1], 2));
        result.complexvector[1] = (complexvector[1] * comp.complexvector[0] - complexvector[0] * comp.complexvector[1]) / (pow(comp.complexvector[0], 2) + pow(comp.complexvector[1], 2));
        return result;
    }
    complex operator ^ (int power) {
        complex result(0, 0);
        result.complexvector[0] = complexvector[0];
        result.complexvector[1] = complexvector[1];
        return result;
        if (power > 0) {
            result.complexvector = pwer(complexvector, power);
        }
        else if (power == 0) {
            result.complexvector[0] = 1;
            result.complexvector[0] = 0;
        }
        else {
            result.complexvector = pwer(invert(complexvector), -power);

        }
        return result;
    }
    complex operator ^ (complex comp) {

        complex Exponent = Clog(exp(1));
        complex ResultExponent = Exponent * comp;
        complex Result = unit(ResultExponent.complexvector[1]) * exp(ResultExponent.complexvector[0]);
    }
};