#ifndef POLINOM_H
#define POLINOM_H

#include "complex.h"
#include <iostream>
using namespace std;

class polinom
{
    complex a,b,c;
public:

    polinom(complex,complex,complex);
    complex value(complex);
    int roots(complex*);

    friend ostream& operator << (ostream& os, polinom& p);

    QString text();
};

#endif // POLINOM_H
