#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "figure.h"

class ellipse : public figure
{
public:
    ellipse(qreal a, qreal b, qreal x, qreal y);
    bool contains(QPointF) override;
private:
    qreal w;
    qreal h;
};

#endif // ELLIPSE_H
