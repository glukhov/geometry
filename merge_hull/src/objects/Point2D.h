#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
public:
    Point2D ();
    Point2D (int, int);
    Point2D (const Point2D &arg);

    Point2D& operator = (const Point2D &arg);
    Point2D operator - (const Point2D &arg);
    Point2D& operator -= (const Point2D &arg);

    friend bool operator ==(const Point2D& a, const Point2D& b);
    friend bool operator <(const Point2D& a, const Point2D& b);
    int getX () {return x;}
    int getY () {return y;}
    int x;
    int y;
};


#endif // POINT2D_H
