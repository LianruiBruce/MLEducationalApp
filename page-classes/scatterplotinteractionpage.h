#ifndef SCATTERPLOTINTERACTIONPAGE_H
#define SCATTERPLOTINTERACTIONPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "scatterplotpagemodel.h"

namespace Ui {
class ScatterplotInteractionPage;
}

class ScatterplotInteractionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScatterplotInteractionPage(QWidget *parent = nullptr);
    void makeConnections(ScatterplotPageModel* model);
    QPushButton* getPrevButton();
    QPushButton* getNextButton();
    ~ScatterplotInteractionPage();

public slots:
    void setUiState(int state); // 0 is stopped, 1 is paused, 2 is running
    void updateSpeedLabelFromSliderValue(int position);

private:
    Ui::ScatterplotInteractionPage *ui;
    void setCustomWidget(QWidget *customWidget);

};

#endif // SCATTERPLOTINTERACTIONPAGE_H
