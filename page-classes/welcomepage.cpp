#include "welcomepage.h"
#include "ui_welcomepage.h"
#include <QVBoxLayout>

WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomePage) {

    ui->setupUi(this);

    this->setStyleSheet(QString("QFrame#welcomeBox { background: #ffef85; border: 1px solid #dec002; border-radius: 4px; } \
                                 QLabel#welcomeLabel1, QLabel#welcomeLabel2 {background: #ffef85;} \
                                 QPushButton { border: none; } \
                                 QPushButton#revButton { display: none; }"));

    ui->nextButton->setIcon(QIcon(":/resources/img/arrow-right.svg"));

}

QPushButton* WelcomePage::getPrevButton() {
    return ui->prevButton;
}

QPushButton* WelcomePage::getNextButton() {
    return ui->nextButton;
}

WelcomePage::~WelcomePage() {
    delete ui;
}
