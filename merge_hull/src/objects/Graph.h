#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

template <class Point>
class Graph {
public:
    Graph() {}


    Graph(std::vector <Point> data) :
        vertices (data) {
    }


    Graph (std::vector <Point> vertices, std::vector <std::pair<int, int> > edges) :
        vertices (vertices),
        edges (edges) {
    }


    Graph (const Graph<Point> &arg) :
        vertices (arg.vertices),
        edges (arg.edges) {
    }


    Graph& operator = (const Graph &arg) {
        edges = arg.edges;
        vertices = arg.vertices;

        return *this;
    }


    void addEdge (unsigned int a, unsigned int b) {
        edges.push_back(std::pair<int, int>(a, b));
    }


    void addVertex (Point pt) {
        vertices.push_back(pt);
    }


    void clear() {
        edges.clear();
        vertices.clear();
    }


    //become a polygon
    void connectVertices() {
        edges.clear();

        for (unsigned int i = 0; i < vertices.size(); ++i) {
            edges.push_back(std::pair<int, int> (i, i + 1));
        }

        if (!edges.empty()) {
            edges.pop_back();
            edges.push_back(std::pair<int, int> (vertices.size() - 1, 0));
        }
    }

    void dumpVertices (std::string fileName) {
        std::ofstream outp (fileName.c_str());
        if (outp.fail()) {
            std::cerr << "can't open output file: " << fileName << std::endl;
            return;
        }

        for (unsigned int i = 0; i < vertices.size(); ++i) {
            outp << vertices[i].getX() << ' ' << vertices[i].getY() << std::endl;
        }

        outp.close();
    }


    Point getVertex (unsigned int i) const {
        assert (i < vertices.size());
        return vertices[i];
    }


    unsigned int getVertexCount () const {
        return vertices.size();
    }


    std::pair <int, int> getEdge (unsigned int i) const {
        assert (i < edges.size());
        return edges[i];
    }


    unsigned int getEdgeCount () const {
        return edges.size();
    }


    void removePoint (unsigned int index) {
        if (index < vertices.size()) {
            vertices.erase(vertices.begin() + index, vertices.begin() + index + 1);
            connectVertices();
        }
    }

    std::vector <Point> vertices;
    std::vector <std::pair<int, int> > edges;    //pair contains numbers of two incident vertexes
};

#endif // GRAPH_H
