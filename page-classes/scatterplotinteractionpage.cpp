#include "scatterplotinteractionpage.h"
#include "ui_scatterplotinteractionpage.h"
#include "scatterplotwidget.h"

ScatterplotInteractionPage::ScatterplotInteractionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterplotInteractionPage) {

    ui->setupUi(this);

    ui->prevButton->setIcon(QIcon(":/resources/img/arrow-left.svg"));
    ui->nextButton->setIcon(QIcon(":/resources/img/arrow-right.svg"));

    this->setStyleSheet(QString(
        "QPushButton { \
            background: #ccc; \
            border: 1px solid #888; \
        } \
        QPushButton:enabled { \
            background: #ffef85; \
            border: 1px solid #dec002; \
        } \
        QPushButton:hover { \
            background: #fff7c4; \
        } \
        QScrollArea QScrollBar:handle { \
                background: #3d7ba4; \
                border: 1px solid #094890; \
                border-radius: 2.5px; \
        } \
        QScrollArea QScrollBar { \
                max-width: 5px; \
        } \
        QScrollArea { \
                border: none; \
                border-top: 1px solid gray; \
                border-bottom: 1px solid gray; \
        } \
        QPushButton#prevButton { \
            background: white !important; \
            border: none !important; \
        } \
        QPushButton#nextButton { \
                background: white !important; \
                border: none !important; \
        } \
        QFrame#titleBox { \
            background: #ffef85; \
            border: 1px solid #dec002; \
            border-radius: 4px; \
        } \
        QLabel#titleLabel { \
            background: #ffef85; \
        } \
        "
    ));

    setUiState(0);
}

void ScatterplotInteractionPage::setUiState(int state) {
    // 0 is stopped, 1 is paused, 2 is running

    if (state == 0) {
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
        ui->clearButton->setEnabled(true);
        ui->speedSlider->setEnabled(true);
    } else if (state == 1) {
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->clearButton->setEnabled(false);
        ui->speedSlider->setEnabled(true);
    } else if (state == 2) {
        ui->startButton->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
        ui->clearButton->setEnabled(false);
        ui->speedSlider->setEnabled(false);
    }

}

void ScatterplotInteractionPage::makeConnections(ScatterplotPageModel* model) {
    connect(ui->plotWidget, &ScatterplotWidget::passClickToModel, model, &ScatterplotPageModel::handlePlotClick);
    connect(model, &ScatterplotPageModel::redrawPlotWidget, ui->plotWidget, &ScatterplotWidget::redrawSelf);
    connect(ui->startButton, &QPushButton::clicked, model, &ScatterplotPageModel::handleStartButtonClick);
    connect(ui->pauseButton, &QPushButton::clicked, model, &ScatterplotPageModel::handlePauseButtonClick);
    connect(ui->stopButton, &QPushButton::clicked, model, &ScatterplotPageModel::handleStopButtonClick);
    connect(ui->clearButton, &QPushButton::clicked, model, &ScatterplotPageModel::handleClearButtonClick);
    connect(ui->speedSlider, &QSlider::sliderMoved, model, &ScatterplotPageModel::handleSpeedSliderChange);
    connect(ui->speedSlider, &QSlider::sliderMoved, this, &ScatterplotInteractionPage::updateSpeedLabelFromSliderValue);
    connect(model, &ScatterplotPageModel::setUiState, this, &ScatterplotInteractionPage::setUiState);

    model->handleStopButtonClick();
}

void ScatterplotInteractionPage::updateSpeedLabelFromSliderValue(int position) {
    ui->speedOutputLabel->setText(QString(QString::fromStdString(std::to_string(position)) + " fps"));
}

QPushButton* ScatterplotInteractionPage::getPrevButton() {
    return ui->prevButton;
}

QPushButton* ScatterplotInteractionPage::getNextButton() {
    return ui->nextButton;
}

ScatterplotInteractionPage::~ScatterplotInteractionPage() { delete ui; }
