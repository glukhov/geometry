#include "stdafx.h"

#include "viewer.h"
#include <stack>

#define SIZE 5
//static point_type pole;

class sort_class
{
    point_type pole;
    sort_class(point_type p)
    {
        this->pole = p;
    }

    bool operator() (point_type i, point_type j)
    {
        if(get_angle(i, pole) == get_angle(j, pole))
            return (get_length(i, pole) < get_length(j, pole)) ;
        else
            return (get_angle(i, pole) <  get_angle(j, pole));
    }
};



double get_angle(point_type p1, point_type p2)
{
    return (p2.x - p1.x) / (p2.y - p1.y);
}
double get_length(point_type p1, point_type p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

int is_left(point_type p1, point_type p2, point_type p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
std::vector<point_type> graham_scan(std::vector<point_type> points, point_type pole)
{
    std::vector<point_type> st;
    st.push_back(pole);
    st.push_back(points[0]);

    for(int i = 1; i < points.size(); i++)
    {
        if(is_left(st[st.size() - 2], st[st.size() - 1], points[i] ) > 0)
        {
            st.push_back(points[i]);
        }
        else
        {
            st.pop_back();
        }
    }
    return st;

}
int get_pole(std::vector<point_type> points)
{
    point_type pole = points[0];
    int pole_pos = 0;
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i].x < pole.x || (points[i].x == pole.x && points[i].y < pole.y))
        {
            pole = points[i];
            pole_pos = i;
        }
    }
    return pole_pos;
}

std::vector<point_type> get_hull(std::vector<point_type> points)
{
    int pole_pos = get_pole(points);
    point_type pole = points[pole_pos];
    points.erase(points.begin() + pole_pos);

    sort_class sorter(pole);
    std::sort(points.begin(), points.end(), sorter);

    std::vector<point_type> hull = graham_scan(points, pole);

    return hull;

}
std::vector<point_type> get_hull_sorted(std::vector<point_type> sorted_points)
{
    int pole_pos = get_pole(sorted_points);
    point_type pole = sorted_points[pole_pos];
    sorted_points.erase(sorted_points.begin() + pole_pos);

    std::vector<point_type> hull = graham_scan(sorted_points, pole);

    return hull;

}
point_type centroid(point_type p1, point_type p2, point_type p3)
{
    point_type p;
    p.x = (p1.x + p2.x + p3.x) / 3;
    p.y = (p1.y + p2.y + p3.y) / 3;
    return p;
}

std::vector<point_type> merge(std::vector<point_type> set1, std::vector<point_type> set2)
{
    point_type p = centroid(set1[0], set1[1], set1[2]);
    std::vector<point_type> sum;
    if(in_polygon(set2, p) != 0)
    {
        for(int i = 0, j = 0; i < set1.size() && j < set2.size();)
        {
            if(get_angle(i, p) == get_angle(j, p))
            {
                if(get_length(i, p) < get_length(j, p))
                {
                    sum.push_back(set1[i++]);
                }
                else
                {
                    sum.push_back(set2[j++]);
                }
            }
            else
            {
                if(get_angle(i, p) < get_angle(j, p))
                {
                    sum.push_back(set1[i++]);
                }
                else
                {
                    sum.push_back(set2[j++]);
                }
            }
        }
    }
    else
    {
           //not_in
    }
    return get_hull_sorted(sum);
}

int in_polygon(std::vector<point_type> polygon, point_type p)
{
    for(int i = 0; i < polygon.size() - 1; i++)
    {
        if(is_left(polygon[i], polygon[i + 1], p) < 0)
            return 0;
    }
    return 1;
}

std::vector<point_type> merge_hull(std::vector<point_type> set)
{

    if (set.size() < SIZE)
    {
        return get_hull(set);
    }


    std::vector<point_type> set1 = set.assign(set.begin(), set.begin() + set.size() / 2);
    std::vector<point_type> set2 = set.assign(set.size() / 2 + 1, set.end());

    std::vector<point_type> hull1 = merge_hull(set1);
    std::vector<point_type> hull2 = merge_hull(set2);

    rerurn merge(hull1, hull2);



}


