/*
 * balls.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */

#include "..\def.h"

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
	game->balls[i]->active = 1;

	return 1;
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

void huntCursor(ballsGame * game, int i){
	/*	 Pointers to x, y and speed	for ball */
	int *posx = &game->balls[i]->rect.x;
	int *posy = &game->balls[i]->rect.y;
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;

	/*	 Position balls nearer current cursor location	*/
	/*	 Calculate distance	*/
	double distance =
			calculateDistance(
					*posx, game->cursor.x,
					*posy, game->cursor.y
				);

	if(distance < MAGSTR){
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
	else{
		moveBall(game, i);
	}
}

void avoidCursor(ballsGame * game, int i){
	/*	 Pointers to x, y and speed	for ball */
	int *posx = &game->balls[i]->rect.x;
	int *posy = &game->balls[i]->rect.y;
	float *velx = &game->balls[i]->speed.x;
	float *vely = &game->balls[i]->speed.y;

	/*	 Position balls away from current cursor location	*/
	/*	 Calculate distance	*/
	double distance =
			calculateDistance(
					*posx, game->cursor.x,
					*posy, game->cursor.y
				);

	if(distance < REPELSTR){
		*posx = (
			*posx > game->cursor.x ?
				*posx + fabs(*velx) * 3 :
				*posx - fabs(*velx) * 3
		);
		*posy = (
			*posy > game->cursor.y ?
				*posy + fabs(*vely) * 3 :
				*posy - fabs(*vely) * 3
		);
	}
	else{
		moveBall(game, i);
	}
}
