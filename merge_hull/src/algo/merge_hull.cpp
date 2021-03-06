
#include "src/algo/merge_hull.h"


//do not want smallest sets to be < 3   (6/2 = 3)
#define SIZE 5

class sort_class
{
public:
    Point2D pole;
    sort_class(Point2D p)
    {
        this->pole = p;
    }

    bool operator() (Point2D i, Point2D j)
    {
        return angle_compare(pole, i, j);
    }
};


bool is_line(std::vector<Point2D> points)
{
    if(points.size() < 3)
    {
        //printf("2 points");
        return true;
    }

    for(int i = 0; i < points.size() - 2; i++)
    {
        if(is_left(points[i], points[i + 1], points[i + 2]) != 0)
            return false;
    }

    return true;
}

int get_pole(std::vector<Point2D> points)
{
    Point2D pole = points[0];
    int pole_pos = 0;
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i].y < pole.y || (points[i].y == pole.y && points[i].x < pole.x))
        {
            pole = points[i];
            pole_pos = i;
        }
    }
    return pole_pos;
}

double get_length(Point2D p1, Point2D p2)
{

    double x = p2.x - p1.x;
    x *= x;
    double y = p2.y - p1.y;
    y *= y;
    double sum = x + y;
    sum = sqrt(sum);
    return sum;
    //return sqrt(double((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));

}



long long int is_left(Point2D p1, Point2D p2, Point2D p3)
{
   // -236479*165277 - -259106*176670
    long long int res = ((long long int)p2.x - (long long int)p1.x);
    res *= ((long long int)p3.y - (long long int)p1.y);
    long long int res2 =  ((long long int)p3.x - (long long int)p1.x);
    res2 *=  ((long long int)p2.y - (long long int)p1.y);
    long long int res3 = res - res2;
    return res3;
}

double is_left(Point2Df p1, Point2Df p2, Point2Df p3)
{
   // -236479*165277 - -259106*176670
    double res = (p2.x - p1.x);
    res *= (p3.y - p1.y);
    double res2 =  (p3.x - p1.x);
    res2 *=  (p2.y - p1.y);
    double res3 = res - res2;
    return res3;
}


//returns i < j
bool angle_compare(Point2D  pole, Point2D  i, Point2D  j)
{
    if(pole == i)
        return 1;
    if(pole == j)
        return 0;
    if(is_left(pole, i , j) == 0)
        {
            if( (i.y > pole.y && j.y > pole.y) || (i.y < pole.y && j.y < pole.y) )
            {
                return (get_length(i, pole) < get_length(j, pole));
            }
            else if(i.y == pole.y && j.y == pole.y)
            {
                if( (i.x > pole.x && j.x > pole.x) || (i.x < pole.x && j.x < pole.y) )
                    return (get_length(i, pole) < get_length(j, pole));
                else
                    return (i.x < j.x);
            }
            else
            {
                return (i.y > j.y);
            }
        }
        else
        {
            if(is_left(pole, i, j) > 0)
            {
                if(i.y >= pole.y)
                    return 1;
                else
                {
                    if(j.y < pole.y)
                        return 1;
                    else
                        return 0;
                }
            }
            else
            {
                if(i.y < pole.y)
                    return 0;
                else
                {
                    if(j.y >= pole.y)
                        return 0;
                    else
                        return 1;
                }
            }
        }
}

