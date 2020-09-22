#include "complex.h"

complex::complex()
{
    re=0;
    im=0;
}

complex::complex(double x, double y)
{
    re=x;
    im=y;
}

complex::complex(const int &i)
{
    re=i;
    im=0;
}

QString complex :: toString(){
    return '(' + QString::number(this->re)+'+' +QString::number(this->im)+ "i)";
}

complex complex :: operator*(complex c){
        return complex(re*c.re-im*c.im, re*c.im+im*c.re);
}

complex complex :: operator*(double d){
    return complex(re*d,im*d);
}

complex complex :: operator+(complex c){
    return complex(re+c.re,im+c.im);
}

complex complex :: operator/(complex c){
    c.im *=-1;
    complex numerator=(*this)*c;
    double denominator= c.re*c.re+c.im*c.im;
    return complex(numerator.re/denominator,numerator.im/denominator);
}

complex complex :: operator-(complex c){
    return complex(re-c.re,im-c.im);
}
