#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <stdlib.h>
#include <time.h>
#include "src/objects/Point2D.h"
#include "src/algo/merge_hull.h"
#include <vector>

#define TEST_SIZE 10000

class Validator
{
public:

    static int test_size;
    std::vector<Point2D> convex_hull;
    std::vector<Point2D> points;
    void generate();
    void get_hull();
    bool test();
    Validator();

};


#endif // VALIDATOR_H
