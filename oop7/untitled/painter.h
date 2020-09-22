#ifndef PAINTER_H
#define PAINTER_H


#include <QWidget>
#include <QPainter>
#include "shape.h"

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = nullptr);
    ~Painter();
    void setFigure(Parallelogramm* );
protected:
    void paintEvent(QPaintEvent *);

private:
    Parallelogramm *figure;
};


#endif // PAINTER_H
