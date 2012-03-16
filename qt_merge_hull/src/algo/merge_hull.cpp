
#include "src/algo/merge_hull.h"
#define SIZE 5

double get_length(Point2D p1, Point2D p2)
{
    return sqrt(double((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

double get_angle(Point2D p1, Point2D p2)
{

    return (p1.x - p2.x)/get_length(p1, p2);
    //return (p2.x - p1.x) / (p2.y - p1.y);
}

int is_left(Point2D p1, Point2D p2, Point2D p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

bool angle_compare(Point2D  pole,Point2D  i, Point2D  j)
{
    if(is_left(pole, i , j) == 0)
        {
            if( (i.y > pole.y && j.y > pole.y) || (i.y < pole.y && j.y < pole.y) )
            {
                return (get_length(i, pole) < get_length(j, pole));
            }
            else if(i.y = pole.y && j.y == pole.y)
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

int get_index (int vertex, int size)
{
    if(vertex >= 0 && vertex < size)
        return vertex;
    else if (vertex >= size)
        return vertex % size;
    else if(vertex < 0)
        return  size + (vertex % size);
}

std::vector<Point2D> my_graham_scan(std::vector<Point2D> points)
{

    if(points.size() < 3 )
        std::cout << "ololol";
    std::vector<int> st;
    std::vector<Point2D> result;
    int cur = 2;
    int prev;
    int prevprev;
    st.push_back(0);
    st.push_back(1);
  /*
    while(!(st[1] == st[st.size() - 1]  &&   st.size() > 2))
    {
        if(st.size() > 1)
        {
            prev = st.size() - 1;
            prevprev = st.size() - 2;
        }
        else if(st.size() == 1)
        {
            prev = 0;
            prevprev = points.size() - 1;
        }
        else
        {
            prev = get_index(cur - 1, points.size());
            prevprev = get_index(cur - 2, points.size());
        }

        int left = is_left(points[st[prevprev]], points[st[prev]], points[get_index(cur, points.size())]);
        if( left > 0)
        {
            st.push_back(get_index(cur, points.size()));
            cur++;
        }
        else
        {
            st.pop_back();
            //cur--;
        }
    }

    */

    while(1)
        {
            if(st.size() > 2)
                if(st[1] == st[st.size() - 1])
                    break;




            if(st.size() == 1)
            {
                int temp = st[0] ;
                st.pop_back();

                //prev = 0;
                st.push_back(points.size() - 1);
                st.push_back(temp);
            }
            else if(st.size() == 0)
            {
                st.push_back(get_index(cur - 2, points.size()));
                st.push_back(get_index(cur - 1, points.size()));
            }

            prev = st.size() - 1;
            prevprev = st.size() - 2;

            int left = is_left(points[st[prevprev]], points[st[prev]], points[get_index(cur, points.size())]);


            if( left > 0)
            {
                st.push_back(get_index(cur, points.size()));
                cur++;
            }
            else
            {
                st.pop_back();
                //cur--;
            }

        }
    st.pop_back();
    for(int i = 1; i < st.size(); i++)
    {
        result.push_back(points[st[i]]);
    }
//st.erase(std::unique(st.begin(), st.end()), st.end());

    return result;

}

std::vector<Point2D> graham_scan(std::vector<Point2D> points, Point2D pole)
{
    std::vector<Point2D> st;

    if(points.size() < 2 )
        std::cout << "ololol";


    st.push_back(points[points.size() - 1]);
    st.push_back(pole);

    for(int i = 0; i < points.size(); i++)
    {
        int left = is_left(st[st.size() - 2], st[st.size() - 1], points[i] );
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
Point2D centroid(Point2D p1, Point2D p2, Point2D p3)
{
    Point2D p;
    p.x = (p1.x + p2.x + p3.x) / 3;
    p.y = (p1.y + p2.y + p3.y) / 3;
    return p;
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

//min in sum[0]
std::vector<Point2D> merge_poligons(std::vector<Point2D> set1, std::vector<Point2D> set2, Point2D pole)
{

        int min1 = 0;
        int min2 = 0;
        for(int i = 0; i < set1.size(); i++)
        {
            if(angle_compare(pole, set1[i], set1[min1]))
                min1 = i;
        }
        for(int i = 0; i < set2.size(); i++)
        {
            if(angle_compare(pole, set2[i], set2[min2]))
                min2 = i;
        }

        std::vector<Point2D> sset1;
        sset1.assign(set1.begin() + min1, set1.end());
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
            if(angle_compare(pole, sset1[i], sset2[j]))
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

std::vector<Point2D> delete_chain(std::vector<Point2D> points, Point2D pole)
{

    //find most right and most left;
    int left = 0;
    int right = 0;
    int enext;
    points.push_back(points[0]);
    int eprev = is_left(points[0], points[1], pole);

    for(int i = 1; i < points.size() - 1; i++)
    {
        enext = is_left(points[i], points[i + 1], pole);
        if ((eprev <= 0) && (enext > 0))
        {
            if (is_left(pole, points[i], points[right]) >= 0)
                right = i;
        }
        else if ((eprev > 0) && (enext <= 0))
        {
            if (is_left(pole, points[i], points[left]) <= 0)
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

std::vector<Point2D> merge(std::vector<Point2D> set1, std::vector<Point2D> set2)
{

    Point2D p = centroid(set1[0], set1[set1.size() - 2], set1[set1.size() - 1]);
    std::vector<Point2D> sum;

    if(in_polygon(set2, p) != 0)
    {
        sum = merge_poligons(set1, set2, p);
        return my_graham_scan(sum);

    }
    else
    {
        std::vector<Point2D> clean_set2;

        clean_set2 = delete_chain(set2, p);
        sum = merge_poligons(set1, clean_set2, p);

        return my_graham_scan(sum);
    }

}

std::vector<Point2D> merge_hull(std::vector<Point2D> set)
{

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
/*
int main()
{
    std::vector<Point2D> a;
    std::vector<Point2D> b;
    std::vector<Point2D> c;
    std::vector<Point2D> d;
    //Point2D pole (-2, 3);
    int n;


    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        a.push_back(Point2D(x, y));
    }*/
 /*
    for(int i = 0; i < 5; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        a.push_back(Point2D(x, y));
    }
    for(int i = 0; i < 6; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        b.push_back(Point2D(x, y));
    }
    */
    //d.erase(std::unique(d.begin(), d.end()), d.end());

  //  d = merge_hull(a);
//	int t = is_left(a[0], a[1], a[2]);

  //  Point2D pole (0, 0);
//	sort_class sorter(pole);
 //   std::sort(a.begin(), a.end(), sorter);

    //std::cout << t;

    //d = delete_chain(a, pole);
    //c = merge_poligons(a, b, pole);

//	d = my_graham_scan(a);

/*
    for(int i = 0; i < d.size(); i++)
    {
        std::cout << d[i].x << "  " << d[i].y << std::endl;
    }
    //*/
/*    return 0;
}
*/

