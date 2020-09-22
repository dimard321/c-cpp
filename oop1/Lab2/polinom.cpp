#include "polinom.h"
#include "math.h"
polinom::polinom(number x,number y,number z)
{
    a=x;b=y;c=z;
}

number polinom::value(number x)
{
    return a*x*x+b*x+c;
}

int polinom::roots(number* x)
{
      number D = b*b-a*c*4;
      double reD = D.Re();
      double imD = D.Im();
      number sqrtD;
      double re_sqrtD=0,im_sqrtD=0;
      double absD = sqrt(reD*reD+imD*imD);
      double argD = atan(imD/reD);

      if (reD < 0 && imD>0){
          argD = M_PI+atan(imD/reD);
      }
      else if (reD < 0 && imD<0){
          argD = (-1)*M_PI+atan(imD/reD);
      }

      if (reD==0 &&imD==0){
          x[0] = (b*(-1))/(a*2);
          return 1;
      }
      else if (reD>0 &&imD==0) {
          re_sqrtD =sqrt(reD);
          im_sqrtD=0;
      }
      else if (reD<0 &&imD==0)
      {
          im_sqrtD =sqrt(reD*(-1));
          re_sqrtD=0;
      }
      else {
        re_sqrtD= sqrt(absD)*cos((argD)/2);
        im_sqrtD = sqrt(absD)*sin((argD)/2);
      }


      sqrtD = number(re_sqrtD, im_sqrtD);
      x[0] = (b*(-1)+sqrtD)/(a*2);
      x[1] = (b*(-1)-sqrtD)/(a*2);
      return 2;
}


ostream& operator<< (ostream& os,polinom& p)
{
    os<<p.a<<"x^2+"<<p.b<<"x+"<<p.c;
    return os;
}
