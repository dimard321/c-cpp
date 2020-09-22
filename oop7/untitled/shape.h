#ifndef SHAPE_H
#define SHAPE_H


class Parallelogramm
{
protected:
    double sideA;
    double sideB;
    double angleAB;

public:
    Parallelogramm(double,double,double);
    double getArea();
    double getPerimeter();
    void   getPoints(int*);
};

class Rectangular : public virtual Parallelogramm
{
public:
    Rectangular(double, double);
    double getArea();
};

class Rhombus : public virtual Parallelogramm
{
public:
    Rhombus(double, double);
};

class Square : public Rectangular, Rhombus
{
public:
    Square(double);
};

#endif // SHAPE_H
