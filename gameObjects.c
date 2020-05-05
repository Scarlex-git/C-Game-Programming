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
void loadFont(gameState *gameObj,char *fontName){
  //Open and store the font, if not found exit the game
	gameObj->font = TTF_OpenFont(fontName,24);  
	if(gameObj->font == NULL){
	  printf("Couldn't open font %s",fontName);
	  exit(1);
	}
	//printf("Loaded font correctly");

}
