#include "Vector2D.h"

Vector2D::Vector2D() :
    x(0),
    y(0) {
}


Vector2D::Vector2D (Point2D a, Point2D b) :
    x (b.getX() - a.getX()),
    y (b.getY() - a.getY()) {
}


Vector2D::Vector2D (const Vector2D &arg) :
    x (arg.x),
    y (arg.y) {
}


Vector2D& Vector2D::operator = (const Vector2D &arg) {
    x = arg.x;
    y = arg.y;

    return *this;
}


int Vector2D::orientation(const Vector2D &arg) {
    return x * arg.y - y * arg.x;
}
