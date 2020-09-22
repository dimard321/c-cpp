#include "target.h"
#include <QRandomGenerator>
target::target()
{

}

target::target(qreal w, qreal h)
{
    this->w = w;
    this->h = h;
}

qreal target::getWidth(){
    return this->w;
}

qreal target::getHeight(){
    return this->h;
}


qreal target::attitudeNew(qreal i, qreal j, figure* pFig, int type)
{
    qreal c = 0;
    qreal all = 0;
    QPoint dot;
    if (type == 0) //regular
    {
        qreal stepX = w/i;
        qreal stepY = h/j;
        for(qreal i = -h/2; i <= h/2; i+=stepY)
            for(qreal j = -w/2; j <= w/2; j+=stepX)
            {
                dot.setX(j);
                dot.setY(i);
                if (!pFig->contains(dot))
                {
                    c++;
                }
                all++;
            }
    }
    else if (type == 1) //random
    {
        QRandomGenerator randGen;
        qreal randX;
        qreal randY;
        all = i*j;
        for(int k = 0; k <i*j; k++)
        {
            randX =  (2*randGen.securelySeeded().generateDouble()-1)*w/2;
            randY =  (2*randGen.securelySeeded().generateDouble()-1)*h/2;
            dot.setX(randX);
            dot.setY(randY);
            if (!pFig->contains(dot))
            {
                c++;
            }
        }
    }
    else
    {
        return -1;
    }

    return c/all;
}
