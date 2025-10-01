#include "world.h"
#include <QDebug>

World::World(float x_size, float y_size)
    : QObject(nullptr), worldSizeX(x_size), worldSizeY(y_size) {

    theWorld = new b2World(b2Vec2(0.0f, -9.81f)); // Initialize the world with gravity

    createBall(b2Vec2(2.5, 5.0));// Position the ball
    initializeWalls();
    initializeFloors();   
    theWorld->SetContinuousPhysics(true);
    connect(&timer, &QTimer::timeout, this, &World::updateWorld);
    //timer.start(16);
    //Slower time for debugging
    timer.start(20);
    //This is a bogus set of values meant to keep any undefined behavior at bay
    canvasSize = b2Vec2(400, 300);
}

World::~World() {
    clearRestartWorld();
    delete theWorld;
}

void World::passCanvasSize(int width, int height) {
    canvasSize = b2Vec2(width, height);
    boxToPixelScaleFactor = (float)width / worldSizeX;
}

RealBall* World::createBall(b2Vec2 position) {
    if (m_ball != nullptr) {
        qDebug() << "Repeat call to Create Ball!  Ignoring..";
    }
    // Create a new ball at the specified position
    m_ball = new RealBall(theWorld, position, ballRadius);
    return m_ball;
}

void World::initializeFloors() {

    QVector<float> intersections;
    intersections.append(0);
    intersections.append(10);

    srand(time (0));
    float num;
    while(intersections.count() <= 7)
    {
        if(!intersections.contains(num = rand() % 10))
        {
            intersections.append(num);
        }
    }

    QVector<QVector<b2Vec2>> newFloorList;
    floorList = newFloorList;
    floorList.append(getCoords(intersections, 0.1, 0.01));

    //Translate floors into pixel coords
    for (int j = 0; j < floorList.size(); j++) {
        QVector<b2Vec2>* floor = &(floorList[j]);
        QVector<b2Vec2> floorPixel;
        for (int i = 0; i < floor->length(); i++) {
            floorPixel.append(translateBoxToPixelCoords(
                floor->at(i).x, floor->at(i).y));
        }
        floorPixelList.append(floorPixel);
    }

    setFloor(0);
}

QVector<b2Vec2> World::getCoords(QVector<float> intersectionCoords, float spacing, float _leadingCoef)
{
    float x = 0.0;
    QVector<b2Vec2> ret;
    float segmentCount = (worldSizeX / spacing);

    for(int i = 0; i < segmentCount+1; i++)
    {
        float leadingCoef = _leadingCoef;
        for(int j = 0; j < intersectionCoords.length(); j++)
        {
            leadingCoef = (x - intersectionCoords[j]) * leadingCoef;           
        }

        //this if statement changes the leading coefficient to always make a graph within the y-bounds (yes -0 exists (i know right?))
        if(!(leadingCoef < 3 && leadingCoef > -3) && leadingCoef != -0)
        {
            return getCoords(intersectionCoords, spacing, _leadingCoef - 0.00001);
        }

        x += spacing;
        ret.append(b2Vec2(i / worldSizeX, leadingCoef + 3.5));
    }

    return ret;
}

void World::setFloor(int floor) {

    if (currentFloorBody != nullptr) {
        theWorld->DestroyBody(currentFloorBody);
    }

    currentFloorIndex = floor;

    //Translate floor points into the right form
    QVector<b2Vec2> *reference = &floorList[floor];
    b2Vec2 translatedPoints [reference->length()];
    for (int i = 0; i < reference->length(); i++) {
        translatedPoints[i] = b2Vec2(reference->at(i).x, reference->at(i).y);
    }

    b2ChainShape chainShape;
    chainShape.CreateChain(translatedPoints, reference->length());
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    b2Body* chainBody = theWorld->CreateBody(&bodyDef);
    fixtureDef.shape = &chainShape;
    fixtureDef.density = 1.0f;
    chainBody->CreateFixture(&fixtureDef);
    currentFloorBody = chainBody;
    m_ball->getBody()->SetTransform(b2Vec2(2.5, 6.0), 0.0);
}

