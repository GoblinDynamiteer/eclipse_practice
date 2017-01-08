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
	SDL_GetMouseState(&game->cursor.x, &game->cursor.y);

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
		}
		rotateBall(game, i);
		accelBall(game, i);
		borderCheck(game, i);
	}

	return 1;
}



bool addBall(ballsGame * game, int x, int y){
	int i = 0;

	/*	 Finds next free ball	*/
	while(game->balls[i] != NULL && i < MAX_BALLS){
		i++;
	}

	printf("Ball index: %d\n", i);

	/*	 Set ball x, y, width, height	*/
	game->balls[i] = malloc(sizeof(ball));
	game->balls[i]->rect.x = x - (BALL_SIZE / 2);
	game->balls[i]->rect.y = y - (BALL_SIZE / 2);
	game->balls[i]->rect.w = BALL_SIZE;
	game->balls[i]->rect.h = BALL_SIZE;

	/*	 Set random ball speed	*/
	game->balls[i]->speed.x = getRandomDirection();
	game->balls[i]->speed.y = getRandomDirection();

	/*	 Set balls starting angle, for rotation	*/
	game->balls[i]->angle = 0.0;

	/*	 Set ball color	*/
	game->balls[i]->color = rand() % (PURPLE + 1);

	return 1;
}

void huntCursor(ballsGame * game, int i){
	/*	 Pointers to x, y and speed	for ball */
	int *posx = &game->balls[i]->rect.x;
	int *posy = &game->balls[i]->rect.y;
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;

	/*	 Position balls nearer current cursor location	*/
	if(*posx != game->cursor.x){
		*posx = (
			*posx > game->cursor.x ?
				*posx - fabs(*velx) * 2 :
				*posx + fabs(*velx) * 2
		);
	}
	if(*posy != game->cursor.y){
		*posy = (
			*posy > game->cursor.y ?
				*posy - fabs(*vely) * 2 :
				*posy + fabs(*vely) * 2
		);
	}
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

void accelBall(ballsGame * game, int i){
	/*	 Pointers to speed for ball */
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;

	/*	 Accelerate balls!	*/
	if(fabs(*velx) < MAXSPEED ){
		*velx = *velx > 0 ? *velx + ACC : *velx - ACC;
	}
	if(fabs(*vely) < MAXSPEED ){
		*vely = *vely > 0 ? *vely + ACC : *vely - ACC;
	}
}

void borderCheck(ballsGame * game, int i){
	/*	 Pointers to x, y and speed	for ball */
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;
	int *posx = &game->balls[i]->rect.x;
	int *posy = &game->balls[i]->rect.y;

	/*	 Check game window collision	*/
	if(*posx + BALL_SIZE/2 >= WIN_WIDTH){
		*velx *= -1;
		*posx = WIN_WIDTH - BALL_SIZE;
	}

	if(*posx - BALL_SIZE/2 < 0){
		*velx *= -1;
		*posx = BALL_SIZE/2;
	}

	if(*posy + BALL_SIZE/2 >= WIN_HEIGHT){
		*vely *= -1;
		*posy = WIN_HEIGHT - BALL_SIZE;
	}

	if(*posy - BALL_SIZE/2 < 0){
		*vely *= -1;
		*posy = BALL_SIZE/2;
	}
}

void rotateBall(ballsGame * game, int i){
	game->balls[i]->angle += 1.6f;

	if(game->balls[i]->angle >= 360){
	game->balls[i]->angle = 0.0;
	}
}


void moveBall(ballsGame * game, int i){
	/*	 Pointers to x, y and speed	for ball */
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;
	int *posx = &game->balls[i]->rect.x;
	int *posy = &game->balls[i]->rect.y;

	/*	 Move balls in x and y	*/
	*posx += *velx;
	*posy += *vely;
}

void cycleGameMode(ballsGame * game, bool upDown){
	if(upDown){
		if(game->mode == MAGNET){
			game->mode = NORMAL;
		}
		else game->mode++;
	}
	else{
		if(game->mode == NORMAL){
			game->mode = MAGNET;
		}
		else game->mode--;
	}
}
