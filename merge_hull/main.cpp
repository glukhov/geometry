#include <iostream>
#include <algorithm>

#include <cstdio>
#include <math.h>
#include <vector>

#define SIZE 5



class point_type
{
public:
	friend bool operator ==(const point_type& a, const point_type& b);
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


bool operator ==(const point_type& a, const point_type& b)
{
	if(a.x == b.x && a.y == b.y)
		return 1;
	else
		return 0;
}

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
bool angle_compare_180(point_type  pole,point_type  i, point_type  j)
{
	if(is_left(pole, i , j) == 0)
	{
		return (get_length(i, pole) < get_length(j, pole));
	}
	else
	{
		if(is_left(pole, i, j) > 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
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



int prev (int vertex, int size)
{
	if(vertex > 0 && vertex <= size)
		return vertex - 1;
	else if(vertex > size)
		return vertex%size - 1;
	else if(vertex <= 0)
		return size + vertex;
}
int get_index (int vertex, int size)
{
	if(vertex >= 0 && vertex < size)
		return vertex;
	else if (vertex >= size)
		return vertex % size;
	else if(vertex < 0)
		return  size + (vertex % size);
}
std::vector<point_type> my_graham_scan(std::vector<point_type> points)
{

	std::vector<int> st;
	std::vector<point_type> result;
//    st.push_back(points[points.size() - 1]);


//	points.push_back(points[0]);



//NEED FIX!!!
/*
	int prev;
	int prevprev;
	int next;
	int v = 0;
	int w = get_index(v - 1, points.size());
	bool f = false;
	
	
	while(get_index(v + 1, points.size()) != 0 || f == false)
	{
		if(get_index(v + 1, points.size()) == w)
			f = true;
		if (is_left(points[get_index(v, points.size())], points[get_index(v + 1, points.size())], points[get_index(v + 2, points.size())]))
			v++;
		else
		{
			deleted[v] = true;
			v = get_index(v + 1, points.size());
		}
	}
	*/

	int cur = 2;
	int prev;
	int prevprev;
	st.push_back(0);
    st.push_back(1);
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
/*    for(int i = 1; i < points.size(); i++)
    {
        
		int prev = st.size() - 2;
		int prevprev = st.size() - 1;

		if()
		{
			int left = is_left(points[st[prevprev]], points[st[prev]], points[i]);
			if( left > 0)
			{
				//if(!(points[i] == st[0]) && !(points[i] == st[1]))
					st.push_back(points[i]);
			}
			else
			{
				st.pop_back();
				i--;
			}
		}
    }
*/	
	st.pop_back();
	for(int i = 1; i < st.size(); i++)
	{
		result.push_back(points[st[i]]);
	}
//st.erase(std::unique(st.begin(), st.end()), st.end());

    return result;

}


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
			if(!(points[i] == st[0]) && !(points[i] == st[1]))
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

//	st.erase(std::unique(st.begin(), st.end()), st.end());

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


//min in sum[0]
std::vector<point_type> merge_poligons(std::vector<point_type> set1, std::vector<point_type> set2, point_type pole)
{
//	set1.erase(std::unique(set1.begin(), set1.end()), set1.end());
//	set2.erase(std::unique(set2.begin(), set2.end()), set2.end());
		
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

	    std::vector<point_type> sum;	
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

std::vector<point_type> delete_chain(std::vector<point_type> points, point_type pole)
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
	std::vector<point_type> sset;

	
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
	/*int min = 0;
	for(int i = 0; i < points.size(); i++)
	{
		if(angle_compare(pole, points[i], points[min]))
			min = i;
	}
	
	std::vector<point_type> sset;
    sset.assign(points.begin() + min, points.end());
	for(int i = 0; i < min; i++)
    {
		sset.push_back(points[i]);
	}
	sset.push_back(sset[0]);
	//sset.push_back(sset[1]);

	
	int up = 0;
	int down = 0;
//	int last = angle_compare(pole, sset[0], sset[1]);
	std::vector<int> direction;
//	direction.push_back( angle_compare(pole, sset[sset.size() - 1], sset[0]));

	for(int i = 0; i < sset.size() - 1; i++)
	{
		
		direction.push_back(angle_compare(pole, sset[i], sset[i + 1]));
	}
	int last =  direction[0];
	for(int i = 1; i < direction.size(); i++)
	{
		if(direction[i] != direction[i - 1])
		{
			if(direction[i-1] == 0)
			{
				up = i;
			}
			else
			{
				down = i;
			}
		}
	}

	down++;
	down %= points.size();
	up++;
	up %= points.size();
	sset.pop_back();
//	sset.pop_back();
	for(int i = up + 1 ; i < down; i++)
	{
		sset.erase(sset.begin() + up + 1);
	}
	//std::vector<point_type> res;
	//res.assign(sset.begin() + down, sset.begin() + up + 1);
	//sset.erase(sset.begin() + down, sset.begin() + up);
	return sset;*/

}


std::vector<point_type> merge(std::vector<point_type> set1, std::vector<point_type> set2)
{
	
	point_type p = centroid(set1[0], set1[set1.size() - 2], set1[set1.size() - 1]);
    std::vector<point_type> sum;

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
		sum = merge_poligons(set1, set2, p);
		return my_graham_scan(sum);
		
	}
	else
    {
	    std::vector<point_type> clean_set2;
		
		clean_set2 = delete_chain(set2, p);
		sum = merge_poligons(set1, clean_set2, p);

		return my_graham_scan(sum);
    }
  
	//return graham_scan(sum, pole);
	
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
    std::vector<point_type> c;
    std::vector<point_type> d;
    //point_type pole (-2, 3);
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
 /*
	for(int i = 0; i < 5; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        a.push_back(point_type(x, y));
    }
	for(int i = 0; i < 6; i++)
    {
        int x; int y;
        std::cin >> x >> y;
        b.push_back(point_type(x, y));
    }
	*/
	//d.erase(std::unique(d.begin(), d.end()), d.end());
	
    d = merge_hull(a);
//	int t = is_left(a[0], a[1], a[2]);

  //  point_type pole (0, 0);
//	sort_class sorter(pole);
 //   std::sort(a.begin(), a.end(), sorter);
	
	//std::cout << t;

	//d = delete_chain(a, pole);
	//c = merge_poligons(a, b, pole);

//	d = my_graham_scan(a);

	
	for(int i = 0; i < d.size(); i++)
    {
        std::cout << d[i].x << "  " << d[i].y << std::endl;
    }
	//*/
    return 0;
}


