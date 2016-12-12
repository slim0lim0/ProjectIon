#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

// Local Includes:
#include "ControllerPlayer.h"

// Library Includes:
#include <vector>

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

	bool CheckTileCollisionOuter(Tile& tile, float xStart, float xEnd, float yStart, float yEnd);
	bool CheckTileCollisionInner(Tile& tile, float xStart, float xEnd, float yStart, float yEnd);

	// Temporary Level Method
	bool CreateTest();

	vector<Tile*> GetTilesSprite();
	vector<Tile*> GetTilesMask();

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