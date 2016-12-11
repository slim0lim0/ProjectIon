//This Include
#include "BackBuffer.h"

//Local Includes
#include "LogManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Texture.h"

//Library Includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

SDL_Rect* m_pCamera;

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0x40)
, m_clearBlue(0xC0)
, m_clearGreen(0x40)
{

}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	IMG_Quit();
	SDL_Quit();
}

bool
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	m_pCamera = new SDL_Rect();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LogSDLError();
		return(false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("JWJ 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		
		if (m_pWindow == 0)
		{
			LogSDLError();
			return(false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return(false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return(false);
				}
			}
		}
	}

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pWindow, m_pRenderer);

	m_pCamera = new SDL_Rect();

	return(true);
}

void
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
}

void
BackBuffer::DrawSprite(Sprite& sprite, bool IsCameraControl, bool IsCameraTrack)
{
	SDL_Rect dest;
	SDL_Rect src;
	if (IsCameraControl)
	{
		src.x = m_pCamera->x;
		src.y = m_pCamera->y;
		src.w = m_pCamera->w;
		src.h = m_pCamera->h;

		if (IsCameraTrack)
		{
			dest.x = sprite.GetX() - m_pCamera->x;
			dest.y = sprite.GetY() - m_pCamera->y;
		}
		else
		{
			dest.x = sprite.GetX();
			dest.y = sprite.GetY();
		}
		dest.w = sprite.GetWidth();
		dest.h = sprite.GetHeight();


		SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &src, &dest);

	}
	else
	{


		if (IsCameraTrack)
		{
			dest.x = sprite.GetX() - m_pCamera->x;
			dest.y = sprite.GetY() - m_pCamera->y;
		}
		else
		{
			dest.x = sprite.GetX();
			dest.y = sprite.GetY();
		}
		dest.w = sprite.GetWidth();
		dest.h = sprite.GetHeight();

		SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
	}
	
}

// Draw Animated Sprite

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;

	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2 - x1;
	fillRect.h = y2 - y1;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite*
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}


Sprite*
BackBuffer::CreateSprite(const char* pcFilename, bool isStreamable)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename, isStreamable);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

Sprite*
BackBuffer::CreateSprite(SDL_Texture* texture, const char* storeName)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(texture, storeName);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}

void
BackBuffer::SetCamera(int CamX, int CamY, int CamWidth, int CamHeight)
{
	m_pCamera->x = CamX;
	m_pCamera->y = CamY;
	m_pCamera->w = CamWidth;
	m_pCamera->h = CamHeight;
}

SDL_Window*
BackBuffer::GetWindow()
{
	return(m_pWindow);
}
SDL_Renderer*
BackBuffer::GetRenderer()
{
	return(m_pRenderer);
}

SDL_Texture*
BackBuffer::ClipTexture(int width, int height, void* pixels, int pitch, bool IsMask)
{
	SDL_Surface* loadedSurface = NULL;
	int depth = pitch / 4;

	if(!IsMask)
	{
		
		loadedSurface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, 0, 0, 0, 255);
		Uint32 colorToChange = SDL_MapRGB(SDL_GetWindowSurface(GetWindow())->format, 0x40, 0x40, 0xC0);
		SDL_SetColorKey(loadedSurface, SDL_TRUE, colorToChange);
	}
	else
	{
		loadedSurface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, 0, 0, 0, 0);
	}


	//SDL_Texture* texture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetRenderer(), loadedSurface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	/*SDL_SetRenderTarget(pRenderer, texture);
	SDL_RenderCopy(pRenderer, texture, &rect, NULL);*/

	//SDL_UpdateTexture(texture, NULL, pixels, pitch);
	SDL_QueryTexture(texture, 0, 0, &width, &height);

	//SDL_SetRenderTarget(pRenderer, NULL);
	// pixels, width, height, depth(256), pitch, 0, 0, 0, 0
	//SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rMask, gMask, bMask, aMask);
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	return texture;
}