bool angle_compare(Point2Df  pole, Point2Df  i, Point2Df j)
{
    if(pole == i)
        return 1;
    if(pole == j)
        return 0;
    if(is_left(pole, i , j) == 0)
        {
            if( (i.y > pole.y && j.y > pole.y) || (i.y < pole.y && j.y < pole.y) )
            {
                return (get_length(i, pole) < get_length(j, pole));
            }
            else if(i.y == pole.y && j.y == pole.y)
            {
                if( (i.x > pole.x && j.x > pole.x) || (i.x < pole.x && j.x < pole.y) )
                    return (get_length(i, pole) < get_length(j, pole));
                else
                    return (i.x < j.x);
            }
            else
            {
                return (i.y > j.y);
            }
        }
        else
        {
            if(is_left(pole, i, j) > 0)
            {
                if(i.y >= pole.y)
                    return 1;
                else
                {
                    if(j.y < pole.y)
                        return 1;
                    else
                        return 0;
                }
            }
            else
            {
                if(i.y < pole.y)
                    return 0;
                else
                {
                    if(j.y >= pole.y)
                        return 0;
                    else
                        return 1;
                }
            }
        }
}

int in_polygon(std::vector<Point2D> polygon, Point2D p)
{
    for(int i = 0; i < polygon.size() - 1; i++)
    {
        if(is_left(polygon[i], polygon[i + 1], p) < 0)
            return 0;
    }
    return 1;
}

int in_polygon(std::vector<Point2D> polygon, Point2Df p)
{
    for(int i = 0; i < polygon.size() - 1; i++)
    {
        if(is_left( (Point2Df) polygon[i],(Point2Df) polygon[i + 1], p) < 0.0)
            return 0;
    }
    return 1;
}


//index of vertex, if polygon is ring
int get_index (int vertex, int size)
{
    if(vertex >= 0 && vertex < size)
        return vertex;
    else if (vertex >= size)
        return vertex % size;
    else if(vertex < 0)
        return  size + (vertex % size);
}


//takes sorted points
std::vector<Point2D> graham_scan(std::vector<Point2D> points)
{
    std::vector<Point2D> st;
    if(is_line(points))
    {
        st.push_back(points[0]);
        st.push_back(points[points.size() - 1]);
        return st;
    }
    Point2D rightest = points[0];
    int rightest_pos = 0;
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i].x > rightest.x || (points[i].x == rightest.x && points[i].y < rightest.y))
        {
            rightest = points[i];
            rightest_pos = i;
        }
    }

    int cur = 1;
    st.push_back(points[get_index(rightest_pos  - 1, points.size())]);
    st.push_back(points[rightest_pos]);
    while(!(st[1] == st[st.size() - 1]  &&   st.size() > 2))
    {
        long long int left = is_left(st[st.size() - 2], st[st.size() - 1], points[get_index(cur + rightest_pos, points.size())]);
        if( left > 0)
        {
            st.push_back(points[get_index(cur + rightest_pos, points.size())]);
            cur++;
        }
        else
        {
            st.pop_back();
            //cur--;
        }
    }

    st.erase(st.begin());
    st.pop_back();
    return st;


}

std::vector<Point2D> graham_scan(std::vector<Point2D> points, Point2D pole)
{
    std::vector<Point2D> st;

    points.push_back(pole);
    if(is_line(points))
    {
        st.push_back(points[points.size() - 1]);
        st.push_back(points[points.size() - 2]);
        return st;
    }
    points.pop_back();


    st.push_back(points[points.size() - 1]);
    st.push_back(pole);

    for(int i = 0; i < points.size(); i++)
    {
        long long int left = is_left(st[st.size() - 2], st[st.size() - 1], points[i] );
        if( left > 0)
        {
            if(!(points[i] == st[0]) && !(points[i] == st[1]))
            st.push_back(points[i]);
        }
        else
        {
            st.pop_back();
            i--;
        }
    }
    //test of 3 last points on one line
    if(is_left(st[st.size() - 2], st[st.size() - 1], points[points.size() - 1]) == 0)
    {
        st.pop_back();
    }



    return st;

}


//returns convex hull of the algo's smallest sets
std::vector<Point2D> get_hull(std::vector<Point2D> points)
{
    int pole_pos = get_pole(points);
    Point2D pole = points[pole_pos];
    points.erase(points.begin() + pole_pos);

    sort_class sorter(pole);
    std::sort(points.begin(), points.end(), sorter);

    std::vector<Point2D> hull = graham_scan(points, pole);

    return hull;

}

