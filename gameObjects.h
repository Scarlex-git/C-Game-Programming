#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
//Simple Rectangle with x y coordinates and area
typedef struct 
{
	float x,y;
	int width,height;
}rectangle;
//Platform for a person to walk onto
typedef struct{
	int x,y;
}heart;
//Structure for a person to walk on
typedef struct{
	int x,y,width,height;
	int r,g,b;
}ledge;
typedef struct{
	rectangle body; 
	float xSpeed,ySpeed;
	bool onLedge;
	int jumps;
	int jumpTimer;
}kid;
//List
typedef struct textureNode{
  SDL_Texture *texture;
  rectangle rect;
  struct textureNode *next;
}textureNode;
/*
 *
 * Create variable with every possible object we could have for the game
 * Allows ordering to be put through a list
 */
typedef struct
{
	rectangle rect;
	kid character;
	heart hearts[20];
	ledge ledges[20];
	SDL_Texture *heartTexture;
	SDL_Texture *kidTextures[2];
	SDL_Renderer *renderer;
	int speed;
	TTF_Font *font;
	textureNode *fontTextures;
	bool debug;
}gameState;

void loadHeartTexture(gameState *object);
void checkSurface(SDL_Surface *surface);
void loadFont(gameState *gameObj,char *fontName);
#endif
