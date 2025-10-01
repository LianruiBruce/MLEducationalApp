#include "conclusionpage.h"
#include "ui_conclusionpage.h"

ConclusionPage::ConclusionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConclusionPage) {

    ui->setupUi(this);
    ui->prevButton->setIcon(QIcon(":/resources/img/arrow-left.svg"));
    this->setStyleSheet(QString("QFrame#titleBox { background: #ffef85; border: 1px solid #dec002; border-radius: 4px; } \
                                 QLabel#titleLabel {background: #ffef85;} \
                                 QPushButton { border: none; } \
                        "));

}

QPushButton* ConclusionPage::getPrevButton() {
    return ui->prevButton;
}

QPushButton* ConclusionPage::getNextButton() {
    return ui->nextButton;
}

ConclusionPage::~ConclusionPage()
{
    delete ui;
}
