#include "rectangle.h"

rectangle::rectangle(qreal a,qreal b, qreal x,qreal y)
{
    this->a = a;
    this->b = b;
    this->x = x;
    this->y = y;
}


bool rectangle::contains(QPointF p)
{
    qreal xp = p.rx();
    qreal yp = p.ry();
    if (xp>x+a/2 || xp<x-a/2 || yp<y-b/2 || yp>y+b/2)
    {
        return false;
    }
    return true;
}
