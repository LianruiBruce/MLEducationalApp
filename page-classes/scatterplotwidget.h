#ifndef SCATTERPLOTWIDGET_H
#define SCATTERPLOTWIDGET_H

#include <QWidget>
#include <vector>
using std::vector;

namespace Ui {
class ScatterplotWidget;
}

class ScatterplotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScatterplotWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *) override;
    ~ScatterplotWidget();

public slots:
    void redrawSelf(vector<QPoint>* dataset, vector<double> lineVars=vector<double>());

signals:
    void passClickToModel(QMouseEvent* event);

private:
    Ui::ScatterplotWidget *ui;
    vector<QPoint>* dataset = nullptr;
    vector<double> lineVars;
    float dotRadius = 0;
};

#endif // SCATTERPLOTWIDGET_H
