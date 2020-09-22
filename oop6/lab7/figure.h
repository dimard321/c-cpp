#ifndef FIGURE_H
#define FIGURE_H

#include <QPointF>

class figure
{
public:
    virtual bool contains(QPointF)=0;
protected:
    qreal x;
    qreal y;
    void setXY(qreal, qreal);
};

#endif // FIGURE_H