void World::initializeWalls() {
    //This section creates a static "ground", and is not part of
    // the walls or floor of our simulation - Matthew
    b2BodyDef staticGroundBodyDef;
    staticGroundBodyDef.type = b2_staticBody;
    staticGroundBody = theWorld->CreateBody(&staticGroundBodyDef);

    // Thickness of the boundary walls
    float wallThickness = 0.5f;

    // Positions and sizes for the boundary walls
    b2Vec2 bottomWallPos(worldSizeX / 2, worldSizeY + wallThickness / 2);
    b2Vec2 topWallPos(worldSizeX / 2, -wallThickness / 2);
    b2Vec2 leftWallPos(-wallThickness / 2, worldSizeY / 2);
    b2Vec2 rightWallPos(worldSizeX + wallThickness / 2, worldSizeY / 2);

    b2Vec2 horizontalWallSize(worldSizeX / 2, wallThickness / 2);
    b2Vec2 verticalWallSize(wallThickness / 2, worldSizeY / 2);

    // Create boundary walls (bottom, top, left, right)
    createWall(bottomWallPos, horizontalWallSize);
    createWall(topWallPos, horizontalWallSize);
    createWall(leftWallPos, verticalWallSize);
    createWall(rightWallPos, verticalWallSize);
}

void World::createWall(const b2Vec2& position, const b2Vec2& size) {
    // Define the wall body
    b2BodyDef wallBodyDef;
    wallBodyDef.position.Set(position.x, position.y);

    // Create the wall body in the world
    b2Body* wallBody = theWorld->CreateBody(&wallBodyDef);

    // Define the wall shape as a rectangle
    b2PolygonShape wallBox;
    wallBox.SetAsBox(size.x, size.y);

    // Create the fixture on the wall body
    wallBody->CreateFixture(&wallBox, 0.0f);
}

void World::updateGravity(int level) {
    //original gravity b2Vec2(0.f, .00015f)
    theWorld->SetGravity(b2Vec2(0.0f, -9.81f + (level * 0.5f)));
}

bool World::isGameOver() const {
    // Implement game over logic
    return false;
}

void World::clearRestartWorld() {
    // Delete all bodies and recreate the ground
    // You'll need to properly delete or clear the pointers in myBalls if you're using such a container
    for (b2Body* body = theWorld->GetBodyList(); body != nullptr;) {
        b2Body* nextBody = body->GetNext();
        theWorld->DestroyBody(body);
        body = nextBody;
    }
    initializeWalls();
    setFloor(0);
}

b2World* World::getWorld()
{
    return theWorld;
}

void World::updateWorld() {
    theWorld->Step(1.0f / 60.0f, 6, 2);
    b2Vec2 pos = getBallPosition();

    float translatedRadius = ballRadius * canvasSize.x / worldSizeX;
    b2Vec2 translatedLocation = translateBoxToPixelCoords(pos.x, pos.y);
    emit updateView(
        translatedRadius,
        translatedLocation,
        (b2ChainShape*)currentFloorBody->GetFixtureList()->GetShape()
    );
}

b2Vec2 World::getBallPosition() const {
    return m_ball->getBody()->GetPosition();
}

void World::drawDebugData() {
    theWorld->DrawDebugData();
}

//TODO: Remove this method
b2Joint* World::CreateJointProxy(b2MouseJointDef* def) {
    return theWorld->CreateJoint(def);
}

void World::handleMouseEvent(QMouseEvent* event) {
    if (event->type() == QMouseEvent::MouseButtonDblClick) { return; }

    b2Vec2 mousePos = translatePixelToBoxCoords(event->pos().x(), event->pos().y());

    if (event->type() == QMouseEvent::MouseButtonPress) {
        //Create the ball and set it's target
        if (mouseSpring == nullptr) {
            mouseSpring = new spring(theWorld, m_ball->getBody(), staticGroundBody);
            mouseSpring->bind(mousePos);
        }
    } else if (event->type() == QMouseEvent::MouseButtonRelease) {
        //Get rid of the mouse spring joint
        if (mouseSpring != nullptr) {
            mouseSpring->destroyJoint(theWorld);
            delete mouseSpring;
            mouseSpring = nullptr;
            m_ball->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
        }
    } else if (event->type() == QMouseEvent::MouseMove) {
        mouseSpring->bind(mousePos);
    }
}

b2Vec2 World::translateBoxToPixelCoords(float coord_x, float coord_y) {
    return b2Vec2(
        (int)(coord_x * boxToPixelScaleFactor),
        (int)((worldSizeY-coord_y) * boxToPixelScaleFactor)
    );
}

b2Vec2 World::translatePixelToBoxCoords(int pixel_x, int pixel_y) {
    return b2Vec2(
        (float)pixel_x / boxToPixelScaleFactor,
        (float)(canvasSize.y-pixel_y) / boxToPixelScaleFactor
        );
}
