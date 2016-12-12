//Texture Class:
//	Initialise - When creating the object, initialises the renderer so that the texture can be drawn.
//  Get Width - Gets the current width of the teture.
// Get Height - Get sthe current hegiht of the texture.
// Get Texture - Returns this texture as a pointer.



// This include:
#include "texture.h"

// Local includes:
//#include "logmanager.h"

// Library include:
#include <SDL_image.h>
#include <cassert>
#include <string>




Texture::Texture()
: m_pTexture(0)
, m_iHeight(0)
, m_iWidth(0)
{
	m_flip = SDL_FLIP_NONE;
}


Texture::~Texture()
{

}

bool
Texture::Initialise(const char* pcFileName, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SDL_Surface* pSurface = IMG_Load(pcFileName);
	
	if (pSurface == 0)
	{
		//LogManager::GetInstance().Log("Image File Failed to Load!");
		return (false);
	}

	else
	{
		Uint32 colorKey = SDL_MapRGB(pSurface->format, 0x40, 0x40, 0xC0);
		SDL_SetColorKey(pSurface, 1, colorKey);
		//SDL_Surface* formattedSurface = SDL_ConvertSurface(pSurface, SDL_GetWindowSurface(m_pWindow)->format, NULL);

		//m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_GetWindowPixelFormat(m_pWindow), SDL_TEXTUREACCESS_STREAMING, pSurface->w, pSurface->h);

		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);

		if (m_pTexture == 0)
		{
			//LogManager::GetInstance().Log("Texture Failed to Create!");
			return (false);
		}

		SDL_FreeSurface(pSurface);
	}

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_iWidth, &m_iHeight);

	return (m_pTexture != 0);

}

bool
Texture::Initialise(SDL_Texture* pTexture)
{
	m_pTexture = pTexture;

	if (m_pTexture == 0)
	{
		//LogManager::GetInstance().Log("Texture Failed to Create!");
		return (false);
	}

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_iWidth, &m_iHeight);

	return (m_pTexture != 0);
}

bool
Texture::Initialise(const char* pcFileName, SDL_Window* pWindow, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pWindow = pWindow;

	SDL_Surface* pSurface = IMG_Load(pcFileName);
	if (pSurface == 0)
	{
		//LogManager::GetInstance().Log("Image File Failed to Load!");
		return (false);
	}

	else
	{
		SDL_Surface* formattedSurface = SDL_ConvertSurface(pSurface, SDL_GetWindowSurface(m_pWindow)->format, NULL);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0x40, 0x40, 0xC0);
			SDL_SetColorKey(formattedSurface, 1, colorKey);
			
			m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_GetWindowPixelFormat(m_pWindow), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
	
			if (m_pTexture == 0)
			{
				//LogManager::GetInstance().Log("Texture Failed to Create!");
				return (false);
			}
			else
			{
				void* pixels;
				int pitch;
				//Lock texture for manipulation
				SDL_LockTexture(m_pTexture, NULL, &pixels, &pitch);

				//Copy loaded/formatted surface pixels
				memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Unlock texture to update
				SDL_UnlockTexture(m_pTexture);
				pixels = NULL;

				//Get image dimensions
				m_iHeight = formattedSurface->w;
				m_iWidth = formattedSurface->h;
			}


			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}


		SDL_FreeSurface(pSurface);
	}

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_iWidth, &m_iHeight);

	return (m_pTexture != 0);

}

bool
Texture::LockTexture()
{
	bool success = true;

	//Texture is already locked
	if (m_pixels != NULL)
	{
		//printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(GetTexture(), NULL, &m_pixels, &m_pitch) != 0)
		{
			std::string s = SDL_GetError();
			success = false;
		}
	}

	return success;
}

bool
Texture::UnlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (m_pixels == NULL)
	{
		//printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(GetTexture());
		m_pixels = NULL;
		m_pitch = 0;
	}

	return success;
}

void* 
Texture::GetPixels()
{
	return m_pixels;
}

int
Texture::GetPitch()
{
	return m_pitch;
}


int
Texture::GetWidth() const
{
	assert(m_iWidth);
	return (m_iWidth);
}


int
Texture::GetHeight() const
{
	assert(m_iHeight);
	return (m_iHeight);
}

SDL_Texture*
Texture::GetTexture()
{
	return (m_pTexture);
}