#include "Background.h"
#include "Sprite.h"

#include <assert.h>

Background::Background()
{
	SetPositionX(0);
	SetPositionY(0);
}

Background::~Background()
{

}

void
Background::Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTrack)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer, IsCameraControlled, IsCameraTrack);
}

