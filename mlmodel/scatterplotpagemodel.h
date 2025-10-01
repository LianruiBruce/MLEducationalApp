#ifndef SCATTERPLOTPAGEMODEL_H
#define SCATTERPLOTPAGEMODEL_H

#include <QObject>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
using std::vector;

#include "linearregressionmodel.h"

class ScatterplotPageModel : public QObject {

    Q_OBJECT

public:
    ScatterplotPageModel();
    ~ScatterplotPageModel();

public slots:
    void handlePlotClick(QMouseEvent* event);
    void handleStartButtonClick();
    void handlePauseButtonClick();
    void handleStopButtonClick();
    void handleClearButtonClick();
    void handleSpeedSliderChange(int position);
    void doRegressionIteration();

signals:
    void redrawPlotWidget(vector<QPoint>* dataset, vector<double> lineVars=vector<double>(0, 0));
    void setUiState(int state); // 0 is stopped, 1 is paused, 2 is running

private:
    LinearRegressionModel* lrModel;
    vector<QPoint> dataset;
    vector<double> currentLine;
    QTimer timer;
    int timerInterval = 33;

    void initModel();

};

#endif // SCATTERPLOTPAGEMODEL_H
