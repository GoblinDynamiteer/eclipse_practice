/*
	Pogramming excercise 8.11, Page 181
	Book "C Från Början"

	Build a program that checks if a soduko-
	playing board is correctly solved.

	Exercise wants a two dimensional array.

	I'm doing my own version to practice with
	the Eclipse IDE and debugger.
 */


#include "def.h"

int main(void){
	/*	 Correct board	*/
	short playingBoard[SIZE] = {
		5, 3, 4, 6, 7, 8, 9, 1, 2,
		6, 7, 2, 1, 9, 5, 3, 4, 8,
		1, 9, 8, 3, 4, 2, 5, 6, 7,
		8, 5, 9, 7, 6, 1, 4, 2, 3,
		4, 2, 6, 8, 5, 3, 7, 9, 1,
		7, 1, 3, 9, 2, 4, 8, 5, 6,
		9, 6, 1, 5, 3, 7, 2, 8, 4,
		2, 8, 7, 4, 1, 9, 6, 3, 5,
		3, 4, 5, 2, 8, 6, 1, 7, 9
	};

	/*	 Faulty board	*/
	short playingBoardFaulty[SIZE] = {
		5, 3, 3, 6, 7, 8, 9, 1, 2,
		6, 7, 2, 1, 9, 5, 3, 4, 8,
		1, 9, 8, 3, 4, 2, 5, 6, 7,
		8, 5, 9, 7, 6, 1, 4, 2, 3,
		4, 2, 6, 8, 5, 3, 7, 9, 1,
		7, 1, 3, 9, 2, 4, 8, 5, 6,
		9, 6, 1, 5, 3, 7, 2, 8, 4,
		2, 8, 7, 4, 1, 9, 6, 3, 5,
		3, 4, 5, 2, 8, 6, 1, 7, 9
	};
	if(checkBoard(playingBoard)){
		printf("Board is solved correctly!\n");
	}

	if(!checkBoard(playingBoardFaulty)){
		printf("Board is not solved correctly!\n");
	}
	return 0;
	}








