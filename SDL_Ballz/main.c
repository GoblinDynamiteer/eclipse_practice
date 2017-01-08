/*
 * main.c
 *
 *  Created on: 8 jan. 2017
 *      Author: kampe_000
 */


#include "def.h"

int main(int argc, char *argv[]){
	/*	 Init SDL	*/
    SDL_Init( SDL_INIT_EVERYTHING );

    /*	 Declare window and renderer	*/
    SDL_Window * window;
    SDL_Renderer * renderer;

    /*	 Create the window and renderer	*/

    if(SDL_CreateWindowAndRenderer(
    		WIN_WIDTH,
			WIN_HEIGHT,
			WIN_FLAGS,
			&window,
			&renderer)
    	){
    	printf("Could not create window/renderer!\n"
    			"Error: %s\n", SDL_GetError());
    };

    /*	 Declare struct ballsGame	*/
    ballsGame ballsGame;
    ballsGame.window = window;
    ballsGame.renderer = renderer;

    /*	 Load game	*/
    loadGame(&ballsGame);

    while(processEvent(&ballsGame)){
    	if(!renderGame(&ballsGame)){
    		break;
    	}
    	SDL_Delay(1000/60);
    }


    /*	 Quit SDL	*/
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();


	return 0;
}
