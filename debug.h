#ifndef DEBUGGING_H
#define DEBUGGING_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "gameObjects.h"
void createDebugLabels(gameState *gameObj);
void insertNode(gameState *gameObj,textureNode *item);
void loadTextureNode(gameState *gameObj,SDL_Surface *surface);
void drawDebugLabels(gameState *gameObj);
void freeFontTextures(gameState *gameObj);
#endif
