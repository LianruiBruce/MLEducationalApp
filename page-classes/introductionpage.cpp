#include "introductionpage.h"
#include "ui_introductionpage.h"

IntroductionPage::IntroductionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroductionPage) {

    ui->setupUi(this);

    ui->prevButton->setIcon(QIcon(":/resources/img/arrow-left.svg"));
    ui->nextButton->setIcon(QIcon(":/resources/img/arrow-right.svg"));

    this->setStyleSheet(QString("QFrame#introBox { background: #ffef85; border: 1px solid #dec002; border-radius: 4px; } \
                                 QLabel#introLabel {background: #ffef85;} \
                                 QPushButton { border: none; } \
                        "));

}

QPushButton* IntroductionPage::getPrevButton() {
    return ui->prevButton;
}

QPushButton* IntroductionPage::getNextButton() {
    return ui->nextButton;
}

IntroductionPage::~IntroductionPage() {
    delete ui;
}
