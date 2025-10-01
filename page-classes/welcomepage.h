#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    QPushButton* getPrevButton();
    QPushButton* getNextButton();
    ~WelcomePage();

private:
    Ui::WelcomePage *ui;
};

#endif // WELCOMEPAGE_H
