#include "validator.h"

int Validator::test_size = TEST_SIZE;

Validator::Validator()
{
}


void Validator::generate()
{

    srand ( rand() );
    int a, b;
    for(int i = 0; i < this->test_size; i++)
    {
        /*
        *for Win
        a = (rand() - 16000) * (rand() - 16000);
        b = (rand() - 16000) * (rand() - 16000);
        */
        //For Unix
        a = (rand() - RAND_MAX / 2) % 100000000;
        b = (rand() - RAND_MAX / 2) % 100000000;
        points.push_back(Point2D (a, b));
        //printf("%d\n", RAND_MAX);
        //printf("%d %d\n", a, b);
    }

}

void Validator::get_hull()
{
     this->convex_hull = merge_hull (remove_equals(this->points));
}

bool Validator::test()
{
    if(points.size() == 1 && convex_hull.size() == 1)
        return true;
    if(points.size() == 2 && convex_hull.size() == 2)
        return true;
    for(int i = 0; i < convex_hull.size() - 3; i++)
    {
        if(!is_left(convex_hull[i], convex_hull[i + 1], convex_hull[i + 2]))
        {
            std::cout << "not convex poly";
            return false;
        }
    }
    std::cout << "good convex poly" << std::endl;

    std::vector<bool> is_hull (points.size(), false);
    for(int i = 0; i < convex_hull.size(); i++)
    {
        for(int j = 0; j < points.size(); j++)
        {
            if(convex_hull[i] == points[j])
                is_hull[j] = true;
        }
    }

    for(int i = 0; i < points.size(); i++)
    {
        if(!is_hull[i])
        {
            if(!in_polygon(convex_hull, points[i]))
            {
                std::cout << "point " << i << " is not in hull " << convex_hull[i].x << "   " << convex_hull[i].y << std::endl;
                return false;
            }
        }
    }

    std::cout << "all points are in hull" << std::endl << "all is OK" << std::endl << std::endl;
    return true;
}
