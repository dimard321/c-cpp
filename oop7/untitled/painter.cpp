#include "painter.h"


Painter::Painter(QWidget *parent)
    :QWidget(parent), figure(nullptr)
{}

Painter::~Painter()
{}

void Painter::setFigure(Parallelogramm* f)
{
    figure = f;
}

void Painter::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPolygon poly;

    int* pnts = new int[8];
    figure->getPoints(pnts); //получили координаты точек треугольника
    int x1 = pnts[0]; //topLeft
    int y1 = pnts[1];
    int x2 = pnts[2]; //topRight
    int y2 = pnts[3];
    int x3 = pnts[4]; //botLeft
    int y3 = pnts[5];
    int x4 = pnts[6]; //botRight
    int y4 = pnts[7];

    poly<<QPoint(x1,y1)<<QPoint(x2,y2)<<QPoint(x4,y4)<<QPoint(x3,y3);
    painter.drawPolygon(poly);
};
