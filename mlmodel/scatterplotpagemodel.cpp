#include "scatterplotpagemodel.h"
#include <QDebug>

ScatterplotPageModel::ScatterplotPageModel() : QObject{nullptr} {
    initModel();
    connect(&timer, &QTimer::timeout, this, ScatterplotPageModel::doRegressionIteration);

    dataset.push_back(QPoint(413, 60));
    dataset.push_back(QPoint(324, 132));
    dataset.push_back(QPoint(244, 222));
    dataset.push_back(QPoint(200, 353));
    dataset.push_back(QPoint(124, 419));
    dataset.push_back(QPoint(44, 492));
    dataset.push_back(QPoint(219, 284));
    dataset.push_back(QPoint(362, 71));
    dataset.push_back(QPoint(167, 373));
    dataset.push_back(QPoint(425, 109));
    dataset.push_back(QPoint(197, 205));
    dataset.push_back(QPoint(97, 400));
    dataset.push_back(QPoint(322, 241));
}

void ScatterplotPageModel::initModel() {
    lrModel = new LinearRegressionModel(1, 100);
}

void ScatterplotPageModel::doRegressionIteration() {
    vector<double> newLine = lrModel->iterateDescent(dataset);
    if (newLine.size() == 1) {
        //Model is done.  Simulate pausing the process.
        handlePauseButtonClick();
    } else {
        currentLine = newLine;
    }
    emit redrawPlotWidget(&dataset, currentLine);
}

void ScatterplotPageModel::handlePlotClick(QMouseEvent* event) {
    // Add the new click spot to the dataset
    dataset.push_back(event->pos());

    emit redrawPlotWidget(&dataset, currentLine);
}

void ScatterplotPageModel::handleStartButtonClick() {
    if (dataset.size() > 0) {
        timer.start(timerInterval);
        emit setUiState(2);
    }
}

void ScatterplotPageModel::handlePauseButtonClick() {
    timer.stop();
    emit setUiState(1);
}

void ScatterplotPageModel::handleStopButtonClick() {
    timer.stop();
    currentLine = vector<double>();
    delete lrModel;
    initModel();
    emit setUiState(0);
    emit redrawPlotWidget(&dataset, currentLine);
}

void ScatterplotPageModel::handleClearButtonClick() {
    currentLine = vector<double>();
    dataset.clear();
    emit redrawPlotWidget(&dataset, currentLine);
}

void ScatterplotPageModel::handleSpeedSliderChange(int position) {
    //Here, the position goes from 1 to 60 and represents iterations/second.
    // the interval is the number of ms between each iteration at that fps.
    timerInterval = (int)(1000.0 / (float)position);
}

ScatterplotPageModel::~ScatterplotPageModel() { delete lrModel; }
