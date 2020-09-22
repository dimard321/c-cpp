#include "ellipse.h"

ellipse::ellipse(qreal w, qreal h, qreal x, qreal y)
{
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
}

bool ellipse::contains(QPointF p)
{
    qreal xp = p.rx();
    qreal yp = p.ry();
    qreal a = w/2;
    qreal b = h/2;
    if ((xp-x)*(xp-x)/(a*a) + (yp-y)*(yp-y)/(b*b) > 1)
    {
        return false;
    }
    return true;
}
