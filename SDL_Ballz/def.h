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
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"


/*	 Window dimensions, FULL HD!	*/
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

/*	 Flags for window	*/
#define WIN_FLAGS 0//SDL_WINDOW_FULLSCREEN
#define REN_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

/*	 Max balls on screen	*/
#define MAX_BALLS 500

/*	 Ball art size. Height == Width	*/
#define BALL_SIZE 50

/*	 Ball movement speed & acceleration	*/
#define MAXSPEED 10
#define ACC 0.04

/*	 Struct definitions	*/
typedef struct velocity{
	float x, y;
}velocity;

typedef struct ball{
	SDL_Rect rect;
	velocity speed;
	double angle;
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
void moveBalls(ballsGame * game);
float getRandomDirection(void);
bool addBall(ballsGame * game, int x, int y);

/*	 draw.c	*/
bool renderGame(ballsGame * game);


#endif /* DEF_H_ */
