
#include "Point2Df.h"

Point2Df::Point2Df ()  :
    x(0),
    y(0) {
}


Point2Df::Point2Df (double x, double y) :
    x (x),
    y (y) {
}


Point2Df::Point2Df (const Point2Df &arg) :
    x (arg.x),
    y (arg.y) {
}

Point2Df::Point2Df (const Point2D &arg) :
    x (arg.x),
    y (arg.y) {
}



Point2Df& Point2Df::operator= (const Point2Df &arg) {
    x = arg.x;
    y = arg.y;

    return *this;
}

Point2Df& Point2Df::operator= (const Point2D &arg) {
    x = arg.x;
    y = arg.y;

    return *this;
}



bool operator ==(const Point2Df& a, const Point2Df& b)
{
    if(a.x == b.x && a.y == b.y)
        return 1;
    else
        return 0;
}
bool operator <(const Point2Df& a, const Point2Df& b)
{
    if(a.x < b.x)
        return 1;
    else if(a.x == b.x && a.y < b.y)
        return 1;
    else
        return 0;
}
