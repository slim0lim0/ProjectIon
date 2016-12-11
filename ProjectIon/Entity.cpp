//Entity Body

//This includes:
#include "Entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>
#include <Box2D/Box2D.h>

Entity::Entity()
: m_bExists(true)
, m_x(-500.0f)
, m_y(-500.0f)
, m_velocityY(0.0f)
, m_velocityX(0.0f)
, m_pBody(0)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// distance = velocity * time
	
	m_x += m_velocityX*deltaTime;

	m_y += m_velocityY*deltaTime;
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}


float
Entity::GetPositionX()
{
	return (m_x);
}

float
Entity::GetPositionY()
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

float
Entity::GetWidth()
{
	return m_pSprite->GetWidth();
}

float
Entity::GetHeight()
{
	return m_pSprite->GetHeight();
}

bool
Entity::Exists()
{
	return (m_bExists);
}

b2Body*
Entity::GetBody()
{
	return m_pBody;
}

void
Entity::SetBody(b2Body* body)
{
	m_pBody = body;
}