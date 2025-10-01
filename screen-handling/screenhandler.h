/**
 * @file screenhandler.h
 * @brief Definition of the ScreenHandler class, a custom Qt widget
 *        responsible for screen switching and navigation in the
 *        educational application. Utilizes a QStackedWidget to manage
 *        multiple pages and provides functionality for navigating
 *        forward, backward, or directly to a specified page index.
 *
 * @author Vsevolod Cherny && Evan Xu
 */

#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <vector>
#include <QFormLayout>
#include "welcomepage.h"
#include "scatterplotinteractionpage.h"
#include "box2dpage.h"
#include "world.h"
#include "testuserpage.h"

class ScreenHandler : public QFrame {
    Q_OBJECT

public:
    // Constructor for the ScreenHandler class
    // Initializes the UI components, including a stacked widget for page switching
    explicit ScreenHandler(QWidget *parent = nullptr);
    void makeConnections(World& worldModel, ScatterplotPageModel* scatterplotPageModel);



public slots:
    // Slot for navigating to the next page
    // Increments the current index and sets the stacked widget's current index
    void nextPage();

    // Slot for navigating to the previous page
    // Decrements the current index and sets the stacked widget's current index
    void previousPage();

    // Slot for navigating to a specific page by index
    // Sets the current index to the specified index and updates the stacked widget
    void goToPage(int index);

private:
    QStackedWidget *stackedWidget;
    int currentIndex;
    int numPages = 0;

    // Helper method for setting up a page
    // Accepts a QWidget pointer and the index of the page
    void setupBox2DSimulationPage();
    Box2dPage* box2dPagePointer = nullptr;
    ScatterplotInteractionPage* scatterplotPagePointer = nullptr;

    //Setup page methods
    void setupWelcomePage();
    void setupIntroductionPage();
    void setupScatterplotInteractionPage();
    void setupTestUserPage();
    void setupConclusionPage();
};

#endif // SCREENHANDLER_H
