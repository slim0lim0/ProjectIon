// This Includes:
#include "texturemanager.h"

// Local includes:
#include "texture.h"

// Library includes:
#include <SDL.h>

TextureManager::TextureManager()
: m_pRenderer(0)
{

}

TextureManager::~TextureManager()
{

}

bool
TextureManager::Initialise(SDL_Window* pWindow, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pWindow = pWindow;

	return(true);
}


Texture*
TextureManager::GetTexture(const char* pcFileName)
{
	Texture* pTexture = 0;


	if (m_pLoadedTextures.find(pcFileName) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...

		pTexture = new Texture();

		if (!pTexture->Initialise(pcFileName, m_pRenderer))
		{

		}

		m_pLoadedTextures[pcFileName] = pTexture;

	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[pcFileName];
	}

	return pTexture;
}

Texture*
TextureManager::GetTexture(SDL_Texture* texture, const char* storeName)
{
	Texture* pTexture = 0;

	if (m_pLoadedTextures.find(storeName) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...

		pTexture = new Texture();

		if (!pTexture->Initialise(texture))
		{

		}

		m_pLoadedTextures[storeName] = pTexture;

	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[storeName];
	}

	return pTexture;
}


Texture*
TextureManager::GetTexture(const char* pcFileName, bool isStreamable)
{
	Texture* pTexture = 0;


	if (m_pLoadedTextures.find(pcFileName) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...

		pTexture = new Texture();
		if (isStreamable)
		{
			if (!pTexture->Initialise(pcFileName, m_pWindow,  m_pRenderer))
			{

			}
		}
		else
		{
			if (!pTexture->Initialise(pcFileName, m_pRenderer))
			{

			}
		}
		

		m_pLoadedTextures[pcFileName] = pTexture;

	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[pcFileName];
	}

	return pTexture;
}