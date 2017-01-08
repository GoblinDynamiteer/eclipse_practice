#include "..\def.h"

/*	 Process game events	*/
bool processEvent(ballsGame * game){
	/*	 Event union	*/
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		Uint32 type = event.type;
		switch(type){
			/*	 Close button is pressed	*/
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_CLOSE){
					return 0;
				}
				break;
			/*	 A key has been pressed	*/
			case SDL_KEYDOWN:
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					return 0;
				}
				break;
			/*	 A mouse button has been pressed	*/
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT &&
						game->mode == NORMAL){
					int x, y;
					SDL_GetMouseState(&x, &y);
					addBall(game, x, y);
				}
				break;
			case SDL_MOUSEWHEEL:
				if(event.wheel.y < 0){
					cycleGameMode(game, 1);
				}
				else if(event.wheel.y > 0){
					cycleGameMode(game, 0);
				}
				break;
		}
	}

	/*	 Gets mouse cursor position	*/
	Uint32 mouseState = SDL_GetMouseState(&game->cursor.x, &game->cursor.y);
	if(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)){
		addBall(game, game->cursor.x, game->cursor.y);
	}

	/*	 Moves and rotate balls	*/
	for(int i = 0; i< MAX_BALLS; i++){
		/*	 Break if NULL pointer	*/
		if(!game->balls[i]){
			break;
		}
		switch(game->mode){
			case NORMAL:
				moveBall(game, i);
				break;
			case MAGNET:
				huntCursor(game, i);
				break;
			case REPEL:
				avoidCursor(game, i);
				break;
		}
		rotateBall(game, i);
		accelBall(game, i);
		borderCheck(game, i);
	}

	return 1;
}

/*	 Uses distance formula	*/
double calculateDistance(int x1, int x2, int y1, int y2){
	 double calc =
		sqrt(
		pow((float)x1 - (float)x2, 2) +
		pow((float)y1 - (float)y2, 2)
	);
	return calc;
}

/*	 Generates a random direction (and speed) for new balls	*/
float getRandomDirection(void){
	int negPos = rand() % 10;
	float direction = (float)(rand() % 5)
			+ (float)(rand() % 10) / 10.0f;
	if(negPos > 5){
		return 0.4 + direction;
	}
	else{
		return 0.4 - direction;
	}
}

void cycleGameMode(ballsGame * game, bool upDown){
	if(upDown){
		if(game->mode == REPEL){
			game->mode = NORMAL;
		}
		else game->mode++;
	}
	else{
		if(game->mode == NORMAL){
			game->mode = REPEL;
		}
		else game->mode--;
	}
}
