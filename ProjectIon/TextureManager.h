#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

//Library Inlcudes:
#include <string>
#include <map>
#include <SDL.h>

using namespace std;

//Forward Declarations:
class Texture;
struct SDL_Renderer;
struct SDL_Window;

class TextureManager
{
	//Member Methods:
public:
	TextureManager();
	~TextureManager();

	bool Initialise(SDL_Window* pWindow,SDL_Renderer* pRenderer);

	Texture* GetTexture(const char* pcFileName);
	Texture* GetTexture(const char* pcFileName, bool isStreamable);
	Texture* GetTexture(SDL_Texture* texture, const char* storeName);
	
protected:

private:
	TextureManager(const TextureManager& oTextureManager);
	TextureManager& operator=(const TextureManager& oTextureMaanger);

	//Member Data:

public:

protected:

private:
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;
	map<string, Texture*> m_pLoadedTextures;
	
};



#endif