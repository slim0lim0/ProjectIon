#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <SDL.h>

//Forward Declarations:

class TextureManager;
class Sprite;

class BackBuffer
{
	//Member Methods
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawSprite(Sprite& sprite);
	void DrawSprite(Sprite& sprite, bool IsCameraControlled, bool IsCameraTrack);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);

	int GetPixels(Sprite& sprite);
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	Sprite* CreateSprite(const char* pcFilename);
	Sprite* CreateSprite(const char* pcFilename, bool isStreamable);
	Sprite* CreateSprite(SDL_Texture* texture, const char* storeName);

	SDL_Texture* ClipTexture(int width, int height, void* pixels, int pitch, bool IsMask);

	void SetCamera(int CamX, int CamY, int CamWidth, int CamHeight);

protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data

public:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearBlue;
	unsigned char m_clearGreen;
};

#endif // __BACKBUFFER_H__