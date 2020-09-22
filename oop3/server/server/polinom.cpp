#include "polinom.h"
#include "math.h"
polinom::polinom(complex x,complex y,complex z)
{
    a=x;b=y;c=z;
}

complex polinom::value(complex x)
{
    return a*x*x+b*x+c;
}

int polinom::roots(complex* x)
{
            complex Disc = b*b-a*c*4;
            double reDisc = Disc.Re();
            double imDisc = Disc.Im();

            double absZ = sqrt(reDisc*reDisc+imDisc*imDisc);
            double argZ = atan(imDisc/reDisc);


            if (reDisc < 0 && imDisc>0) argZ = M_PI+atan(imDisc/reDisc);
            if (reDisc < 0 && imDisc<0) argZ = (-1)*M_PI+atan(imDisc/reDisc);


            double reZ = sqrt(absZ)*cos((argZ)/2);
            double imZ = sqrt(absZ)*sin((argZ)/2);
            complex Z = complex(reZ, imZ);
            if (reZ == 0 && imZ ==0)
            {
               x[0] = (b*(-1))/(a*2);
               return 1;
            } else {
                x[0] = (b*(-1)+Z)/(a*2);
                x[1] = (b*(-1)-Z)/(a*2);
                return 2;
            }

}


QString polinom::text(){
    QString txt = a.toString()+"x^2+"+b.toString()+"x+"+c.toString();
    return txt;
}
