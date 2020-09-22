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
istream& operator >> (istream& is, complex& c){
    is>>c.re>>c.im;
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
