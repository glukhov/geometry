#include "Drawer.h"

Drawer::Drawer(QWidget *parent) :
    QWidget (parent) {
}


Drawer::Drawer(QWidget *parent, const Graph <Point2D> & poly) :
    QWidget (parent),
    poly (poly) {
}


void Drawer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        int ptXCoord = (event->x() - offsetx) / scale;
        int ptYCoord = (event->y() - offsety) / scale;

        emit pointAdded(Point2D (ptXCoord, ptYCoord));
    } else if (event->button() == Qt::RightButton) {
        int ptXCoord = (event->x() - offsetx) / scale;
        int ptYCoord = (event->y() - offsety) / scale;

        for (unsigned int i = 0; i < poly.getVertexCount(); ++i) {
            Point2D curr = poly.getVertex(i);
            if (abs(curr.getX() - ptXCoord) < (3 / scale) && abs(curr.getY() - ptYCoord) < (3 / scale)) {
                emit pointRemoved(i);
                break;
            }
        }
    }
}


void Drawer::paintEvent(QPaintEvent *event) {
    const int radius = 6;

    offsetx = this->width() / 2;
    offsety = this->height() / 2;

    double maxx = -1;
    double maxy = -1;
    scale = 1.0;

    if (poly.getVertexCount() > 0) {
        for (unsigned int i = 0; i < poly.getVertexCount(); ++i) {
            maxx = std::max ((int)maxx, abs(poly.getVertex(i).getX()));
            maxy = std::max ((int)maxy, abs(poly.getVertex(i).getY()));
        }

        scale = std::min (std::min (offsetx/maxx, offsety/maxy) / 1.1, 1.0);
    }

    QPainter painter0(this);

    painter0.setPen(QPen(Qt::transparent, 1, Qt::SolidLine));
    painter0.drawLine(0, 0, this->width(), this->height());

    painter0.setRenderHint(QPainter::Antialiasing, true);
    painter0.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter0.setFont(QFont("Arial", 8, QFont::Bold));

    //Draw (0, 0)
    painter0.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter0.drawEllipse (offsetx - scale * radius, offsety - scale * radius, sqrt(scale) * radius * 2, sqrt(scale) * radius * 2);

    //Draw points
    painter0.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    for (unsigned int i = 0; i < poly.getVertexCount(); ++i) {
        painter0.drawEllipse (offsetx + scale * (poly.getVertex(i).getX() - radius/2),
                              offsety + scale * (poly.getVertex(i).getY() - radius/2),
                              sqrt(scale) * radius, sqrt(scale) * radius);

        //print vertex numbers
        std::stringstream ss;
        ss << i;
        painter0.setPen(QPen(Qt::blue, 1, Qt::SolidLine));
        painter0.drawText((int)(offsetx + scale * (poly.getVertex(i).getX())),
                          (int)(offsety + scale * (poly.getVertex(i).getY() + radius)), ss.str().c_str());
        painter0.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    }

    //Draw lines
    painter0.setBrush(QBrush(Qt::transparent, Qt::SolidPattern));
    for (unsigned int i = 0; i < poly.getEdgeCount(); ++i) {
        int xVertex = poly.getEdge(i).first;
        int yVertex = poly.getEdge(i).second;

        painter0.drawLine (offsetx + scale * (poly.getVertex(xVertex).getX()), offsety + scale * (poly.getVertex(xVertex).getY()),
                           offsetx + scale * (poly.getVertex(yVertex).getX()), offsety + scale * (poly.getVertex(yVertex).getY()));
    }

    if (event) {} //this magic code removes warning
}


void Drawer::replacePoly(const Graph <Point2D> &poly) {
    this->poly = poly;
    this->repaint();
}
