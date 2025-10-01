#ifndef CONCLUSIONPAGE_H
#define CONCLUSIONPAGE_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ConclusionPage;
}

class ConclusionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConclusionPage(QWidget *parent = nullptr);
    QPushButton* getPrevButton();
    QPushButton* getNextButton();
    ~ConclusionPage();

private:
    Ui::ConclusionPage *ui;
};

#endif // CONCLUSIONPAGE_H
