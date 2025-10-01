#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    // Colors I like:
    // orange:      #ff8533
    // lightGray:   #cccccc
    // white:       #ffffff
    // lightBlue:   #a7d6fa
    // darkerBlue:  #3d7ba4

    ui->setupUi(this);
    screenHandler = new ScreenHandler(this);
    this->setStyleSheet(
        QString(
            "* { \
                background-color: white; \
                margin: 0; padding: 0; \
            } \
              \
            "
        )
    );

    screenHandler->setStyleSheet("ScreenHandler { border-top: 2px solid #3d7ba4; }");
    setCentralWidget(screenHandler);

}

void MainWindow::makeConnections(World& worldModel, ScatterplotPageModel* scatterModel) {
    screenHandler->makeConnections(worldModel, scatterModel);
}

MainWindow::~MainWindow() {
    delete ui;
}

