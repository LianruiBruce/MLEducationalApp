#include "spring.h"
#include <QDebug>


spring::spring(b2World* world, b2Body* ball, b2Body* staticGround) {

    //Create the actual underlying joint
    b2MouseJointDef def;
    def.bodyA = staticGround;
    def.bodyB = ball;
    def.maxForce = 1200.0;
    def.dampingRatio = 0.9;
    def.collideConnected = false;
    def.target = ball->GetPosition();
    mouseJoint = (b2MouseJoint*)world->CreateJoint(&def);

}

void spring::bind(b2Vec2 targetPosition) {
    mouseJoint->SetTarget(targetPosition);
}

void spring::destroyJoint(b2World* world) {
    world->DestroyJoint(mouseJoint);
}
