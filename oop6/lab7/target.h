#ifndef TARGET_H
#define TARGET_H

#include <QWidget>
#include "figure.h"
class target
{
public:
    target();
    target(qreal, qreal);
    qreal getHeight();
    qreal getWidth();
    qreal attitudeNew(qreal i, qreal j, figure*, int);
private:
    qreal w;
    qreal h;
};

#endif // TARGET_H
