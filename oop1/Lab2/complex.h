#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;
class complex
{
    double re, im;
public:
    complex();
    complex(double, double);
    complex( const int&);
    complex operator*(complex);
    complex operator*(double);
    complex operator+(complex);
    complex operator-(complex);
    complex operator/(complex);

    double Re(){return re;}
    double Im(){return im;}
    friend istream& operator >> (istream& is, complex& c);
    friend ostream& operator << (ostream& os, complex& c);
};

#endif // COMPLEX_H
