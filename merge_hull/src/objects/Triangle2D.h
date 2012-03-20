#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "src/objects/Point2D.h"

class Triangle2D {
public:
    Triangle2D();
    Triangle2D (Point2D, Point2D, Point2D);
    Triangle2D (const Triangle2D&);

    Triangle2D& operator = (const Triangle2D&);

    Point2D getA() {return a;}
    Point2D getB() {return b;}
    Point2D getC() {return c;}

protected:
    Point2D a;
    Point2D b;
    Point2D c;
};

#endif // TRIANGLE2D_H
