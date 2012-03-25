#ifndef MERGE_HULL_H
#define MERGE_HULL_H
#include <iostream>
#include <algorithm>
#include <set>
#include <cstdio>
#include <math.h>
#include <vector>
#include "src/objects/Point2D.h"
#include "src/objects/Point2Df.h"



bool is_line(std::vector<Point2D> points);

int get_pole(std::vector<Point2D> points);
double get_length(Point2D p1, Point2D p2);
double get_angle(Point2D p1, Point2D p2);
long long int is_left(Point2D p1, Point2D p2, Point2D p3);
double is_left(Point2Df p1, Point2Df p2, Point2Df p3);
bool angle_compare(Point2D  pole,Point2D  i, Point2D  j);
bool angle_compare(Point2Df  pole, Point2Df  i, Point2Df  j);
int in_polygon(std::vector<Point2D> polygon, Point2D p);
int in_polygon(std::vector<Point2D> polygon, Point2Df p);

int get_index (int vertex, int size);
std::vector<Point2D> graham_scan(std::vector<Point2D> points);
std::vector<Point2D> graham_scan(std::vector<Point2D> points, Point2D pole);

std::vector<Point2D> get_hull(std::vector<Point2D> points);
std::vector<Point2D> get_hull_sorted(std::vector<Point2D> sorted_points, Point2D pole);
Point2Df centroid(Point2D p1, Point2D p2, Point2D p3);

std::vector<Point2D> remove_equals(std::vector<Point2D> points);

std::vector<Point2D> merge_hull(std::vector<Point2D> set);
std::vector<Point2D> merge(std::vector<Point2D> set1, std::vector<Point2D> set2);
std::vector<Point2D> merge_polygons(std::vector<Point2D> set1, std::vector<Point2D> set2, Point2D pole);
std::vector<Point2D> delete_chain(std::vector<Point2D> points, Point2D pole);

class sort_class;

#endif // MERGE_HULL_H

