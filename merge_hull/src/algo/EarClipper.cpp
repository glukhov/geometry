#include "EarClipper.h"

Graph <Point2D> EarClipper::triangulate(const Graph <Point2D> &arg, std::vector <Triangle2D> *triangles) {
    Graph <Point2D> result (arg);
    std::vector<bool> cutOff (arg.getVertexCount(), false);
    int vertexRemaining = arg.getVertexCount();

    unsigned int a = 0; //first of three vertexes, which create a corner
    while (vertexRemaining > 3) {
        bool isEar = true;
        a = a % arg.getVertexCount();
        unsigned int b = 0;
        unsigned int c = 0;
        unsigned int currentVertex = a + 1;

        while (true) { //b will be next unused vertex
            currentVertex = currentVertex % arg.getVertexCount(); //cycle vertexes
            if (!cutOff[currentVertex]) {
                b = currentVertex++;
                break;
            }
            ++currentVertex;
        }

        while (true) { //c will be next unused vertex
            currentVertex = currentVertex % arg.getVertexCount();
            if (!cutOff[currentVertex]) {
                c = currentVertex++;
                break;
            }
            ++currentVertex;
        }

        Vector2D va(arg.getVertex(a), arg.getVertex(b));
        Vector2D vb(arg.getVertex(b), arg.getVertex(c));

        if (va.orientation(vb) > 0) {
            ++a;
            a = a % arg.getVertexCount(); //cycle vertexes
            while (cutOff[a]) {
                ++a;
                a = a % arg.getVertexCount(); //cycle vertexes
            }
            continue;
        }

        for (unsigned int i = 0; i < arg.getVertexCount(); ++i) {
            if (i == a || i == b || i == c || cutOff[i]) {
                continue;
            }

            Vector2D vai(arg.getVertex(a), arg.getVertex(i));
            Vector2D vic(arg.getVertex(i), arg.getVertex(c));
            Vector2D vib(arg.getVertex(i), arg.getVertex(b));
            Vector2D vci(arg.getVertex(c), arg.getVertex(i));


            if (vai.orientation(vic) < 0 && vai.orientation(vib) > 0 && vci.orientation(vib) < 0) {
                isEar = false;
                std::cout << a << ' ' << b << ' ' << c << ' ' << i << " - not ear\n";
                break;
            }
        }

        if (isEar) {
            --vertexRemaining;
            cutOff[b] = true;
            result.addEdge(a, c);
            if (triangles != 0) {
                triangles->push_back(Triangle2D(arg.getVertex(a), arg.getVertex(b), arg.getVertex(c)));
            }
            std::cout << a << ' ' << c << " - edge added\n";
        } else {
            ++a;
            a = a % arg.getVertexCount();
            while (cutOff[a]) {
                ++a;
                a = a % arg.getVertexCount(); //cycle vertexes
            }
        }
    }

    return result;
}
