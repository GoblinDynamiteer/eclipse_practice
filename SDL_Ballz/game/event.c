#include "..\def.h"

/*	 Process game events	*/
bool processEvent(ballsGame * game){
	/*	 Event union	*/
	SDL_Event event;

	while(SDL_PollEvent(&event)){
		Uint32 type = event.type;
		switch(type){
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
	game->balls[index] = malloc(sizeof(ball));
	game->balls[index]->rect.x = x - (BALL_SIZE / 2);
	game->balls[index]->rect.y = y - (BALL_SIZE / 2);
	game->balls[index]->rect.w = BALL_SIZE;
	game->balls[index]->rect.h = BALL_SIZE;
	return 1;
}
