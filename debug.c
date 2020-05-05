#include "debug.h"

void createPositionLabel(gameState *gameObj){
  	//Create two labels for the kid's x and y position
	SDL_Rect labelRect = {0,10,200,42};
	SDL_Color color = {255,255,255};
	char *xText = malloc(sizeof(char)*30); 
	sprintf(xText,"X: %i",(int)gameObj->character.body.x);
	char *yText = malloc(sizeof(char)*30); 
	sprintf(yText,"Y: %i",(int)gameObj->character.body.y);
	SDL_Surface *x = TTF_RenderText_Blended(gameObj->font,xText,color);
	SDL_Surface *y = TTF_RenderText_Blended(gameObj->font,yText,color);
	loadTextureNode(gameObj,x);
	loadTextureNode(gameObj,y);
	free(xText);
	free(yText);
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
