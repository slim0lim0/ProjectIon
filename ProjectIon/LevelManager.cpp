// This Include:
#include "LevelManager.h"

// Local Includes:

#include "TileMap.h"
#include "Tile.h"
#include "Texture.h"

#include <SDL.h>

#include <iostream>
#include <string>
#include <fstream>

#include <vector>

using namespace std;
//const int LEVEL_WIDTH = 1920;
//const int LEVEL_HEIGHT = 1080;
//const int TEST_WIDTH = 640;
//const int TEST_HEIGHT = 480;

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{

}

bool
LevelManager::Initialise()
{

	return true;
}

bool
LevelManager::PrepareLevel(BackBuffer& backBuffer, const char* LevelName)
{
	vector<int> gData;

	int currentID = 0;

	ifstream file(LevelName);
	if (file.is_open())
	{
		string spriteSheet = "";
		string maskSheet = "";

		const char* spriteSheetName = "";
		const char* maskSheetName = "";

		file >> spriteSheet;
		spriteSheetName = spriteSheet.c_str();
		file >> maskSheet;
		maskSheetName = maskSheet.c_str();

	/*	while (file >> spriteSheetName)
		{

		}
		while (file >> maskSheetName)
		{

		}*/
		//file >> maskSheetName;

		LoadTileMap(backBuffer, spriteSheetName, maskSheetName);
	
		int width = 0;
		int height = 0;

		file >> width;
		file >> height;

		//Sint32 gData[LEVEL_WIDTH][LEVEL_HEIGHT];

		//Uint32 gData[TEST_WIDTH][TEST_HEIGHT] = { { 0 } };;

		gData.resize(width*height);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				file >> currentID;

				Tile* tileSprite = new Tile();
			
					//m_pTileMap->GetTileAt(currentID);
				Sprite* sprite = new Sprite();
				*sprite = *m_pTileMap->GetTileSpriteAt(currentID);

				if (tileSprite->Initialise(sprite));
				{

					tileSprite->SetX((x * 32) + 150);
					tileSprite->SetY((y * 32) + 100);

					m_levelSpriteTiles.push_back(tileSprite);
				}

				Tile* tileMask = new Tile();

				//m_pTileMap->GetTileAt(currentID);
				Sprite* mask = new Sprite();
				*mask = *m_pTileMapMask->GetTileSpriteAt(currentID);

				if (tileMask->Initialise(mask));
				{

					tileMask->SetX((x * 32) + 150);
					tileMask->SetY((y * 32) + 100);

					m_levelMaskTiles.push_back(tileMask);
				}
				

				//file >> gData[x+(y*width)];
			}
		}
	}

	

	//const int TOTAL_DATA = 1024;

	//Sint32 gData[TOTAL_DATA];

	//SDL_RWops* file = SDL_RWFromFile(LevelName, "r+b");

	//if (file != NULL)
	//{
	//	//Load data
	//	printf("Reading file...!\n");
	//	for (int i = 0; i < TOTAL_DATA; ++i)
	//	{
	//		SDL_RWread(file, &gData[i], sizeof(Sint32), 1);
	//	}

	//	//Close file handler
	//	SDL_RWclose(file);
	//}
	//else
	//{
	//
	//}

	//for (int i = 1; i < TOTAL_DATA; ++i)
	//{
	//	int x = (_Longlong)gData[i];
	//	int y = 0;
	//}

	return true;
}

bool
LevelManager::LoadTileMap(BackBuffer& backBuffer, const char* spriteSheet, const char* maskSheet)
{

	m_pTileMap = new TileMap();
	m_pTileMap->LoadTileSet(backBuffer, spriteSheet, false);

	m_pTileMapMask = new TileMap();
	m_pTileMapMask->LoadTileSet(backBuffer, maskSheet, true);

	return true;
}

void
LevelManager::Process(float deltaTime, ControllerPlayer& playerController)
{
	/*for each(Tile* t in m_levelMaskTiles)
	{
		t->Process(deltaTime);
	}*/

	float xStart = playerController.GetPlayer().GetPositionX();
	float xEnd = xStart + playerController.GetPlayer().GetWidth();
	float yStart = playerController.GetPlayer().GetPositionY();
	float yEnd = yStart + playerController.GetPlayer().GetHeight();

	for each(Tile* tSprite in m_levelSpriteTiles)
	{
		tSprite->Process(deltaTime);
	}

	for each(Tile* tMask in m_levelMaskTiles)
	{
		if (CheckTileCollisionOuter(*tMask, xStart, xEnd, yStart, yEnd))
		{
			if (CheckTileCollisionInner(*tMask, xStart, xEnd, yStart, yEnd))
			{
				playerController.StopPlayerVelocityX();
			}			
		}
		tMask->Process(deltaTime);
	}
}

void
LevelManager::Draw(BackBuffer& backBuffer)
{
	//for each(Tile* t in m_levelMaskTiles)
	//{
	//	t->Draw(backBuffer);
	//}

	for each(Tile* t in m_levelSpriteTiles)
	{
		t->Draw(backBuffer);
	}
}

vector<Tile*>
LevelManager::GetTilesSprite()
{
	return m_levelSpriteTiles;
}

vector<Tile*>
LevelManager::GetTilesMask()
{
	return m_levelMaskTiles;
}

bool
LevelManager::CheckTileCollisionOuter(Tile& tile, float xStart, float xEnd, float yStart, float yEnd)
{
	if (tile.GetX() >= xStart && tile.GetX() <= xEnd && tile.GetY() >= yStart && tile.GetY() <= yEnd)
		return true;
	else
		return false;
}

bool
LevelManager::CheckTileCollisionInner(Tile& tile, float xStart, float xEnd, float yStart, float yEnd)
{
	bool result = false;

	tile.GetSprite().LockTexture();

	Uint32* tilePixels = (Uint32*)tile.GetSprite().GetPixels();

	if (tile.GetX() >= xStart && tile.GetX() <= xEnd && tile.GetY() >= yStart && tile.GetY() <= yEnd)
		result = true;
	else
		result = false;


	tile.GetSprite().UnlockTexture();

	return result;
}