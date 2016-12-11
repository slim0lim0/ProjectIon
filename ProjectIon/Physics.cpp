// This Include:

#include "Physics.h"

// Local Includes

// Library Includes

#include "Box2D\Box2D.h"
#include "cassert"

int VELITER = 6;
int POSITER = 2;

const int PPM = 100;

Physics::Physics()
{

}

Physics::~Physics()
{

}

bool
Physics::Initialise()
{
	b2Vec2 gravity(0.0f * PPM, 9.8f * PPM);

	m_pWorld = new b2World(gravity);
	
	SetWorldGravity(gravity.x, gravity.y);

	return true;
}

void
Physics::SetWorldGravity(float xVel, float yVel)
{
	b2Vec2 gravity(xVel, yVel);
	m_pWorld->SetGravity(gravity);
}

void
Physics::Process(float deltaTime)
{
	assert(m_pWorld);
	m_pWorld->Step(deltaTime, VELITER, POSITER);
}

b2Body*
Physics::CreatePlayer()
{
	b2Body* playerBody;
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.angularVelocity = 0.0f;
	playerBodyDef.position.Set(100, 0);
	playerBodyDef.awake = true;
	playerBody = m_pWorld->CreateBody(&playerBodyDef);


	return playerBody;
}