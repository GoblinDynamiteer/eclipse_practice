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
				if(event.button.button == SDL_BUTTON_LEFT){
					int x, y;
					SDL_GetMouseState(&x, &y);
					addBall(game, x, y);
				}
				break;
		}
	}

	return 1;
}

bool addBall(ballsGame * game, int x, int y){
	int index = 0;

	/*	 Finds next free ball	*/
	while(game->balls[index] != NULL && index < MAX_BALLS){
		index++;
	}

	printf("Ball index: %d\n", index);

	/*	 Set ball x, y, width, height	*/
	game->balls[index] = malloc(sizeof(ball));
	game->balls[index]->rect.x = x - (BALL_SIZE / 2);
	game->balls[index]->rect.y = y - (BALL_SIZE / 2);
	game->balls[index]->rect.w = BALL_SIZE;
	game->balls[index]->rect.h = BALL_SIZE;

	/*	 Set random ball speed	*/
	game->balls[index]->speed.x = getRandomDirection();
	game->balls[index]->speed.y = getRandomDirection();

	return 1;
}


float getRandomDirection(void){
	int negPos = rand() % 10;
	float direction = (float)(rand() % 5);
	if(negPos > 5){
		printf("RandDir: %g\n", 0.0 + direction);
		return 0.0 + direction;
	}
	else{
		printf("RandDir: %g\n", 0.0 - direction);
		return 0.0 - direction;
	}
}


