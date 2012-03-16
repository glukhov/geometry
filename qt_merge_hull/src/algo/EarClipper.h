#ifndef EARCLIPPER_H
#define EARCLIPPER_H

#include <cmath>
#include <utility>
#include <vector>
#include <iostream>
#include "src/objects/Graph.h"
#include "src/objects/Vector2D.h"
#include "src/objects/Triangle2D.h"

class EarClipper {
public:
    static Graph <Point2D> triangulate (const Graph <Point2D> &arg, std::vector <Triangle2D> *triangles = 0);
};

#endif // EARCLIPPER_H
