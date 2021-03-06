#include "MainWidget.h"



MainWidget::MainWidget()
    :   clearButton ("Clear"),
        exitButton ("Exit"),
        exportButton ("Export points to:"),
        importFromFileButton ("Import points from file:"),
        processButton ("Convex Hull"),
        processWithTestButton ("Convex Hull with Validator"),
        randomPicButton ("Random with picture"),
        randomNoPicButton ("Random test, no picture"),
        fileNameExport ("output.txt"),
        fileNameInput ("test.txt"),
        visualizer (this) {

    tabs.addTab(&visualizer, "Visualizer");

    mainLay.addWidget(&tabs, 0, 0);
    mainLay.addWidget(&controlWidget, 0, 1);
    this->setLayout(&mainLay);

    controlWidgetLay.addWidget(&importFromFileButton, 0, 0);
    controlWidgetLay.addWidget(&fileNameInput, 1, 0);
    controlWidgetLay.addWidget(&processButton, 2, 0);
    controlWidgetLay.addWidget(&processWithTestButton, 3, 0);
    controlWidgetLay.addWidget(&randomPicButton, 4, 0);
    controlWidgetLay.addWidget(&randomNoPicButton, 5, 0);
    controlWidgetLay.addWidget(&clearButton, 6, 0);
    controlWidgetLay.addWidget(&exportButton, 7, 0);
    controlWidgetLay.addWidget(&fileNameExport, 8, 0);
    controlWidgetLay.addWidget(&exitButton, 9, 0);
    controlWidget.setLayout(&controlWidgetLay);
    controlWidget.setMaximumWidth(200);

    visualizer.setMinimumSize(600, 400);

    QObject::connect(&clearButton, SIGNAL(clicked()), this, SLOT(clickedClearButton()));
    QObject::connect(&exitButton, SIGNAL(clicked()), this, SLOT(clickedExitButton()));
    QObject::connect(&exportButton, SIGNAL(clicked()), this, SLOT(clickedExportButton()));
    QObject::connect(&processButton, SIGNAL(clicked()), this, SLOT(clickedProcessButton()));
    QObject::connect(&processWithTestButton, SIGNAL(clicked()), this, SLOT(clickedProcessWithTestButton()));
    QObject::connect(&randomPicButton, SIGNAL(clicked()), this, SLOT(clickedRandomPicButton()));
    QObject::connect(&randomNoPicButton, SIGNAL(clicked()), this, SLOT(clickedRandomNoPicButton()));
    QObject::connect(&importFromFileButton, SIGNAL(clicked()), this, SLOT(clickedImportFromFileButton()));
    QObject::connect(&visualizer, SIGNAL(pointAdded(Point2D)), this, SLOT(addPoint(Point2D)));
    QObject::connect(&visualizer, SIGNAL(pointRemoved(unsigned int)), this, SLOT(removePoint(unsigned int)));
}


void MainWidget::addPoint(Point2D arg) {
    poly.addVertex(arg);
//    poly.connectVertices();
    visualizer.replacePoly(poly);
    visualizer.update();
}


void MainWidget::clickedClearButton() {
    poly.clear();
    visualizer.replacePoly(poly);
}


void MainWidget::clickedExitButton() {
    emit performExitButtonAction();
}


void MainWidget::clickedExportButton() {
    poly.dumpVertices(fileNameExport.text().toStdString());
}


void MainWidget::clickedImportFromFileButton() {
    poly = Graph <Point2D> (PolygonInputParser::parseFile(fileNameInput.text().toStdString()));

    visualizer.replacePoly(poly);
    visualizer.update();
        poly.connectVertices();
}


void MainWidget::clickedProcessButton() {

    Graph <Point2D> convex_hull;
    std::vector<Point2D> hull = merge_hull (remove_equals(poly.vertices));

    convex_hull.vertices = hull;
    convex_hull.connectVertices();

    visualizer.replacePoly(convex_hull);
    poly.edges.clear();
   // poly.connectVertices();
    visualizer.update();

    for (unsigned int i = 0; i < hull.size(); ++i)
    {
        std::cout << hull[i].getX()<< ' ' << hull[i].getY() << std::endl;
    }
    std::cout << std::endl;
}

void MainWidget::clickedProcessWithTestButton() {

    Validator val;
    val.points = poly.vertices;
    val.get_hull();
    val.test();

    for (int j = 0; j < val.convex_hull.size(); j++)
    {
        std::cout << val.convex_hull[j].getX()<< ' ' << val.convex_hull[j].getY() << std::endl;
    }
    std::cout << std::endl;

    Graph <Point2D> convex_hull;
    convex_hull.vertices = val.convex_hull;
    convex_hull.connectVertices();

    visualizer.replacePoly(convex_hull);
    poly.edges.clear();
    visualizer.update();


}

void MainWidget::clickedRandomPicButton() {


    Validator val;

    //std::vector<Point2D> hull = merge_hull (remove_equals(val.points));
    val.generate();
    val.get_hull();
    val.test();
    for (unsigned int i = 0; i < val.convex_hull.size(); ++i)
    {
        std::cout << val.convex_hull[i].getX()<< ' ' << val.convex_hull[i].getY() << std::endl;
    }
    std::cout << "picture is being drawn..." << std::endl << std::endl;
    Graph <Point2D> convex_hull;
    convex_hull.vertices = val.convex_hull;
    convex_hull.connectVertices();
    convex_hull.vertices.insert(convex_hull.vertices.end(), val.points.begin(), val.points.end());

    visualizer.replacePoly(convex_hull);
    visualizer.update();

}

void MainWidget::clickedRandomNoPicButton() {

    Validator val;
    val.generate();
    val.get_hull();
    val.test();
    for (unsigned int i = 0; i < val.convex_hull.size(); ++i)
    {
        std::cout << val.convex_hull[i].getX()<< ' ' << val.convex_hull[i].getY() << std::endl;
    }
    std::cout << std::endl;
}


void MainWidget::removePoint(unsigned int index) {
    poly.removePoint(index);
    poly.edges.clear();
    visualizer.replacePoly(poly);

}
