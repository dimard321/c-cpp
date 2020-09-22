#ifndef DRAWER_H
#define DRAWER_H

#include <QRectF>
#include <QGraphicsScene>

class triangle;

class drawer
{
public:
    drawer(bool isRB, bool isRS, bool isAny);

    QPolygon updateData(qreal x, qreal y, qreal a, qreal b, qreal c);

    qreal S = 0;
    qreal P = 0;

private:

    bool isRB;
    bool isRS;
    bool isAny;

    QList<QPair<qreal, qreal>> getCoordinates(triangle tri, qreal x, qreal y, qreal b, qreal c);
};

#endif // DRAWER_H
