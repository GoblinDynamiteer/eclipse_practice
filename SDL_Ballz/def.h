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

#include "SDL_ttf.h"

/*	 Window dimensions, FULL HD!	*/
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

/*	 Flags for window	*/
#define WIN_FLAGS 0//SDL_WINDOW_FULLSCREEN
#define REN_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

/*	 Max balls on screen	*/
#define MAX_BALLS 1000

/*	 Ball art size. Height == Width	*/
#define BALL_SIZE 50

/*	 Ball movement speed & acceleration	*/
#define MAXSPEED 15.0
#define ACC 0.001
#define MAGSTR 500
#define REPELSTR 500

/*	 Font stuff	*/
#define FONT_SIZE 28


/*	 Game modes // Cursors	*/
enum {NORMAL, MAGNET, REPEL, BLADE};

/*	 Ball colors, for texture array index	*/
enum {RED, YELLOW, BLUE, GREEN, SMILEY, PURPLE};

/*	 Struct definitions	*/
typedef struct velocity{
	float x, y;
}velocity;

typedef struct pos{
	int x, y;
}position;

typedef struct ball{
	short color;
	SDL_Rect rect;
	velocity speed;
	double angle;
}ball;

typedef struct ballsGame{
	SDL_Window * window;
	SDL_Renderer * renderer;
	ball * balls[MAX_BALLS];
	SDL_Texture * cursorArt[3];
	position cursor;
	double cursorAngle;
	short mode;
	TTF_Font *font;
	int ballIndex;
	int killedBalls;
	/*	 Flexible struct member needs to be last.	*/
	SDL_Texture * ballArt[];
}ballsGame;


/*	 Function definitions	*/

/*	 load.c	*/
bool loadGame(ballsGame * game);

/*	 event.c	*/
bool processEvent(ballsGame * game);
float getRandomDirection(void);
void cycleGameMode(ballsGame * game, bool upDown);
double calculateDistance(int x1, int x2, int y1, int y2);

/*	 balls.c	*/
bool addBall(ballsGame * game, int x, int y);
void moveBall(ballsGame * game, int i);
void rotateBall(ballsGame * game, int i);
void accelBall(ballsGame * game, int i);
void borderCheck(ballsGame * game, int i);
void huntCursor(ballsGame * game, int i);
void avoidCursor(ballsGame * game, int i);

/*	 draw.c	*/
bool renderGame(ballsGame * game);
void renderCursor(ballsGame * game);
void renderBalls(ballsGame * game);


#endif /* DEF_H_ */
