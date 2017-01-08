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

	/*	 Render balls and mouse cursor, order matters	*/
	renderBalls(game);
	renderCursor(game);

	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
	return 1;
}


void renderBalls(ballsGame * game){
	/*	 Draws balls	*/
	for(int i = 0; i< MAX_BALLS; i++){
		if(!game->balls[i]){
			break;
		}
		short color = game->balls[i]->color;
		SDL_RenderCopyEx(
			game->renderer,
			game->ballArt[color],
			NULL,
			&game->balls[i]->rect,
			game->balls[i]->angle,
			NULL,
			SDL_FLIP_NONE
		);
	}
}

void renderCursor(ballsGame * game){
	/*	 Draw mouse cursor	*/
	SDL_Rect cursorRect;

	/*	 Gets width and height from texture	*/
	SDL_QueryTexture(
		game->cursorArt,
		NULL,
		NULL,
		&cursorRect.w,
		&cursorRect.h
	);

	cursorRect.x = game->cursor.x - cursorRect.w / 2;
	cursorRect.y = game->cursor.y - cursorRect.h / 2;


	SDL_RenderCopyEx(
		game->renderer,
		game->cursorArt,
		NULL,
		&cursorRect,
		game->cursorAngle,
		NULL,
		SDL_FLIP_NONE
	);
}

