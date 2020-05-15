#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_clipboard.h>
#include <stdio.h>
#include <stdbool.h>
#include "gameFunctions.h"
#include "gameObjects.h"
#include <time.h>
#include <stdint.h>
#include "debug.h"

void checkSurface(SDL_Surface *surface);
int main(int argc, char *argv[])
{
	bool running = true;	
	SDL_Window *window;  //Create the window to draw in
	SDL_Renderer *renderer; //Create the compiler which helps draw the screen
		SDL_Init(SDL_INIT_VIDEO); //Initialize the library used for displaying video im guessing
	TTF_Init(); //Initialize font library
	//Create the application window with settings
	//Parameters being passed in: Title of the window, Initial x position, Initial Y position
	window = SDL_CreateWindow("Game Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			0);
	//Create the Renderer? Last parameter combines both flags
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//Call a game object to write data to	
	gameState gameObject;

	//Initialize RNG by seeding with time
	srand(time(0));
	//Create rectangle to hold data for 
	rectangle rect = {120,120,32,32};
	gameObject.character.body = rect;
	gameObject.character.xSpeed = 3;
	gameObject.character.ySpeed = -3;
	gameObject.renderer = renderer;
	gameObject.character.onLedge = false;
	gameObject.character.jumps = 1;
	gameObject.fontTextures = NULL;
	gameObject.debug = false;
	gameObject.cameraOffset = 0;
	if (argc == 2){
	  printf("debug set to true");
		gameObject.debug = true;
	}

	loadHeartTexture(&gameObject);
	loadFont(&gameObject,"Lato-Regular.ttf");
	SDL_Surface *kid = IMG_Load("kidStanding.png");
	checkSurface(kid);
	gameObject.kidTextures[0] = SDL_CreateTextureFromSurface(renderer,kid);
	SDL_FreeSurface(kid);
	kid = IMG_Load("kidWalking.png");
	checkSurface(kid);
	gameObject.kidTextures[1] = SDL_CreateTextureFromSurface(renderer,kid);
	SDL_FreeSurface(kid);
//	for(int i = 0; i<20; i++)
//	{
//		//Create hearts in random locations
//		heart tmp = {rand()%640,rand()%480};
//		gameObject.hearts[i] = tmp;
//		//Create ledges
//		ledge tmpLedge = {i*64-10,400,64,20};
//		gameObject.ledges[i] = tmpLedge;
//		
//	}
	ledge firstLedge = {0,460,640,30,150,75,0};
	gameObject.ledges[0] = firstLedge;
	ledge secondLedge = {420,300,64,40,150,75,0};
	gameObject.ledges[1] = secondLedge;
		//Check for events while running
	uint32_t timeStepMs = 1000 / 60;
	uint32_t nextGameStep = SDL_GetTicks();
	while(running)
	{
	  //Get current time
		uint32_t now = SDL_GetTicks();
		if (nextGameStep <= now){
		  	int maxAdvancedFrames = 2;

			//Keep advancing logic until the time catches up
			while(nextGameStep <= now && (maxAdvancedFrames--)){
				running = manageEvents(window,&gameObject);
				detectCollision(&gameObject);
				gameObject.cameraOffset = -gameObject.character.body.x + 200;
				if (gameObject.cameraOffset > 0){
				  gameObject.cameraOffset = 0;
				}
				//advance the game by one tick
				nextGameStep += timeStepMs;
			}
			if(!gameObject.debug){
			  renderScreen(renderer,&gameObject);
			}else{
			  createDebugLabels(&gameObject);
			  renderScreen(renderer,&gameObject);
			  freeFontTextures(&gameObject);	
			}
		}
		else{
		  SDL_Delay(nextGameStep - now);
		}
	}

	//Destroy textures
	SDL_DestroyTexture(gameObject.heartTexture);
	SDL_DestroyTexture(gameObject.kidTextures[0]);
	SDL_DestroyTexture(gameObject.kidTextures[1]);
	freeFontTextures(&gameObject);	
	//Close and Destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//Close the font 
	TTF_CloseFont(gameObject.font);

	//Clean and quit
	SDL_Quit();
	TTF_Quit();
	return 0;
}

