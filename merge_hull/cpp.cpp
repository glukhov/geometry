#include "stdafx.h"

#include "viewer.h"
#include <stack>


static point_type pole;

struct sort_class
{
    bool operator() (point_type i, point_type j)
    {
        if(get_angle(i, pole) == get_angle(j, pole))
            return (get_length(i, pole) < get_length(j, pole)) ;
        else
            return (get_angle(i, pole) <  get_angle(j, pole));
    }
} sort_points_by_angle;



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

std::vector<point_type> graham_scan(std::vector<point_type> points)
{
    pole = points[0];
    int pole_pos = 0;
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i].x < pole.x || (points[i].x == pole.x && points[i].y < pole.y))
        {
            pole = points[i];
            pole_pos = i;
        }
    }
    points.erase(points.begin() + pole_pos);

    std::sort(points.begin(), points.end(), sort_points_by_angle);

    std::vector<point_type> st;
    st.push_back(pole);
    st.push_back(points[0]);

    for(int i = 0; i < points.size(); i++)
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
