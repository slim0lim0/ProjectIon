#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

// Local Includes:
#include "Tile.h"
#include "BackBuffer.h"
#include "Sprite.h"

// Library Includes:
#include <vector>	

using namespace std;

class TileMap
{
	//Member Methods
public:
	TileMap();
	TileMap(bool IsMask);
	~TileMap();

	bool LoadTileSet(BackBuffer& backBuffer, const char* pcFileName, bool IsMask);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	//Tile* GetTileAt(int i);
	Sprite* GetTileSpriteAt(int i);

private:

	Sprite* ConstructTile(BackBuffer& backBuffer, Uint32* sourcePixels, int width, int height, int offSetWidth, int spriteSheetX, int spriteSheetY, bool IsMask);
	
	//Member Data
public:

private:
	//vector<Tile*> m_lstTiles;
	vector<Sprite*> m_lstTileSprites;
	bool m_IsMask;
};

#endif // __TILE_MAP_H__