/*
 * load.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */


#include "..\def.h"

bool loadGame(ballsGame * game){

	/*	 Random seed	*/
	srand((int)time(NULL));

	/*	 Set starting ball array to NULL	*/
	for(int i = 0; i< MAX_BALLS; i++){
		game->balls[i] = NULL;
	};


	//RED, YELLOW, BLUE, GREEN, PURPLE
	char * imageFiles[] = {
			"art/ball_red.png",
			"art/ball_yellow.png",
			"art/ball_blue.png",
			"art/ball_green.png",
			"art/ball_purple.png",
	};

	/*	 Loads the ball texture	*/
	SDL_Surface * surface;

	for(int i = 0; i<= PURPLE; i++){
		surface = IMG_Load(imageFiles[i]);
		game->ballArt[i] = SDL_CreateTextureFromSurface(game->renderer, surface);
	}

	/*	 Load cursor texture and set rectangle	*/
	surface = IMG_Load("art/cursor.png");
	game->cursorArt = SDL_CreateTextureFromSurface(game->renderer, surface);

	/*	 Free surfaces	*/
	SDL_FreeSurface(surface);

	game->cursorAngle = 0.0;

	return 1;
}
