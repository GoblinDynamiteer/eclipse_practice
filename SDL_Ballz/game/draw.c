#include "..\def.h"

/*
 * draw.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

bool renderGame(ballsGame * game){
	/*	 Sets background color	*/
	SDL_SetRenderDrawColor(game->renderer, 102, 204, 204, 255);
	SDL_RenderClear(game->renderer);

	/*	 Draws balls	*/
	for(int i = 0; i< MAX_BALLS; i++){
		if(!game->balls[i]){
			break;
		}
		SDL_RenderCopyEx(
				game->renderer,
				game->ballArt,
				NULL,
				&game->balls[i]->rect,
				game->balls[i]->angle,
				NULL,
				SDL_FLIP_NONE
			);
	};


	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
	return 1;
}
;

