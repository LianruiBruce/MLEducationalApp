#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "world.h"
#include <QTimer>
#include <QPushButton>
#include "spring.h"

namespace Ui {
class canvas;
}

class canvas : public QWidget
{
    Q_OBJECT

public:
    explicit canvas(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    ~canvas();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    // maybe we shouldn't have this
    void setBox2DWorld(b2World* world); // TODO: Delete this;

    void makeConnections(World& world);
signals:
    void destroyJointInWorld();
    void passMouseEventToModel(QMouseEvent* event);
    void drawWorldDebugData();

public slots:
    void handleRedraw(float, b2Vec2, b2ChainShape*);

private:
    Ui::canvas *ui;
    float ballToDraw_Radius = 0.0f;
    b2Vec2 ballToDraw_Location;
    b2ChainShape* floorShapeToDraw = nullptr;
    QColor ballColor;
    QColor floorColor;
    float pixelToBoxScaleFactor = 1;
    b2Vec2 worldSize;

    b2Vec2 translateBoxToPixelCoords(float coord_x, float coord_y);
    b2Vec2 translatePixelToBoxCoords(int pixel_x, int pixel_y);
    void ingestWorldSize(World& world);

};

#endif // CANVAS_H
