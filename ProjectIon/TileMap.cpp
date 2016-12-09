// This Include:
#include "TileMap.h"

// Local Include:
#include "Sprite.h"
#include "BackBuffer.h"
#include "Tile.h"
#include "Texture.h"

#include <string>
#include <list>
#include <cassert>

Sprite* m_pSprite;
BackBuffer* m_backBuffer;

using namespace std;

TileMap::TileMap()
{

}

TileMap::~TileMap()
{

}

Sprite*
TileMap::ConstructTile(BackBuffer& backBuffer, Uint32* pixels, int width, int height, int offSetWidth, int spriteSheetX, int spriteSheetY, bool IsMask)
{

	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;

	int tilePitch = TILE_WIDTH * 4;

	int tileOffset = 0;
	int spriteSheetOffset = 0;

	Uint32 tilePixels[TILE_WIDTH * TILE_HEIGHT];

	//Uint32 colorToChange = SDL_MapRGB(SDL_GetWindowSurface(backBuffer.GetWindow())->format, 0x40, 0x20, 0x80);
	//Uint32 colorTarget = SDL_MapRGB(SDL_GetWindowSurface(backBuffer.GetWindow())->format, 0x40, 0x40, 0xC0);
	//Uint32 colorTransparent = SDL_MapRGBA(SDL_GetWindowSurface(backBuffer.GetWindow())->format, 0x40, 0x40, 0xC0, 0xFF);


	for (int y = 0; y < TILE_HEIGHT; y++)
	{
		int tileOffset = (y * TILE_WIDTH);
		int spriteSheetOffset = ((y * offSetWidth) + (spriteSheetY * offSetWidth));
		for (int x = 0; x < TILE_WIDTH; x++)
		{
			Uint32 currentPixel = pixels[spriteSheetOffset + x + spriteSheetX];

			tilePixels[tileOffset + x] = currentPixel;
		}
	}

	tileOffset = 0;

	// Build the tileID

	int ID = m_lstTileSprites.size();
	char* combine;
	char IDstring[32];
	char nameMask[64] = "tileMask";
	char nameSprite[64] = "tileSprite";
	char* name = "";
	sprintf_s(IDstring, "%d", ID);
	if (IsMask)
	{
		strcat_s(nameMask, IDstring);
		name = nameMask;
	}
	else
	{
		strcat_s(nameSprite, IDstring);
		name = nameSprite;
	}


	Sprite* tileSprite = backBuffer.CreateSprite(backBuffer.ClipTexture(TILE_WIDTH, TILE_HEIGHT, tilePixels, tilePitch, IsMask), name);

	return tileSprite;
}

bool
TileMap::LoadTileSet(BackBuffer& backBuffer, const char* pcFileName, bool IsMask)
{

	const int TILE_HEIGHT = 32;
	const int TILE_WIDTH = 32;



	Sprite* sprite = new Sprite();
	sprite = backBuffer.CreateSprite(pcFileName, true);

	assert(sprite);
	m_pSprite = sprite;

	m_pSprite->LockTexture();


	Uint32* pixels = (Uint32*)m_pSprite->GetPixels();
	
	int pixelCount = (m_pSprite->GetPitch() / 4) * m_pSprite->GetHeight();
	

	for (int y = 0; y < m_pSprite->GetHeight(); y += TILE_HEIGHT)
	{
		for (int x = 0; x < m_pSprite->GetWidth(); x += TILE_WIDTH)
		{
			Sprite* sprite = ConstructTile(backBuffer, pixels, TILE_WIDTH, TILE_HEIGHT, m_pSprite->GetWidth(), x, y, IsMask);
			m_lstTileSprites.push_back(sprite);
		}
	}

	m_pSprite->UnlockTexture();

	return true;
}
//
//void
//TileMap::Process(float deltaTime)
//{
//	for each(Tile* t in m_lstTiles)
//	{
//		t->Process(deltaTime);
//	}
//}
//
//void
//TileMap::Draw(BackBuffer& backBuffer)
//{
//	//m_pSprite->Draw(backBuffer);
//	for each(Tile* t in m_lstTiles)
//	{
//		t->Draw(backBuffer);
//	}
//}

Sprite*
TileMap::GetTileSpriteAt(int i)
{

	if (m_lstTileSprites.size() > 0 && i < m_lstTileSprites.size())
	{
		return m_lstTileSprites[i];
	}
}