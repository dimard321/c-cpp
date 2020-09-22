#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "figure.h"

class rectangle : public figure
{
public:
    rectangle(qreal a, qreal b, qreal x, qreal y);
    bool contains(QPointF) override;
private:
    qreal a;
    qreal b;
};

#endif // RECTANGLE_H
