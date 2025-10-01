#ifndef REALBALL_H
#define REALBALL_H
#include <box2d/box2d.h>

#include "Box2D/Common/b2Math.h"
class RealBall
{
public:
    RealBall(b2World*, b2Vec2, float);
    b2Body* getBody(){return m_body;}
private:
    b2Body* m_body;
};


#endif // REALBALL_H
