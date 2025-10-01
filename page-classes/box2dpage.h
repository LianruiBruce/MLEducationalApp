#ifndef BOX2DPAGE_H
#define BOX2DPAGE_H

#include <QWidget>
#include <QPushButton>

#include "world.h"

namespace Ui {
class Box2dPage;
}

class Box2dPage : public QWidget
{
    Q_OBJECT

public:
    explicit Box2dPage(QWidget *parent = nullptr);
    QPushButton* getPrevButton();
    QPushButton* getNextButton();
    void makeConnections(World& worldModel);
    ~Box2dPage();

private:
    Ui::Box2dPage *ui;
};

#endif // BOX2DPAGE_H
