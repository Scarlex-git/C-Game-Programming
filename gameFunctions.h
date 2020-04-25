#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameObjects.h"

//Manage events for the game like moving an object
bool manageEvents(SDL_Window *window, gameState *gameObj);
//Render the objects on the screen
void renderScreen(SDL_Renderer *renderer, gameState *gameObj);
void detectCollision(gameState *gameObj);

#endif
