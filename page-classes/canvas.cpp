#include "canvas.h"
#include "ui_canvas.h"
#include <QMouseEvent>
canvas::canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::canvas) {

    ui->setupUi(this);
    ballColor = QColor(255, 150, 0);
    floorColor = QColor(Qt::green);
}

canvas::~canvas()
{
    delete ui;
}

void canvas::mousePressEvent(QMouseEvent *event) { emit passMouseEventToModel(event); }
void canvas::mouseReleaseEvent(QMouseEvent *event) { emit passMouseEventToModel(event); }
void canvas::mouseMoveEvent(QMouseEvent *event) { emit passMouseEventToModel(event); }

void canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //DebugDraw debugDraw(painter);

    //Outline self
    painter.setPen(QColor(126, 166, 191));
    painter.drawRect(QRect(0, 0, this->width()-1, this->height()-1));

    painter.setPen(QColor(Qt::black));

    if (ballToDraw_Location.x != 0) {
        painter.setBrush(QBrush(ballColor));
        painter.drawEllipse(QRect(ballToDraw_Location.x - ballToDraw_Radius,
            ballToDraw_Location.y - ballToDraw_Radius, ballToDraw_Radius*2, ballToDraw_Radius*2));
        // This line does the same thing as above
        //debugDraw.DrawCircle(ballToDraw_Location + b2Vec2(-ballToDraw_Radius, -ballToDraw_Radius), ballToDraw_Radius, ballColor);
    }


    if (floorShapeToDraw != nullptr) {
        int v_count = floorShapeToDraw->m_count;
        b2Vec2 lastVertex = translateBoxToPixelCoords(
            floorShapeToDraw->m_vertices[0].x, floorShapeToDraw->m_vertices[0].y);

        painter.setBrush(QBrush(floorColor));
        for (int i = 1; i < v_count; i++) {
            b2Vec2 temp = translateBoxToPixelCoords(
                floorShapeToDraw->m_vertices[i].x, floorShapeToDraw->m_vertices[i].y);

            painter.drawLine(lastVertex.x, lastVertex.y, temp.x, temp.y);
            // This line does nothing - No result achieved
            //debugDraw.DrawSegment(lastVertex, temp, floorColor);
            lastVertex = temp;
        }
    }

    emit drawWorldDebugData();
}

void canvas::handleRedraw(float ball_radius, b2Vec2 ball_location, b2ChainShape* floorShape) {
    ballToDraw_Radius = ball_radius;
    ballToDraw_Location = ball_location;
    floorShapeToDraw = floorShape;
    this->update();
}

void canvas::makeConnections(World& world) {
    world.passCanvasSize(this->minimumWidth(), this->minimumHeight());
    ingestWorldSize(world);

    connect(&world, &World::updateView, this, &canvas::handleRedraw);
    connect(this, &canvas::passMouseEventToModel, &world, &World::handleMouseEvent);
    connect(this, &canvas::drawWorldDebugData, &world, &World::drawDebugData);
}

void canvas::ingestWorldSize(World &world) {
    worldSize = b2Vec2(world.worldSizeX, world.worldSizeY);
    pixelToBoxScaleFactor = world.worldSizeX / (float)this->minimumWidth();
}

b2Vec2 canvas::translateBoxToPixelCoords(float coord_x, float coord_y) {
    return b2Vec2(
        (int)(coord_x / pixelToBoxScaleFactor),
        (int)((worldSize.y-coord_y) / pixelToBoxScaleFactor)
        );
}

b2Vec2 canvas::translatePixelToBoxCoords(int pixel_x, int pixel_y) {
    return b2Vec2(
        (float)pixel_x * pixelToBoxScaleFactor,
        (float)(this->minimumHeight()-pixel_y) * pixelToBoxScaleFactor
        );
}
