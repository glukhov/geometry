#ifndef MERGE_HULL_H
#define MERGE_HULL_H
#include <iostream>
#include <algorithm>

#include <cstdio>
#include <math.h>
#include <vector>
#include "src/objects/Point2D.h"

double get_length(Point2D p1, Point2D p2);
double get_angle(Point2D p1, Point2D p2);
int is_left(Point2D p1, Point2D p2, Point2D p3);
bool angle_compare(Point2D  pole,Point2D  i, Point2D  j);
class sort_class;
int get_index (int vertex, int size);
std::vector<Point2D> my_graham_scan(std::vector<Point2D> points);
std::vector<Point2D> graham_scan(std::vector<Point2D> points, Point2D pole);
int get_pole(std::vector<Point2D> points);
std::vector<Point2D> get_hull(std::vector<Point2D> points);
Point2D centroid(Point2D p1, Point2D p2, Point2D p3);
int in_polygon(std::vector<Point2D> polygon, Point2D p);
std::vector<Point2D> merge_poligons(std::vector<Point2D> set1, std::vector<Point2D> set2, Point2D pole);
std::vector<Point2D> delete_chain(std::vector<Point2D> points, Point2D pole);
std::vector<Point2D> merge(std::vector<Point2D> set1, std::vector<Point2D> set2);
std::vector<Point2D> merge_hull(std::vector<Point2D> set);

#endif // MERGE_HULL_H