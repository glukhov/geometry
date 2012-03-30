#include "validator.h"

Validator::Validator()
{
}

void Validator::generate()
{

    srand ( time(NULL) );
    int a, b;
    for(int i = 0; i < 1000; i++)
    {
        a = (rand() - 16000) * (rand() - 16000);
        b = (rand() - 16000) * (rand() - 16000);
        points.push_back(Point2D (a, b));
    }

}

void Validator::get_hull()
{
     this->convex_hull = merge_hull (remove_equals(this->points));
}

bool Validator::test()
{
    for(int i = 0; i < convex_hull.size() - 3; i++)
    {
        if(!is_left(convex_hull[i], convex_hull[i + 1], convex_hull[i + 2]))
        {
            std::cout << "not convex poly";
            return false;
        }
    }
    std::cout << "good convex poly" << std::endl;

    std::vector<bool> in_hull (points.size(), false);
    for(int i = 0; i < convex_hull.size(); i++)
    {
        for(int j = 0; j < points.size(); j++)
        {
            if(convex_hull[i] == points[j])
                in_hull[j] = true;
        }
    }

    for(int i = 0; i < points.size(); i++)
    {
        if(!in_hull[i])
        {
            if(!in_polygon(convex_hull, points[i]))
            {
                std::cout << "point " << i << " is not in hull " << convex_hull[i].x << "   " << convex_hull[i].y << std::endl;
                return false;
            }
        }
    }

    std::cout << "all points are in hull" << std::endl << "all is OK, waiting picture" << std::endl << std::endl;
    return true;
}