std::vector<Point2D> get_hull_sorted(std::vector<Point2D> sorted_points, Point2D pole)
{

    std::vector<Point2D> hull = graham_scan(sorted_points, pole);

    return hull;

}

//return point in poly
Point2Df centroid(Point2D p1, Point2D p2, Point2D p3)
{
    Point2Df p;
    p.x = (p1.x + p2.x + p3.x);
    p.x /= 3.0;
    p.y = (p1.y + p2.y + p3.y);
    p.y /= 3.0;
    return p;
}


std::vector<Point2D> remove_equals(std::vector<Point2D> points)
{
    std::set<Point2D> set;
    for(int i = 0; i < points.size(); i++)
    {
        set.insert(points[i]);
    }
    std::vector<Point2D> res;
    std::set<Point2D>::iterator it;
    for(it = set.begin(); it != set.end(); ++it)
    {
        res.push_back(*it);
    }
    return res;
}


//min in sum[0]
//fast merging of 2 sorted polygons or chains
std::vector<Point2D> merge_polygons(std::vector<Point2D> set1, std::vector<Point2D> set2, Point2Df pole)
{

        int min1 = 0;
        int min2 = 0;
        for(int i = 0; i < set1.size(); i++)
        {
            if(angle_compare(pole,(Point2Df) set1[i], (Point2Df)set1[min1]))
                min1 = i;
        }
        for(int i = 0; i < set2.size(); i++)
        {
            if(angle_compare(pole,(Point2Df) set2[i],(Point2Df) set2[min2]))
                min2 = i;
        }

        std::vector<Point2D> sset1;
        sset1.assign(set1.begin() + min1, set1.end() );
        for(int i = 0; i < min1; i++)
        {
            sset1.push_back(set1[i]);
        }
        std::vector<Point2D> sset2;
        sset2.assign(set2.begin() + min2, set2.end());
        for(int i = 0; i < min2; i++)
        {
            sset2.push_back(set2[i]);
        }

        std::vector<Point2D> sum;
        int last_1;
        int last_2;
        for(int i = 0, j = 0; i < sset1.size() && j < sset2.size();)
        {
            if(angle_compare(pole, (Point2Df)sset1[i], (Point2Df)sset2[j]))
            {
                sum.push_back(sset1[i++]);
            }
            else
            {
                sum.push_back(sset2[j++]);
            }

            last_1 = i;
            last_2 = j;

        }

        if(last_1 != sset1.size())
        {
            for(int i = last_1; i < sset1.size(); i++)
            {
                sum.push_back(sset1[i]);
            }

        }
        else if(last_2 != sset2.size())
        {
            for(int i = last_2; i < sset2.size(); i++)
            {
                sum.push_back(sset2[i]);
            }
        }

        return sum;

}

//deleting not sorted useless points
std::vector<Point2D> delete_chain(std::vector<Point2D> points, Point2Df pole)
{

    //find most right and most left;
    int left = 0;
    int right = 0;
    double enext;
    points.push_back(points[0]);
    double eprev = is_left((Point2Df)points[0],(Point2Df) points[1], pole);

    for(int i = 1; i < points.size() - 1; i++)
    {
        enext = is_left((Point2Df)points[i], (Point2Df)points[i + 1], pole);
        if ((eprev <= 0.0) && (enext > 0.0))
        {
            if (is_left(pole, (Point2Df)points[i], (Point2Df)points[right]) >= 0.0)
                right = i;
        }
        else if ((eprev > 0) && (enext <= 0))
        {
            if (is_left(pole, (Point2Df)points[i], (Point2Df)points[left]) <= 0.0)
                left = i;
        }
        eprev = enext;
        if(i == points.size() - 1)
            break;
    }
    points.pop_back();
    //angle_compare_180
    std::vector<Point2D> sset;


    if (right < left)
    {
        sset.assign(points.begin() + right, points.begin() + left + 1);
        return sset;
    }
    else
    {
        points.erase(points.begin() + left + 1, points.begin() + right);
        return points;

    }

}


