#include <QApplication>
#include <QtGui>
#include "src/gui/MainWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.show();
    QObject::connect (&mainWindow, SIGNAL(performExitButtonAction()), &app, SLOT(quit()));

    return app.exec();
}
