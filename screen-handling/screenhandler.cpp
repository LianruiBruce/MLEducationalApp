#include "screenhandler.h"

#include "introductionpage.h"
#include "conclusionpage.h"

ScreenHandler::ScreenHandler(QWidget *parent) : QFrame(parent) {
    // Create main layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setGeometry(QRect(0, 0, this->width(), this->height()));

    // Create stacked widget to hold pages
    stackedWidget = new QStackedWidget(this);

    //-----------------[ Example Code ]---------------------------
    /*
    //Three Steps: 1) Instantiate pointer, 2) connect buttons to slots, 3) add widget to class members
    ExamplePageAdd *examplePage = new ExamplePageAdd(this);
    connect(examplePage->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(examplePage->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    stackedWidget->addWidget(examplePage);
    pages.push_back(examplePage);
    */
    // --------------[ End Example Code ]--------------------------

    //----------[ Here we set up all the pages to add ]---------------------
    setupWelcomePage();
    setupIntroductionPage();
    setupScatterplotInteractionPage();
    setupBox2DSimulationPage();
    setupTestUserPage();
    setupConclusionPage();
    // Set the initial page
    currentIndex = 0;
    stackedWidget->setCurrentIndex(currentIndex);

    // Add stacked widget to the main layout
    layout->addWidget(stackedWidget);
}

void ScreenHandler::makeConnections(World &worldModel, ScatterplotPageModel* scatterplotPageModel) {
    box2dPagePointer->makeConnections(worldModel);
    scatterplotPagePointer->makeConnections(scatterplotPageModel);
}

void ScreenHandler::nextPage() {
    currentIndex = (currentIndex + 1) % numPages;
    stackedWidget->setCurrentIndex(currentIndex);
}

void ScreenHandler::previousPage() {
    currentIndex = (currentIndex - 1 + numPages) % numPages;
    stackedWidget->setCurrentIndex(currentIndex);
}

void ScreenHandler::goToPage(int index) {
    if (index >= 0 && index < numPages) {
        currentIndex = index;
        stackedWidget->setCurrentIndex(currentIndex);
    }
}

void ScreenHandler::setupWelcomePage() {
    //Instantiate pointer
    WelcomePage *page = new WelcomePage(this);
    //Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    //Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    numPages+=1;
}

void ScreenHandler::setupIntroductionPage() {
    //Instantiate pointer
    IntroductionPage *page = new IntroductionPage(this);
    //Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    //Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    numPages+=1;
}

void ScreenHandler::setupScatterplotInteractionPage() {
    //Instantiate pointer
    ScatterplotInteractionPage *page = new ScatterplotInteractionPage(this);
    //Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    //Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    scatterplotPagePointer = page;
    numPages+=1;
}

void ScreenHandler::setupBox2DSimulationPage() {
    //Instantiate pointer
    Box2dPage *page = new Box2dPage(this);
    //Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    //Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    box2dPagePointer = page;
    numPages+=1;
}

void ScreenHandler::setupTestUserPage() {
    // Instantiate pointer
    testUserPage *page = new testUserPage(this);
    // Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    // Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    numPages+=1;
}

void ScreenHandler::setupConclusionPage() {
    //Instantiate pointer
    ConclusionPage *page = new ConclusionPage(this);
    //Connect buttons to slots
    connect(page->getPrevButton(), QPushButton::clicked, this, &ScreenHandler::previousPage);
    connect(page->getNextButton(), QPushButton::clicked, this, &ScreenHandler::nextPage);
    //Add widget to screen-handler class members
    stackedWidget->addWidget(page);
    numPages+=1;
}