//merging of 2 convex hulls
std::vector<Point2D> merge(std::vector<Point2D> set1, std::vector<Point2D> set2)
{

    Point2Df p;
    std::vector<Point2D> sum;
    int is_line1 = is_line(set1);
    int is_line2 = is_line(set2);

    if(!is_line1)
    {
        for(int i = 0; i < set1.size() - 2; i++)
        {
            if(is_left(set1[i], set1[i + 1], set1[i + 2]) != 0)
            {
                p = centroid(set1[i], set1[i + 1], set1[i + 2]);
                break;
            }
        }
    }
    else if(!is_line2)
    {
        for(int i = 0; i < set2.size() - 2; i++)
        {
            if(is_left(set2[i], set2[i + 1], set2[i + 2]) != 0)
            {
                p = centroid(set2[i], set2[i + 1], set2[i + 2]);
                break;
            }
        }
    }

    if(!is_line1 && !is_line2)// 2 polygons
    {
        if(in_polygon(set2, p) != 0)
        {
            sum = merge_polygons(set1, set2, p);
            return graham_scan(sum);

        }
        else
        {
            std::vector<Point2D> clean_set2;

            clean_set2 = delete_chain(set2, p);
            sum = merge_polygons(set1, clean_set2, p);

            return graham_scan(sum);
        }
    }
    else if (!is_line1 && is_line2)//polygon with centroid p and line
    {

        std::vector<Point2D> clean_set2;
       /*
        clean_set2 = delete_chain(set2, p);
        sum = merge_polygons(set1, clean_set2, p);
        */


        if(angle_compare(p, (Point2Df)set2[0], (Point2Df)set2[set2.size() - 1]))
        {
            clean_set2.push_back(set2[0]);
            clean_set2.push_back(set2[set2.size() - 1]);
        }
        else
        {
            clean_set2.push_back(set2[set2.size() - 1]);
            clean_set2.push_back(set2[0]);
        }

        sum = merge_polygons(set1, clean_set2, p);

        return graham_scan(sum);
    }
    else if(is_line1 && !is_line2)
    {
        std::vector<Point2D> clean_set1;
    /*
        clean_set1 = delete_chain(set1, p);
        sum = merge_polygons(clean_set1, set2, p);
    */
        if(angle_compare(p, (Point2Df)set1[0], (Point2Df)set1[set1.size() - 1]))
        {
            clean_set1.push_back(set1[0]);
            clean_set1.push_back(set1[set1.size() - 1]);
        }
        else
        {
            clean_set1.push_back(set1[set1.size() - 1]);
            clean_set1.push_back(set1[0]);
        }

        sum = merge_polygons(clean_set1, set2, p);
        return graham_scan(sum);

    }
    else // if(is_line1 && is_line2)
    {
        std::vector<Point2D> clean_set1;
        clean_set1.push_back(set1[0]);
        clean_set1.push_back(set1[set1.size() - 1]);
        clean_set1.push_back(set2[0]);
        clean_set1.push_back(set2[set2.size() - 1]);
        return get_hull(clean_set1);
    }
}

std::vector<Point2D> merge_hull(std::vector<Point2D> set)
{

    if(set.size() < 2)
        return set;
    if (set.size() <= SIZE)
    {
        return get_hull(set);
    }


    std::vector<Point2D> set1;
    set1.assign(set.begin(), set.begin() + set.size() / 2);
    std::vector<Point2D> set2;
    set2.assign(set.begin() + set.size() / 2 , set.end());

    std::vector<Point2D> hull1 = merge_hull(set1);
    std::vector<Point2D> hull2 = merge_hull(set2);

    return merge(hull1, hull2);



}


