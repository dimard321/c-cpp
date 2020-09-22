#ifndef POLINOM_H
#define POLINOM_H

#include "number.h"
#include <iostream>
using namespace std;

class polinom
{
    number a,b,c;
public:

    polinom(number,number,number);
    number value(number);
    int roots(number*);

    friend ostream& operator << (ostream& os, polinom& p);
};

#endif // POLINOM_H
