#ifndef POLINOM_H
#define POLINOM_H

#include "complex.h"
#include "math.h"
#include <iostream>
using namespace std;
template <typename number>
class polinom
{
    number a,b,c;
public:

    polinom(number,number,number);
    number value(number);
    int roots(number*);
    template<typename U>
    friend ostream& operator<< (ostream&, polinom <U>&);
};


template <typename number>
polinom<number>::polinom(number x,number y,number z)
{
    a=x;b=y;c=z;
}

template <typename number>
number polinom<number>::value(number x)
{
    return a*x*x+b*x+c;
}

template <typename number>
int polinom<number>::roots(number* x)
{
            number Disc = b*b-a*c*4;
            if (Disc==0)
            {
               x[0] = (b*(-1))/(a*2);
               return 1;
            } else if (Disc>=0) {
               x[0] = (b*(-1)+sqrt(Disc))/(a*2);
               x[1] = (b*(-1)-sqrt(Disc))/(a*2);
               return 2;
            }
            else {
                return 3;
            }
}
template <typename number>
ostream& operator<< (ostream &os, polinom <number> &p)
{
    os << p.a << "*x^2+" << p.b << "*x+"<<p.c;
    return os;
}

#endif // POLINOM_H

