#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "gameFunctions.h"
#include "debug.h"
bool manageEvents(SDL_Window *window, gameState *gameObj)
{
	//Create event variable
	SDL_Event event;
	//Variable to pass back to the main function to determine if to run or not
	bool running = true;
	while(SDL_PollEvent(&event))	
	{
		//Check category of the event
		switch (event.type)
		{
			case SDL_WINDOWEVENT_CLOSE:
				//Check for window
				if (window)
				{
					printf("window close event recieves\n");
					SDL_DestroyWindow(window);
					window = NULL;
					running = false;
				}
				break;
			case SDL_KEYDOWN:
				//Check what key was being pressed through gettings its code
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						printf("Setting false in escape\n");
						running = false;
						break;
					case SDLK_LSHIFT:
						if (gameObj->character.jumps > 0){
							if (gameObj->character.jumps == 2){gameObj->character.ySpeed = 8;}
							else if (gameObj->character.jumps == 1){gameObj->character.ySpeed = 6;}
							gameObj->character.jumpTimer = 0;
							gameObj->character.jumps -= 1;
							printf("jumps left: %i\n",gameObj->character.jumps);
						}
						break;		
					
						
				}
				break;
			case SDL_QUIT:
				running = false;
				break;
		}
	}
	//Retunrs a list of points, where we can scan keys at one time
	//Uses scancode sdlk
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	//Apply movement to the character
	
	gameObj->character.body.y -= gameObj->character.ySpeed;
	//Slow down the character
	if(gameObj->character.ySpeed != -5){
		gameObj->character.ySpeed -= .7;
		//catch if going faster
		if (gameObj->character.ySpeed <= -5){
			gameObj->character.ySpeed = -5;
		}
	}	
	if(gameObj->character.xSpeed != 0){gameObj->character.xSpeed = 0;}
	if(state[SDL_SCANCODE_LEFT]){
		gameObj->character.xSpeed = -3;
		gameObj->character.body.x += gameObj->character.xSpeed;
	}
	if(state[SDL_SCANCODE_RIGHT]){
		gameObj->character.xSpeed = 3;
		gameObj->character.body.x += gameObj->character.xSpeed;	
	}
	if(state[SDL_SCANCODE_LSHIFT]){
		if (gameObj->character.jumpTimer < 30){
			gameObj->character.ySpeed += .5;
			gameObj->character.jumpTimer += 1;
		}
	}else{
		  gameObj->character.jumpTimer = 50;
	}
	return running;
}
void renderScreen(SDL_Renderer *renderer, gameState *gameObj)
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(renderer,60,60,60,255);

	//Clear the screen
	SDL_RenderClear(renderer);
	
	//Set drawing color to white
	SDL_SetRenderDrawColor(renderer,43,43,43,255);
	//Create a rectangle and call function in order to draw rectangle
	SDL_Rect body = {gameObj->character.body.x,gameObj->character.body.y,gameObj->character.body.width,gameObj->character.body.height};
	SDL_RenderCopyEx(gameObj->renderer,gameObj->kidTextures[0],NULL,&body,0,NULL,0);
	for(int i = 0; i < 2; i++){
		//SDL_Rect heart = {gameObj->hearts[i].x,gameObj->hearts[i].y,64,64};
		//SDL_RenderCopy(renderer,gameObj->heartTexture,NULL,&heart);
		SDL_Rect shape = {gameObj->ledges[i].x,gameObj->ledges[i].y,gameObj->ledges[i].width,gameObj->ledges[i].height};
		SDL_SetRenderDrawColor(renderer,gameObj->ledges[i].r,gameObj->ledges[i].g,gameObj->ledges[i].b,255);
		SDL_RenderFillRect(renderer,&shape);
	}

	//Render the surface with the renderer, object (sdl_texture), null(not fully sure), and dimensions
	//printf("X: %3.f,Y: %3.f\n",gameObj->character.body.x,gameObj->character.body.y);
	if(gameObj->debug){
	  drawDebugLabels(gameObj);
	}
	SDL_RenderPresent(renderer);

}
void detectCollision(gameState *gameObj){
	//Define width of the kid
	float kw = gameObj->character.body.width, kh = gameObj->character.body.height; 
	//Define position of the kid
	float kx = gameObj->character.body.x, ky = gameObj->character.body.y;
	gameObj->character.onLedge = false;
	for (int i = 0; i < 2;i++){
		float pw = gameObj->ledges[i].width;
		float ph = gameObj->ledges[i].height;
		float px = gameObj->ledges[i].x;
		float py = gameObj->ledges[i].y;
		gameObj->ledges[i].r = 120;

	  //Colliding with the right of ledge
	  // First condition: is the object's bottom below the platform's top?
	  // Second condition: is the object's top above the platform's bottom?
	  // Conclusion: the object is inside the platform's top side
	  if (ky+kh > py && ky<py+ph){
		  //Colliding with the right of ledge
		  //First condition: Is the object's left before the platform's right?
		  //Second condition: Is the object's right after the platform's right?
		  //Conclusion: object is inside the platform's right side
		  if (kx < px+pw && kx + kw > px + pw && gameObj->character.xSpeed < 0){
			  gameObj->character.body.x = px + pw;
			  kx = px + pw;
			  gameObj->character.xSpeed = 0;
			  break;
		  }
		  //Colliding with the left of ledge
		  //First condition: is the object's rightmost position beyond the ledge's left?
		  //Second condition: is the object's leftmost position before ledge's left?
		  //Conclusion: the object's left and right bounds are between the left side of platform
		  else if(kx + kw > px && kx < px && gameObj->character.xSpeed > 0){
			  gameObj->character.body.x = px - kw;
			  kx = px - kw;
			  gameObj->character.xSpeed = 0;
			  break;
		  }

	  }		
	  //First condition: is the object's rightside beyond the left of the platform?
	  //Second condition: is the object's leftside before the right of the platform?
	  //Conclusion: the object's inbetween the platform (but not inside confirmed)
	  if (kx + kw/2 > px && kx+kw/2 < px + pw){
		  //First condition: is the object's top above the platform's bottom?
		  //Second condition: is the object's top above  the platform's top?
		  //Conclusion: The object's head is inbetween the platform
		  if(gameObj->character.ySpeed > 0 && ky < py + ph && ky > py){
			  gameObj->character.body.y = py + ph;
			  ky = py + ph;
			  gameObj->character.ySpeed = 0;
		  }

		  //Object's lower half is inside the top of platform
		  if (gameObj->character.ySpeed < 0 && ky + kh > py && ky < py){
			gameObj->character.body.y = py - kh;
			gameObj->character.ySpeed = -0.001;
			gameObj->character.onLedge = true;
			ky = py - kh;
			gameObj->character.jumps = 2;
			//currentlyOnPlatform = true;
			//printf("on ledge\n");
			gameObj->ledges[i].r = 255;
		}
		//If in freefall, give only one jump
				
	  }
  }
	//Check if the character is standing on a ledge. If not, reduce his jumps to 0/1 depending on if used already
  	if (!gameObj->character.onLedge && gameObj->character.ySpeed < 0 && gameObj->character.jumps != 0){
			//Check if previously on ledge, and the collision was made by this platform
			gameObj->character.jumps = (gameObj->character.jumps)?1:0;
	}
}


