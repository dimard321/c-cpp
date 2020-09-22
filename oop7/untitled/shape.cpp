#include "shape.h"
#include <cmath>

Parallelogramm::Parallelogramm(double a, double b, double ab)
    :sideA(a), sideB(b), angleAB(ab/180*M_PI)
{}

double Parallelogramm::getArea()
{
    return sideA*sideB*sin(angleAB);
}

double Parallelogramm::getPerimeter()
{
    return 2*(sideA+sideB);
}


Rectangular::Rectangular(double a, double b)
    :Parallelogramm (a, b, 90)
{}

double Rectangular::getArea()
{
    return sideA*sideB;
}


Rhombus::Rhombus(double a, double ab)
    :Parallelogramm (a, a, ab)
{}

Square::Square(double a)
    :Parallelogramm (a,a, 90), Rectangular (a,a), Rhombus (a, 90)
{}

void Parallelogramm::getPoints(int *m)
{
    m[0] = 100;
    m[1] = 100;
    m[2] = 100 + 10*sideB;
    m[3] = 100;
    m[4] = 100 - 10*sideA*cos(angleAB);
    m[5] = 100 + 10*sideA*sin(angleAB);
    m[6] = 100 - 10*sideA*cos(angleAB) + 10*sideB;
    m[7] = 100 + 10*sideA*sin(angleAB);
}
