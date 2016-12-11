// Entity Class contains the frame of any object. This includes:

// Object Consturct, Destruct
// Object Texture
// Object X, Y
// Object Update
// Object Draw
// Object Existence

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Sprite;
class BackBuffer;

#include <Box2D/Box2D.h>

class Entity
{

	// Member Methods
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);

	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);

	float GetPositionX();
	void SetPositionX(float x);

	float GetPositionY();
	void SetPositionY(float y);

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float velocityX);

	float GetVerticalVelocity();
	void SetVerticalVelocity(float velocityY);

	float GetWidth();
	float GetHeight();

	b2Body* GetBody();
	void SetBody(b2Body* body);

	bool Exists();

private:
	Entity(const Entity& oEntity);
	Entity& operator=(const Entity& oEntity);

	// Member Data

protected:
	Sprite* m_pSprite;

	float m_y;
	float m_x;
	float m_velocityY;
	float m_velocityX;

	bool m_bExists;

	b2Body* m_pBody;
};

#endif
