#include "Player.h"
#include "Sprite.h"

#include <assert.h>

Player::Player()
{

}

Player::~Player()
{

}

void
Player::Process(float deltaTime, int LevelWidth, int LevelHeight)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	if (m_pBody != 0)
	{
		b2Vec2 bodyVector = m_pBody->GetPosition();
		b2Vec2 CurrentVelocity = m_pBody->GetLinearVelocity();
		b2Vec2 CollideVelocity(CurrentVelocity.x, 0.0f);
		b2Vec2 GravityVelocity(CurrentVelocity.x, 9.8);

		if (m_y > 500 && m_pBody->GetGravityScale() != 0)
		{
			m_pBody->SetGravityScale(0);
			m_pBody->SetLinearVelocity(CollideVelocity);
			//bodyVector.y = m_y;
		}
		else if( m_y <= 500 && m_pBody->GetGravityScale() == 0)
		{
			m_pBody->SetGravityScale(1);
			m_pBody->SetLinearVelocity(GravityVelocity);
		}
			
		
		m_x = bodyVector.x;
		m_y = bodyVector.y;
	}

	// distance = velocity * time

	//m_x += m_velocityX*deltaTime;

	//if (m_x < 0 || (m_x + m_pSprite->GetWidth()) > LevelWidth)
		//m_x -= m_velocityX*deltaTime;

	//m_y += m_velocityY*deltaTime;

	//if (m_y < 0 || (m_y + m_pSprite->GetHeight()) > LevelHeight)
	//	m_y -= m_velocityY*deltaTime;

}

void
Player::Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTrack)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer, IsCameraControlled, IsCameraTrack);
}

