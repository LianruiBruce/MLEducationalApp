#ifndef INTRODUCTIONPAGE_H
#define INTRODUCTIONPAGE_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class IntroductionPage;
}

class IntroductionPage : public QWidget {

    Q_OBJECT

public:
    explicit IntroductionPage(QWidget *parent = nullptr);
    QPushButton* getPrevButton();
    QPushButton* getNextButton();
    ~IntroductionPage();

private:
    Ui::IntroductionPage *ui;
};

#endif // INTRODUCTIONPAGE_H
