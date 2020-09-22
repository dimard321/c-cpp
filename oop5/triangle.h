#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QRectF>

class triangle
{
public:
    triangle(qreal, qreal, qreal);

    qreal getPer();

    qreal getS();

    qreal getRad();

private:
    qreal a, b,c;

    qreal Per, p, S;
};

#endif // TRIANGLE_H
