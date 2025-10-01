#ifndef WORLD_H
#define WORLD_H

#include <box2d/box2d.h>
#include "realball.h"
#include <QPainter>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QVector>
#include <QObject>
#include <QTimer>
#include "realball.h"
#include "spring.h"

class World : public QObject {

    Q_OBJECT

public:
    float worldSizeX;
    float worldSizeY;
    b2Body* staticGroundBody;

    World(float x_size, float y_size);
    ~World();
    RealBall* createBall(b2Vec2 position);
    bool isGameOver() const;
    void clearRestartWorld();
    b2World* getWorld();
    void updateGravity(int level);
    b2Vec2 floor1Points[4];

    b2Vec2 getBallPosition() const;

    void setDebugDraw(QPainter& painter);
    void drawDebugData();
    void passCanvasSize(int, int);
    QVector<b2Vec2> getCoords(QVector<float>, float, float);

signals:
    void updateView(float, b2Vec2, b2ChainShape*);

public slots:
    void updateWorld();
    void handleMouseEvent(QMouseEvent* event);
    b2Joint* CreateJointProxy(b2MouseJointDef* def);
    void initializeFloors();

private:
    b2World* theWorld;
    RealBall* m_ball = nullptr;
    float ballRadius = 0.27f;
    float boxToPixelScaleFactor = 1.0f;
    QTimer timer;
    spring* mouseSpring;
    QVector<b2Body*> groundBodiesVector;
    QVector<QVector<b2Vec2>> floorList;      //Holds possible floor chain objects
    QVector<QVector<b2Vec2>> floorPixelList; //Holds the chain objects' QWidget positions
    int currentFloorIndex = 0;
    b2Body* currentFloorBody = nullptr;
    b2Vec2 canvasSize;

    void createWall(const b2Vec2& position, const b2Vec2& size);
    void setFloor(int floor);
    void initializeWalls();
    b2Vec2 translateBoxToPixelCoords(float coord_x, float coord_y);
    b2Vec2 translatePixelToBoxCoords(int pixel_x, int pixel_y);

};

#endif // WORLD_H
