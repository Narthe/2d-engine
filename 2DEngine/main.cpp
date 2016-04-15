#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "res_path.h"
#include "TextureManager.h"
#include "cleanup.h"

SDL_Window * SDL_WINDOW;
SDL_Renderer * SDL_RENDERER;
TextureManager * TEXTURE_MGR;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//We'll just be using square tiles for now
const int TILE_SIZE = 40;

void paint(std::vector<SDL_Texture*> _textures);

void initManagers()
{
	TEXTURE_MGR = new TextureManager();
}

int main(int argc, char** argv)
{
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* init window */
	SDL_WINDOW = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	const std::string resPath = getResourcePath("Bitmaps");
	SDL_Texture *background = TEXTURE_MGR->LoadTexture(resPath + "background.png", SDL_RENDERER);
		SDL_Texture *image = TEXTURE_MGR->LoadTexture(resPath + "image.png", SDL_RENDERER);
	if (background == NULL || image == NULL) {
		cleanup(background, SDL_RENDERER, SDL_WINDOW);
		SDL_Quit();
		return 1;
	}
	
	std::vector<SDL_Texture*> textures;
	//textures.push_back(image);
	textures.push_back(background);
	
	
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	while (true)
	{
		/*Render background*/
		int bW, bH;
		SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
		TEXTURE_MGR->RenderTexture(background, SDL_RENDERER, 0, 0);
		TEXTURE_MGR->RenderTexture(background, SDL_RENDERER, bW, 0);
		TEXTURE_MGR->RenderTexture(background, SDL_RENDERER, 0, bH);
		TEXTURE_MGR->RenderTexture(background, SDL_RENDERER, bW, bH);

		int iW, iH;
		SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
		int x = SCREEN_WIDTH / 2 - iW / 2;
		int y = SCREEN_HEIGHT / 2 - iH / 2;
		TEXTURE_MGR->RenderTexture(image, SDL_RENDERER, x, y);

		SDL_RenderPresent(SDL_RENDERER);
		SDL_Delay(1000);

		SDL_RenderPresent(SDL_RENDERER);
		SDL_Delay(1000);

		SDL_RenderPresent(SDL_RENDERER);
		SDL_Delay(1000);
	}
	for each (SDL_Texture* tex in textures)
	{
		cleanup(tex);
	}
	cleanup(SDL_WINDOW, SDL_RENDERER);
	SDL_Quit();

	return 0;
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
