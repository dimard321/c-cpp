#include "triangle.h"
#include <math.h>

triangle::triangle(qreal A, qreal B, qreal C)
{
    a = A;
    b = B;
    c = C;

    p = (a + b + c)/2;
    S = getS();
    Per = getPer();
}

qreal triangle::getPer()
{
    return (a + b + c);
}

qreal triangle::getS()
{
    return (sqrt(p * (p - a) * (p - b) * (p - c)));
}

qreal triangle::getRad()
{
    return (a * b * c)/(4 * S);
}

