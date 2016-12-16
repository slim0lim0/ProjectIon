#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

// Local Includes:
#include "ControllerPlayer.h"

// Library Includes:
#include <vector>
#include <SDL.h>

// Forward Declarations
class Tile;
class TileMap;
class TileMask;
class BackBuffer;

using namespace std;

class LevelManager
{
	// Member Methods

public:
	LevelManager();
	~LevelManager();

	bool Initialise();

	bool LoadTileMap(BackBuffer& backBuffer, const char* sheetName, const char* maskName);

	bool PrepareLevel(BackBuffer& backBuffer, const char* LevelName);

	void Process(float deltaTime, ControllerPlayer& playerController);
	void Draw(BackBuffer& backBuffer);

	bool CheckTileCollision(Tile& tile, const SDL_Rect& boundsA, const SDL_Rect& boundsB);

	int CheckTilePosition(const SDL_Rect& boundsA, const SDL_Rect& boundsB);


	vector<Tile*> GetTilesSprite();
	vector<Tile*> GetTilesMask();

private:

	SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);
	static bool GetAlphaXY(Uint32* pixels, int x, int y);
	// Temporary Level Method
	bool CreateTest();


	// Member Data
public:

private:
	
	vector<Tile*> m_levelSpriteTiles;
	vector<Tile*> m_levelMaskTiles;
	int m_LevelWidth;
	int m_LevelHeight;

	TileMap* m_pTileMap;
	TileMap* m_pTileMapMask;

};

#endif // __LEVEL_MANAGER_H__