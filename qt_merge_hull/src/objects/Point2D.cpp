#include "Point2D.h"

Point2D::Point2D ()  :
    x(0),
    y(0) {
}


Point2D::Point2D (int x, int y) :
    x (x),
    y (y) {
}


Point2D::Point2D (const Point2D &arg) :
    x (arg.x),
    y (arg.y) {
}


Point2D& Point2D::operator= (const Point2D &arg) {
    x = arg.x;
    y = arg.y;

    return *this;
}


Point2D Point2D::operator - (const Point2D &arg) {
    Point2D res (*this);
    return res -= arg;
}


Point2D& Point2D::operator -= (const Point2D &arg) {
    x -= arg.x;
    y -= arg.y;

    return *this;
}

bool operator ==(const Point2D& a, const Point2D& b)
{
    if(a.x == b.x && a.y == b.y)
        return 1;
    else
        return 0;
}
