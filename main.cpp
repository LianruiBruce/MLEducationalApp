#include "mainwindow.h"
#include <QApplication>
#include "world.h"
#include "linearregressionmodel.h"
#include "scatterplotpagemodel.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;

    //Creat needed models
    World myWorld(10.0f, 7.5f);
    ScatterplotPageModel scatterModel;

    w.makeConnections(myWorld, &scatterModel);
    w.show();
    return a.exec();

}
