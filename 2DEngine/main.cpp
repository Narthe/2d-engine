#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "res_path.h"

SDL_Window * SDL_WINDOW;
SDL_Renderer * SDL_RENDERER;

SDL_Surface* LoadBitmap(const std::string _path);
SDL_Texture * LoadTexture(SDL_Surface * _surf);
void paint(std::vector<SDL_Texture*> _textures);

int main(int argc, char** argv)
{
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* init window */
	SDL_WINDOW = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (SDL_WINDOW == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	/* init renderer */
	SDL_RENDERER = SDL_CreateRenderer(SDL_WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDL_RENDERER == nullptr) {
		SDL_DestroyWindow(SDL_WINDOW);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::string imagePath = getResourcePath("Bitmaps") + "hello.bmp";
	std::vector<SDL_Texture*> textures;

	SDL_Surface *bmp = LoadBitmap(imagePath);
	SDL_Texture *tex = LoadTexture(bmp);
	textures.push_back(tex);
	while (true)
	{
		paint(textures);
	}
	SDL_Quit();

	return 0;
}

SDL_Surface* LoadBitmap(const std::string _path)
{
	SDL_Surface * surface = SDL_LoadBMP(_path.c_str());
	if (surface == NULL) {
		SDL_DestroyRenderer(SDL_RENDERER);
		SDL_DestroyWindow(SDL_WINDOW);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return surface;
}

SDL_Texture * LoadTexture(SDL_Surface * _surf)
{
	SDL_Texture *tex = SDL_CreateTextureFromSurface(SDL_RENDERER, _surf);
	SDL_FreeSurface(_surf);
	if (tex == NULL) {
		SDL_DestroyRenderer(SDL_RENDERER);
		SDL_DestroyWindow(SDL_WINDOW);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return tex;
}

void paint(std::vector<SDL_Texture*> _textures)
{
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		for each (SDL_Texture* tex in _textures)
		{
			//First clear the renderer
			SDL_RenderClear(SDL_RENDERER);
			//Draw the texture
			SDL_RenderCopy(SDL_RENDERER, tex, NULL, NULL);
			//Update the screen
			SDL_RenderPresent(SDL_RENDERER);
			//Take a quick break after all that hard work
			//SDL_Delay(1000);
		}
	}
}