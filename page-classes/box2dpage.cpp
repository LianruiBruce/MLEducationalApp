#include "box2dpage.h"
#include "ui_box2dpage.h"

Box2dPage::Box2dPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Box2dPage) {

    ui->setupUi(this);

    ui->prevButton->setIcon(QIcon(":/resources/img/arrow-left.svg"));
    ui->nextButton->setIcon(QIcon(":/resources/img/arrow-right.svg"));

    this->setStyleSheet(QString(" \
        QFrame#titleFrame { background: #ffef85; border: 1px solid #dec002; border-radius: 4px; } \
        QLabel#titleLabel { background: #ffef85; } \
        QPushButton { border: none; } \
        QPushButton#randomGraphButton { background: #ffef85; border: 1px solid #dec002; } \
        QPushButton#randomGraphButton:hover { background: #fff7c4; } \
        QScrollArea QScrollBar { max-width: 5px; } \
        QScrollArea { border: none; border-top: 2px solid lightGray; border-bottom: 2px solid lightGray; } \
        QScrollArea QScrollBar:handle { background: #3d7ba4; border: 1px solid #094890; } \
    "));
}

QPushButton* Box2dPage::getPrevButton() {
    return ui->prevButton;
}

QPushButton* Box2dPage::getNextButton() {
    return ui->nextButton;
}

void Box2dPage::makeConnections(World &worldModel) {
    ui->canvasWidget->makeConnections(worldModel);
    ui->canvasWidget->connect(ui->randomGraphButton, &QPushButton::clicked, &worldModel, &World::initializeFloors);
}

Box2dPage::~Box2dPage() { delete ui; }
