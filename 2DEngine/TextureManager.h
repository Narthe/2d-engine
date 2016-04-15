#include <stdio.h>
#include "SDL2\SDL.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	SDL_Surface* LoadBitmap(const std::string _path, SDL_Renderer *ren, SDL_Window * win);
	SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren);
	void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
};