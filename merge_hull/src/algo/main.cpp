#include <QApplication>
#include <QtGui>
#include "src/gui/MainWidget.h"
#include <string>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::string str;
    if(argc > 1 && std::string(argv[1]) == "--test")
    {
        std::string attempts_str = "--attempts_num=";
        std::string points_str = "--points_num=";
        int attempts = 0;
        int points = 0;
        for(int i = 2; i < argc; i++)
        {
            str = argv[i];
            size_t found_attempts = str.find(attempts_str);
            size_t found_points = str.find(points_str);
            if (found_attempts != std::string::npos)
            {
                int start = found_attempts + attempts_str.size();
                attempts = atoi(str.substr(start , str.size() - start).c_str());
            }
            if (found_points != std::string::npos)
            {
                int start = found_points + points_str.size();
                points = atoi(str.substr(start , str.size() - start).c_str());
            }
        }
        if(points < 1)
        {
             std::cout << "need at least 1 point" << std::endl;
             return 0;
        }
        std::cout  << attempts << " attempts with " << points << " points" << std::endl << std::endl;


        Validator::test_size = points;

        MainWidget mainWindow;
        for(int i = 0; i < attempts; i++)
        {
            std::cout <<  i << " attempt"<< std::endl;
            mainWindow.clickedRandomNoPicButton();
        }
        return app.exec();
    }
    else
    {
        MainWidget mainWindow;
        mainWindow.show();
        QObject::connect (&mainWindow, SIGNAL(performExitButtonAction()), &app, SLOT(quit()));
        return app.exec();
    }
    return app.exec();
}
