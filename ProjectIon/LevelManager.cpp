// This Include:
#include "LevelManager.h"

// Local Includes:

#include "TileMap.h"
#include "Tile.h"
#include "Texture.h"
#include "Sprite.h"

#include <SDL.h>

#include <iostream>
#include <string>
#include <fstream>

#include <Box2D\Box2D.h>

#include <vector>

using namespace std;
//const int LEVEL_WIDTH = 1920;
//const int LEVEL_HEIGHT = 1080;
//const int TEST_WIDTH = 640;
//const int TEST_HEIGHT = 480;


#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

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

	float playerX = playerController.GetPlayer().GetPositionX();
	float playerY = playerController.GetPlayer().GetPositionY();
	float playerWidth = playerController.GetPlayer().GetWidth();
	float playerHeight = playerController.GetPlayer().GetHeight();

	SDL_Rect entity = { playerX, playerY, playerWidth, playerHeight };
	

	for each(Tile* tSprite in m_levelSpriteTiles)
	{
		tSprite->Process(deltaTime);
	}

	for each(Tile* tMask in m_levelMaskTiles)
	{
		SDL_Rect tile = { tMask->GetX(), tMask->GetY(), 32, 32 };

		if (CheckTileCollision(*tMask, entity, tile))
		{
			b2Body& body = *playerController.GetPlayer().GetBody();
			b2Vec2 velocity = body.GetLinearVelocity();

			if (velocity.x > 0 && tile.x > entity.x && tile.y <= entity.y)
			{
				playerController.StopPlayerVelocityX();
			}
			if (velocity.x < 0 && tile.x < entity.x && tile.y <= entity.y)
			{
				playerController.StopPlayerVelocityX();
			}

			
			/*if (CheckTilePosition(entity, tile) == 0)
			{
				playerController.StopPlayerVelocityX();
			}
			else if (CheckTilePosition(entity, tile) == 1)
			{
				playerController.StopPlayerVelocityX();
			}
			else if (CheckTilePosition(entity, tile) == 2)
			{
				playerController.StopPlayerVelocityY();
			}
			else if (CheckTilePosition(entity, tile) == 3)
			{
				playerController.StopPlayerVelocityY();
			}*/

				// playerController.StopPlayerVelocityX();
				playerController.StopPlayerVelocityY();		
				
		}
		tMask->Process(deltaTime);
	}
}

void
LevelManager::Draw(BackBuffer& backBuffer)
{
	/*for each(Tile* t in m_levelMaskTiles)
	{
		t->Draw(backBuffer);
	}*/

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
LevelManager::CheckTileCollision(Tile& tile, const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
	bool result = false;;

	SDL_Rect collisionRect = Intersection(boundsA, boundsB);

	if (collisionRect.w == 0 && collisionRect.h == 0)
		return result;

	tile.GetSprite().LockTexture();
	Uint32* pixels = (Uint32*)tile.GetSprite().GetPixels();

	int pitch = tile.GetSprite().GetPitch();

	float height = tile.GetSprite().GetHeight();
	float width = tile.GetSprite().GetWidth();

	int Position = CheckTilePosition(boundsA, boundsB);

	/*
	Check Postion Where
	  0 = TopLeft
	  1 = TopRight
	  2 = BottomLeft
	  3 = BottomRight
	*/
	int collisionX = 0;
	int collisionY = 0;
	int collisionHeight = 0;
	int collisionWidth = 0;

	if (Position == 0)
	{
		collisionX = 0;
		collisionY = 0;
		collisionWidth = collisionRect.w;
		collisionHeight = collisionRect.h;
		
	}
	else if (Position == 1)
	{
		collisionX = 32 - collisionRect.w;
		collisionY = 0;
		
		collisionWidth = width;
		collisionHeight = collisionRect.h;
	}
	else if (Position == 2)
	{
		collisionX = 0;
		collisionY = 32 - collisionRect.h;
		collisionWidth = collisionWidth;
		collisionHeight = height;
	}
	else if (Position == 3)
	{
		collisionX = 32 - collisionRect.w;
		collisionY = 32 - collisionRect.h;
		collisionWidth = width;
		collisionHeight = height;
	}

	for (int y = collisionY; y < collisionHeight; y++)
	for (int x = collisionX; x < collisionWidth; x++)
	if (GetAlphaXY(pixels, x, y * height)) //&& GetAlphaXY(pixels, +x, (y * height)))
		result = true;
	
	if (result != true)
		result = false;
		
	/*for (int y = 0; y < collisionRect.h; y++)
		for (int x = 0; x < collisionRect.w; x++)
			if (GetAlphaXY(pixels, x, y))
				return true;*/



	//for (int y = 0; y < height; y++)
	//	for (int x = 0; x < width; x++)
	//		if (GetAlphaXY(pixels, x, (y * height))) //&& GetAlphaXY(pixels, +x, (y * height)))
	//			return true;


	tile.GetSprite().UnlockTexture();

	return result;
}

int
LevelManager::CheckTilePosition(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
	bool GreaterX = false;
	bool GreaterY = false;

	if (boundsA.x >= boundsB.x)
		GreaterX = true;

	if (boundsA.y >= boundsB.y)
		GreaterY = true;

	if (GreaterX)
	{
		if (GreaterY)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (GreaterY)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}


	return 0;
}


SDL_Rect 
LevelManager::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
	int x1 = Maximum(boundsA.x, boundsB.x);
	int y1 = Maximum(boundsA.y, boundsB.y);
	int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
	int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

	int width = x2 - x1;
	int height = y2 - y1;

	if (width > 0 && height > 0)
	{
		SDL_Rect intersect = { x1, y1, width, height };
		return intersect;
	}
	else
	{
		SDL_Rect intersect = { 0, 0, 0, 0 };
		return intersect;
	}
}

bool 
LevelManager::GetAlphaXY(Uint32* pixels, int x, int y)
{
	//Uint32 pixelColor = (Uint32)pixels + y * 128 + x * 32;
	

	//int bpp = entity->surface->format->BytesPerPixel;
	//Uint8* p = (Uint8*)entity->surface->pixels + y * entity->surface->pitch + x * bpp;
	//Uint32 pixelColor;

	/*switch (bpp)
	{
	case(1) :
		pixelColor = *p;
		break;
	case(2) :
		pixelColor = *(Uint16*)p;
		break;
	case(3) :
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixelColor = p[0] << 16 | p[1] << 8 | p[2];
		else
			pixelColor = p[0] | p[1] << 8 | p[2] << 16;
		break;
	case(4) :
		pixelColor = *(Uint32*)p;
		break;
	}*/

	//Uint8 red, green, blue, alpha;
	//SDL_GetRGBA(pixelColor, entity->surface->format, &red, &green, &blue, &alpha);
	
	
	
	Uint32 pixel = pixels[x + y];
	return pixel != 12599360;

	//return pixelColor != 12599360;
}