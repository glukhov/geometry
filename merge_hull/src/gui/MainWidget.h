#ifndef MAINWIDGET_H
#define	MAINWIDGET_H

#include <string>
#include <iostream>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include "src/algo/PolygonInputParser.h"
#include "src/gui/Drawer.h"
#include "src/objects/Graph.h"
#include "src/algo/merge_hull.h"
#include "src/algo/validator.h"

class MainWidget : public QWidget {
    Q_OBJECT
    
protected:
    QTabWidget tabs;
    QWidget controlWidget;

    QGridLayout mainLay;
    QGridLayout controlWidgetLay;

    QPushButton clearButton;
    QPushButton exitButton;
    QPushButton exportButton;
    QPushButton importFromFileButton;
    QPushButton processButton;
    QPushButton processWithTestButton;
    QPushButton randomPicButton;
    QPushButton randomNoPicButton;

    QLineEdit fileNameExport;
    QLineEdit fileNameInput;

    Drawer visualizer;

    Graph<Point2D> poly;

public:
    MainWidget();
    
public slots:
    void addPoint (Point2D);
    void clickedClearButton();
    void clickedExitButton();
    void clickedExportButton();
    void clickedImportFromFileButton();
    void clickedProcessButton();
    void clickedProcessWithTestButton();
    void clickedRandomPicButton();
    void clickedRandomNoPicButton();
    void removePoint (unsigned int);

signals:
    void performExitButtonAction();
};

#endif	/* MAINWIDGET_H */
