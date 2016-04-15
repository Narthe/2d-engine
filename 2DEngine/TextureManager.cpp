#include <string>
#include <iostream>
#include "cleanup.h"
#include "TextureManager.h"
#include "SDL2\SDL_image.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

SDL_Surface* TextureManager::LoadBitmap(const std::string _file, SDL_Renderer *ren, SDL_Window * win)
{
	SDL_Surface * surface = SDL_LoadBMP(_file.c_str());
	if (surface == nullptr) {
		cleanup(win, ren);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return surface;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* TextureManager::LoadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void TextureManager::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void TextureManager::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	RenderTexture(tex, ren, x, y, w, h);
}