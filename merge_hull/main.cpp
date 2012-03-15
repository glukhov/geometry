#include <iostream>
#include <algorithm>

#include <cstdio>
#include <math.h>
#include <vector>

#define SIZE 5



class point_type
{
public:
    int x;
    int y;
    point_type()
    {

    }
    point_type(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

};

//OXY, return 1 if X < Y
int triangle_area_2 (point_type p1, point_type p2, point_type p3) {
	int s = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	if(s > 0)
		return 1;
	else if(s < 0)
		return -1;
	else
		return 0;
}

double get_length(point_type p1, point_type p2)
{
    return sqrt(double((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

double get_angle(point_type p1, point_type p2)
{
    
	return (p1.x - p2.x)/get_length(p1, p2);
    //return (p2.x - p1.x) / (p2.y - p1.y);
}


int is_left(point_type p1, point_type p2, point_type p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

bool angle_compare(point_type  pole,point_type  i, point_type  j)
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
    point_type pole;
    sort_class(point_type p)
    {
        this->pole = p;
    }

    bool operator() (point_type i, point_type j)
	{
      /*  if(get_angle(i, pole) == get_angle(j, pole))
            return (get_length(i, pole) < get_length(j, pole)) ;
        else
            return (get_angle(i, pole) >  get_angle(j, pole));
			
			*/
	/*	if(triangle_area_2(pole, i, j) == 0)
            return (get_length(i, pole) < get_length(j, pole)) ;
        else
            return (triangle_area_2(pole, i ,j)  > 0);
			*/
		
		return angle_compare(pole, i, j);
    }
};






std::vector<point_type> graham_scan(std::vector<point_type> points, point_type pole)
{
    std::vector<point_type> st;

    st.push_back(points[points.size() - 1]);
    st.push_back(pole);

    for(int i = 0; i < points.size() - 1; i++)
    {
        int left = is_left(st[st.size() - 2], st[st.size() - 1], points[i] );
		if( left > 0)
        {
            st.push_back(points[i]);
        }
      /*else if(left == 0)
        {
			st.pop_back();
            st.push_back(points[i]);

		}*/
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
int get_pole(std::vector<point_type> points)
{
    point_type pole = points[0];
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
std::vector<point_type> get_hull_sorted(std::vector<point_type> sorted_points, point_type pole)
{

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

int in_polygon(std::vector<point_type> polygon, point_type p)
{
    for(int i = 0; i < polygon.size() - 1; i++)
    {
        if(is_left(polygon[i], polygon[i + 1], p) < 0)
            return 0;
    }
    return 1;
}

std::vector<point_type> merge_poligons(std::vector<point_type> set1, std::vector<point_type> set2, point_type pole)
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

}

std::vector<point_type> merge(std::vector<point_type> set1, std::vector<point_type> set2)
{
    point_type pole;
	point_type p = centroid(set1[0], set1[1], set1[2]);
    std::vector<point_type> sum;
	sum.assign(set1.begin(), set1.end());
    for(int i = 0; i < set2.size(); i++)
	{
		sum.push_back(set2[i]);
	}

    if(in_polygon(set2, p) != 0)
    {
        /*
        int pole_pos;
        int in_set = 0;
        int pole1 = get_pole(set1);
        int pole2 = get_pole(set2);
        if(set1[pole1].y < set2[pole2].y || (set1[pole1].y == set2[pole2].y && set1[pole1].x < set2[pole2].x))
        {
            pole_pos = pole1;
            in_set = 1;
            pole = set1[pole_pos];
            set1.erase(set1.begin() + pole_pos);
        }
        else
        {
            pole_pos = pole2;
            in_set = 2;
            pole = set2[pole_pos];
            set2.erase(set2.begin() + pole_pos);
        }


        std::vector<double> angles1;
        std::vector<double> angles2;
        for(int i = 0; i < set1.size(); i++)
        {
            angles1.push_back(get_angle(set1[i], pole));
        }
        for(int i = 0; i < set2.size(); i++)
        {
            angles2.push_back(get_angle(set2[i], pole));
        }

        int min1 = 0;
        int min2 = 0;
        for(int i = 0; i < set1.size(); i++)
        {
            if(angles1[i] > angles1[min1])
                min1 = i;
        }
        for(int i = 0; i < set2.size(); i++)
        {
            if(angles2[i] > angles2[min2])
                min2 = i;
        }

        std::vector<point_type> sset1;
        sset1.assign(set1.begin() + min1, set1.end());
        for(int i = 0; i < min1; i++)
        {
            sset1.push_back(set1[i]);
        }
        std::vector<point_type> sset2;
        sset2.assign(set2.begin() + min2, set2.end());
        for(int i = 0; i < min2; i++)
        {
            sset2.push_back(set2[i]);
        }


        for(int i = 0, j = 0; i < sset1.size() || j < sset2.size();)
        {
            if(angles1[i] == angles2[j])
            {
                if(get_length(sset1[i], pole) < get_length(sset2[j], pole))
                {
                    sum.push_back(sset1[i++]);
                }
                else
                {
                    sum.push_back(sset2[j++]);
                }
            }
            else
            {
                if(angles1[i] > angles2[j])
                {
                    sum.push_back(sset1[i++]);
                }
                else
                {
                    sum.push_back(sset2[j++]);
                }
            }
        }
		*/

   }
    else
    {
           return get_hull(sum);
    }
  
	return graham_scan(sum, pole);
	
	//return get_hull(sum);
}



std::vector<point_type> merge_hull(std::vector<point_type> set)
{

    if (set.size() <= SIZE)
    {
        return get_hull(set);
    }


    std::vector<point_type> set1;
    set1.assign(set.begin(), set.begin() + set.size() / 2);
    std::vector<point_type> set2;
    set2.assign(set.begin() + set.size() / 2 , set.end());

    std::vector<point_type> hull1 = merge_hull(set1);
    std::vector<point_type> hull2 = merge_hull(set2);

    return merge(hull1, hull2);



}




int main()
{
    std::vector<point_type> a;
    std::vector<point_type> b;
    int n;


	freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        a.push_back(point_type(x, y));
    }
    b = get_hull(a);
//	int t = is_left(a[0], a[1], a[2]);
/*
    point_type pole (0, 0);
	sort_class sorter(pole);
    std::sort(a.begin(), a.end(), sorter);
*/	
	//std::cout << t;
    for(int i = 0; i < b.size(); i++)
    {
        std::cout << b[i].x << "  " << b[i].y << std::endl;
    }

    return 0;
}


