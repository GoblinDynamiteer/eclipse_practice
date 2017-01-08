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

	/*	 Moves and rotate balls	*/
	moveBalls(game);

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

	/*	 Set balls starting angle, for rotation	*/
	game->balls[index]->angle = 0.0;

	/*	 Set ball color	*/
	game->balls[index]->color = rand() % (PURPLE + 1);

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


void moveBalls(ballsGame * game){

	/*	 Move balls	*/
	for(int i = 0; i< MAX_BALLS; i++){
		float *velx = &game->balls[i]->speed.x;
		float *vely = &game->balls[i]->speed.y;
		int *posx = &game->balls[i]->rect.x;
		int *posy = &game->balls[i]->rect.y;
		if(!game->balls[i]){
			break;
		}

		/*	 Check game window collision	*/
		if(*posx + BALL_SIZE/2 >= WIN_WIDTH){
			*velx *= -1;
			*posx = WIN_WIDTH - BALL_SIZE;
		}

		if(*posx - BALL_SIZE/2 <= 0){
			*velx *= -1;
			*posx = 0 + BALL_SIZE;
		}

		if(*posy + BALL_SIZE/2 >= WIN_HEIGHT){
			*vely *= -1;
			*posy = WIN_HEIGHT - BALL_SIZE;
		}

		if(*posy - BALL_SIZE/2 <= 0){
			*vely *= -1;
			*posy = 0 + BALL_SIZE;
		}

		/*	 Move balls in x and y	*/
		*posx += *velx;
		*posy += *vely;

		/*	 Accelerate balls!	*/
		if(fabs(*velx) < MAXSPEED ){
			*velx = *velx > 0 ? *velx + ACC : *velx - ACC;
		}
		if(fabs(*vely) < MAXSPEED ){
			*vely = *vely > 0 ? *vely + ACC : *vely - ACC;
		}

		game->balls[i]->angle += 1.6f;
		if(game->balls[i]->angle >= 360){
			game->balls[i]->angle = 0.0;
		}

	}
}
