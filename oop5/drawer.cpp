#include "drawer.h"
#include "triangle.h"
#include "RS_triangle.h"

#include <QPainter>
#include <QPolygon>
#include <QWindow>
#include <triangle.h>
#include <math.h>

drawer::drawer(bool RB, bool RS, bool Any)
{
    isRB = RB;
    isRS = RS;
    isAny= Any;
}


QPolygon drawer::updateData(qreal x, qreal y, qreal a, qreal b, qreal c)
{
    QList<QPair<qreal, qreal>> coords;
    if (isRS)
    {
        rs_triangle tri(a);
        coords = getCoordinates(tri, x, y, a, a);
        P = tri.getPer();
        S = tri.getS();
    }
    else if(isRB)
    {
        rb_triangle tri(a, b);
        coords = getCoordinates(tri, x, y, b, b);
        P = tri.getPer();
        S = tri.getS();
    }
    else if(isAny)
    {
        triangle tri (a, b, c);
        coords = getCoordinates(tri, x, y, b, c);
        P = tri.getPer();
        S = tri.getS();
    }


    QPolygon polygon;

    polygon << QPoint(coords[0].first, (-1)*coords[0].second) <<
               QPoint(coords[1].first, (-1)*coords[1].second) <<
               QPoint(coords[2].first, (-1)*coords[2].second);
    return polygon;
}

QList<QPair<qreal, qreal>> drawer::getCoordinates(triangle tri, qreal x, qreal y, qreal b, qreal c)
{
    QList<QPair<qreal, qreal>> coords;
    QPair<qreal, qreal> temp;
    qreal rad = tri.getRad();
    temp.first = x;
    temp.second = y + rad;
    coords.push_back(temp);

    double sinB = b/(2*rad);
    double cosB = sqrt(1 - (b/(2*rad)) * (b/(2*rad)));
    temp.second = y - rad * cosB;
    temp.first = x + (sinB * rad);
    coords.push_back(temp);

    double sinC = c/(2*rad);
    double cosC = sqrt(1 - sinC *sinC);
    temp.first = x - (sinC * rad);
    temp.second = (y - rad*cosC);
    coords.push_back(temp);
    return coords;
}
