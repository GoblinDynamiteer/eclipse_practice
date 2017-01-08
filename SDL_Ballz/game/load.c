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

	/*	 Loads the ball texture	*/
	SDL_Surface * surface = IMG_Load("art/ball.png");
	game->ballArt = SDL_CreateTextureFromSurface(game->renderer, surface);

	return 1;
}
