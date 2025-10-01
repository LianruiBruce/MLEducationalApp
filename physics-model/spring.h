#ifndef SPRING_H
#define SPRING_H

#include <Box2D/Box2D.h>
#include <QMouseEvent>

class spring {

public:
    spring(b2World* world, b2Body* ball, b2Body* staticGround);

    //Tell the joint where to pull the ball towards
    void bind(b2Vec2 targetPosition);
    //Remove the joint from the world's simulations
    void destroyJoint(b2World* world);

private:
    b2MouseJoint* mouseJoint;

};

#endif // SPRING_H
