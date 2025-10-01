#include "realball.h"

RealBall::RealBall(b2World* world, b2Vec2 position, float radius) {
    // Set up the definition for a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Make it dynamic, so it can move
    bodyDef.position.Set(position.x,position.y);    // Set its initial position

    // Create the body in the Box2D world
    m_body = world->CreateBody(&bodyDef);

    // Define the shape of the body
    b2CircleShape circleShape;
    circleShape.m_radius = radius;

    // Define a fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 6.0f;      // Set its density
    fixtureDef.friction = 0.8f;     // Set the friction
    fixtureDef.restitution = 0.3f;  // Set the restitution - bounciness

    // Add the fixture to the body
    m_body->CreateFixture(&fixtureDef);
}
