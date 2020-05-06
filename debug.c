#include "debug.h"

void createDebugLabels(gameState *gameObj){
  	//Create two labels for the kid's x and y position
	SDL_Rect labelRect = {0,10,200,42};
	SDL_Color color = {255,255,255};
	char *xText = malloc(sizeof(char)*12); 
	sprintf(xText,"X: %i",(int)gameObj->character.body.x);
	char *yText = malloc(sizeof(char)*12); 
	sprintf(yText,"Y: %i",(int)gameObj->character.body.y);
	char *ySpeedText = malloc(sizeof(char)*12); 
	sprintf(ySpeedText,"Y Speed: %i",(int)gameObj->character.ySpeed);
	char *xSpeedText = malloc(sizeof(char)*12); 
	sprintf(xSpeedText,"X Speed: %i",(int)gameObj->character.xSpeed);
	char *onLedgeText = malloc(sizeof(char)*12); 
	sprintf(onLedgeText,"On Ledge: %s",gameObj->character.onLedge?"true":"false");
	SDL_Surface *x = TTF_RenderText_Blended(gameObj->font,xText,color);
	SDL_Surface *y = TTF_RenderText_Blended(gameObj->font,yText,color);
	SDL_Surface *xSpeed = TTF_RenderText_Blended(gameObj->font,xSpeedText,color);
	SDL_Surface *ySpeed = TTF_RenderText_Blended(gameObj->font,ySpeedText,color);
	SDL_Surface *onLedge = TTF_RenderText_Blended(gameObj->font,onLedgeText,color);
	loadTextureNode(gameObj,x);
	loadTextureNode(gameObj,y);
	loadTextureNode(gameObj,xSpeed);
	loadTextureNode(gameObj,ySpeed);
	loadTextureNode(gameObj,onLedge);
	free(xText);
	free(yText);
	free(xSpeedText);
	free(ySpeedText);
	free(onLedgeText);
}

void loadTextureNode(gameState *gameObj,SDL_Surface *surface){
  	textureNode *tmp = malloc(sizeof(textureNode));
	if (tmp ==NULL){
	  printf("could not load textureNode correctly\n");
	}
	SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(gameObj->renderer,surface);
	tmp->texture = tmpTexture;
	tmp->rect.width = surface->w;
	tmp->rect.height = surface->h;
	insertNode(gameObj,tmp);
}

void insertNode(gameState *gameObj,textureNode *item){
  //Keep looping over the list until the next item is null (base case)
  textureNode *list = gameObj->fontTextures;
  if(list == NULL){
	gameObj->fontTextures = item;
	item->next = NULL;
	return;
  }
  while(list->next != NULL){
	list = list->next;
  }
  list->next = item;
  item->next = NULL;
  return;
}

	
void drawDebugLabels(gameState *gameObj){
  textureNode *item = gameObj->fontTextures;
  //printf("drawing?\n");
  int y = 20;
  while(item != NULL){
  	//printf("attempting to draw debug\n");
	SDL_Rect textRect = {0,y,item->rect.width,item->rect.height};
	SDL_RenderCopy(gameObj->renderer,item->texture,NULL,&textRect);
	item = item->next;
	y +=20;
  }
  return;
}
void freeFontTextures(gameState *gameObj){
  textureNode *list =  gameObj->fontTextures;
  while(list != NULL){
	//printf("freeing texture\n");
	  textureNode *tmp = list->next;
	  SDL_DestroyTexture(list->texture);
	  free(list);
	  list = tmp;
	}
	gameObj->fontTextures = NULL;
}
