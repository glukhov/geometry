#include "Triangle2D.h"

Triangle2D::Triangle2D() {
}


Triangle2D::Triangle2D(Point2D a, Point2D b, Point2D c) :
    a(a),
    b(b),
    c(c) {
}


Triangle2D::Triangle2D(const Triangle2D &arg) :
    a(arg.a),
    b(arg.b),
    c(arg.c) {
}


Triangle2D& Triangle2D::operator = (const Triangle2D &arg) {
    a = arg.a;
    b = arg.b;
    c = arg.c;

    return *this;
}
