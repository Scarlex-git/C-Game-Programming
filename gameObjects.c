#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameObjects.h"
void loadHeartTexture(gameState *object)
{
	//Open image similar to fopen
	SDL_Surface *surface = IMG_Load("heart.png");
	//Check if heart is loaded correctly
	checkSurface(surface);
	object->heartTexture = SDL_CreateTextureFromSurface(object->renderer,surface);
	//Free the memory from the heart surface (cause malloc)
	SDL_FreeSurface(surface);

}
void checkSurface(SDL_Surface *surface)
{
	if (!surface)
	{
		printf("surface was not loaded corrctly\n");	
		SDL_Quit();
		exit(1);
	}
}
	
