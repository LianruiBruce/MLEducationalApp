#include "scatterplotwidget.h"
#include "ui_scatterplotwidget.h"
#include <QPainter>

ScatterplotWidget::ScatterplotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterplotWidget) {

    ui->setupUi(this);
    dotRadius = 2.0f;

}

void ScatterplotWidget::mousePressEvent(QMouseEvent* event) {
    emit passClickToModel(event);
}

void ScatterplotWidget::redrawSelf(vector<QPoint>* _dataset, vector<double> _lineVars) {
    //Save parameter data for the paint method to use
    dataset = _dataset;
    lineVars = _lineVars;
    update();
}

void ScatterplotWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    //Draw border around self
    painter.setPen(QColor("#a6c8de"));
    painter.drawRect(QRect(0, 0, this->width()-1, this->height()-1));

    if (dataset != nullptr) {
        painter.setBrush(QBrush(QColor(Qt::black)));
        for (vector<QPoint>::size_type i = 0; i < dataset->size(); i++) {
            painter.drawEllipse(dataset->at(i), dotRadius, dotRadius);
        }
    }

    painter.setRenderHint(QPainter::Antialiasing);
    if (lineVars.size() > 1) {
        QPen pen;
        pen.setWidth(1.4);
        pen.setColor(QColor(255, 150, 0));
        painter.setPen(pen);
        painter.drawLine(0, lineVars[1], this->width(), (this->width() * lineVars[0]) + lineVars[1]);
    }
}

ScatterplotWidget::~ScatterplotWidget() { delete ui; }
