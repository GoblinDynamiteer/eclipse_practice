/*
 * def.h
 *
 *  Created on: 6 jan. 2017
 *      Author: kampe_000
 */

#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdbool.h>

#define SIZE 81
#define ROW 9
#define CORRECT_SUM 1+2+3+4+5+6+7+8+9

void printBoard(short board[]);
bool checkRows(short board[]);
bool checkCols(short board[]);
bool checkSquare(short board[], int index);
bool checkBoard(short board[]);

#endif /* DEF_H_ */
