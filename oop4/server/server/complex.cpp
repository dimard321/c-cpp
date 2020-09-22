#include "complex.h"
#include <cmath>
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

complex sqrt(complex c){
        double r, phi, R;
        r=sqrt(c.im*c.im+c.re*c.re);
        phi=atan2(c.im, c.re);
        R=sqrt(r);
        c.re=R*cos(phi/2);
        c.im=R*sin(phi/2);
        return c;
}

bool complex::operator == (int x)
{
    if (re==x && im==x)
        return true;
    else
        return false;
}

bool complex::operator >= (complex)
{
    return true;
}

ostream& operator << (ostream& os, complex& c){
    char sign=' ';
    if(c.im==0)
    {
        os<<"("<<c.re<<")";
    }
    else if(c.re==0)
    {
         os<<"("<<c.im<<")i";
    }
    else{
    if(c.im>0) sign='+';
    else if (c.im<0){
        sign='-';
    }
    os<<"("<<c.re<<sign<<abs(c.im)<<"i)";
    }
    return os;
}
