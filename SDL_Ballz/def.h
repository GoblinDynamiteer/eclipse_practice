/*
 * def.h
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

/*	 Include guard	*/
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"


/*	 Window dimensions, FULL HD!	*/
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

/*	 Flags for window	*/
#define WIN_FLAGS 0//SDL_WINDOW_FULLSCREEN

/*	 Max balls on screen	*/
#define MAX_BALLS 500

/*	 Ball art size. Height == Width	*/
#define BALL_SIZE 50

/*	 Default ball movement speed	*/
#define SPEED 2

/*	 Struct definitions	*/
typedef struct velocity{
	float x, y;
}velocity;

typedef struct ball{
	SDL_Rect rect;
	velocity speed;
}ball;

typedef struct ballsGame{
	SDL_Window * window;
	SDL_Renderer * renderer;
	ball * balls[MAX_BALLS];
	SDL_Texture * ballArt;
}ballsGame;


/*	 Function definitions	*/

/*	 load.c	*/
bool loadGame(ballsGame * game);

/*	 event.c	*/
bool processEvent(ballsGame * game);
bool addBall(ballsGame * game, int x, int y);

/*	 draw.c	*/
bool renderGame(ballsGame * game);


#endif /* DEF_H_ */
