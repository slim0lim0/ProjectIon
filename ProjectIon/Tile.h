#ifndef __TILE_H__
#define __TILE_H__

// Local Includes:
#include "Sprite.h"
// Library Includes:
#include <SDL.h>

class BackBuffer;

class Tile
{
	// Member Methods
public:
	Tile();
	Tile(int tileCode);
	~Tile();

	void SetX(int x);
	void SetY(int y);

	int GetX();
	int GetY();

	Sprite& GetSprite();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);


	// Member Data
public:


private:

	SDL_Rect* m_pTileBox;
	int m_x;
	int m_y;
	
	int m_width;
	int m_height;

	int m_tileID;

	Sprite* m_pSprite;
};

#endif //__TILE_H__