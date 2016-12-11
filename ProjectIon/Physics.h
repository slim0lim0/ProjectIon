#ifndef __PHYSICS_H__
#define __PHYSICS_H__

// Library Include:
#include <Box2D/Box2D.h>

class Physics
{
	// Member Methods
public:
	Physics();
	~Physics();

	bool Initialise();

	void SetWorldGravity(float xVel, float yVel);

	b2Body* CreatePlayer();

	void Process(float deltaTime);

private:

	// Member Data
public:
	b2World* m_pWorld;

};

#endif // __PHYSICS_H__