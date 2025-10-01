/**
 * @file mainwindow.h
 * @brief Definition of the MainWindow class, representing the
 *        main window of the educational application.
 *        The MainWindow class includes the ScreenHandler widget,
 *        serving as the central component for managing UI and
 *        screen navigation.
 * @author Vsevolod Cherny && Evan Xu
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "screenhandler.h"
#include "scatterplotpagemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void makeConnections(World& worldModel, ScatterplotPageModel* scatterModel);

private:
    Ui::MainWindow *ui;
    ScreenHandler *screenHandler;
};
#endif // MAINWINDOW_H
