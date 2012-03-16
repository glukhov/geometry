#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "src/objects/Point2D.h"

class Vector2D {
public:
    Vector2D ();
    Vector2D (Point2D, Point2D);
    Vector2D (const Vector2D &arg);

    Vector2D& operator = (const Vector2D &arg);

    int orientation (const Vector2D &arg);

protected:
    int x;
    int y;
};

#endif // VECTOR2D_H
