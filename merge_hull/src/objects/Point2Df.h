#pragma once
#include "Point2D.h"
class Point2Df :
    public Point2D
{
public:
    Point2Df(void);
    Point2Df(double, double);
    Point2Df (const Point2Df &arg);
    Point2Df (const Point2D &arg);

    Point2Df& operator = (const Point2Df &arg);
    Point2Df& operator = (const Point2D &arg);

    friend bool operator ==(const Point2Df& a, const Point2Df& b);
    friend bool operator <(const Point2Df& a, const Point2Df& b);

    double getX () {return x;}
    double getY () {return y;}
    double x;
    double y;
};

