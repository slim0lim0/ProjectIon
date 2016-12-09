#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//Library includes:
#include <SDL.h>

class Texture
{

	//Member Methods
public:
	Texture();
	~Texture();

	bool Initialise(const char* pcFilename, SDL_Renderer* pRenderer);
	bool Initialise(const char* pcFilename, SDL_Window* pWindow, SDL_Renderer* pRenderer);
	bool Initialise(SDL_Texture* pTexture);

	int GetWidth() const;
	int GetHeight() const;

	void* GetPixels();
	int GetPitch();

	SDL_Texture* GetTexture();

	bool LockTexture();
	bool UnlockTexture();

protected:

private:
	Texture(const Texture& texture);
	Texture& operator=(const Texture& texture);

	//Member Data:
public:

protected:
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;
	SDL_Texture* m_pTexture;

	int m_iWidth;
	int m_iHeight;

	void* m_pixels;
	int m_pitch;

	SDL_RendererFlip m_flip;

private:

};

#endif