// This Include

#include "Sprite.h"

// Local Include

#include "Texture.h"
#include "BackBuffer.h"

Sprite::Sprite()
: m_pTexture(0)
, m_x(-500.0)
, m_y(-500.0)
, m_width(0)
, m_height(0)
, m_angle(0.0f)
, m_centerX(0)
, m_centerY(0)
{


}

Sprite::~Sprite()
{

}

bool
Sprite::Initialise(Texture& texture)
{
	m_pTexture = &texture;

	m_width = m_pTexture->GetWidth();
	m_height = m_pTexture->GetHeight();

	return (true);
}

void
Sprite::Process(float deltaTime)
{

}

void
Sprite::Draw(BackBuffer& backBuffer)
{
	backBuffer.DrawSprite(*this);
}

void
Sprite::Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTracked)
{
	backBuffer.DrawSprite(*this, IsCameraControlled, IsCameraTracked);
}

void
Sprite::SetX(int x)
{
	m_x = x;
}

void
Sprite::SetY(int y)
{
	m_y = y;
}

int
Sprite::GetX() const
{
	return(m_x);
}

int
Sprite::GetY() const
{
	return(m_y);
}

float
Sprite::GetAngle() const
{
	return(m_angle);
}

void
Sprite::SetAngle(float angle)
{
	m_angle = angle;
}

void
Sprite::SetCenter(int x, int y)
{
	m_centerX = x;
	m_centerY = y;
}

Texture*
Sprite::GetTexture()
{
	return(m_pTexture);
}

int
Sprite::GetWidth() const
{
	return(m_width);
}

int
Sprite::GetHeight() const
{
	return(m_height);
}

void*
Sprite::GetPixels()
{
	return GetTexture()->GetPixels();
}

int
Sprite::GetPitch()
{

	return GetTexture()->GetPitch();
}

bool
Sprite::LockTexture()
{
	bool success = true;
	if (!GetTexture()->LockTexture())
		success = false;

	return success;
}

bool
Sprite::UnlockTexture()
{
	bool success = true;
	if (!GetTexture()->UnlockTexture())
		success = false;

	return success;
}