// This Include:
#include "Tile.h"

// Local Includes:
#include "Sprite.h"
#include "BackBuffer.h"

// Library Includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>


Tile::Tile()
{

}

Tile::Tile(int tileID)
{
	m_tileID = tileID;
}

Tile::~Tile()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Tile::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	m_pTileBox = new SDL_Rect();
	m_pTileBox->x = 0;
	m_pTileBox->y = 0;
	m_pTileBox->w = m_pSprite->GetWidth();
	m_pTileBox->h = m_pSprite->GetHeight();

	return true;
}

void
Tile::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
}

void
Tile::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

void 
Tile::SetX(int x)
{
	m_x = x;
}
void 
Tile::SetY(int y)
{
	m_y = y;
}

int 
Tile::GetX()
{
	return(m_x);
}

int 
Tile::GetY()
{
	return(m_y);
}

Sprite&
Tile::GetSprite()
{
	assert(m_pSprite);
	return(*m_pSprite);
}