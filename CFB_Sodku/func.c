#include "def.h"

/*	 Prints the board	*/
void printBoard(short board[]){
	for(int i = 0; i < SIZE; i++){
		printf("%d ", board[i]);
		if((i+1) % 9 == 0 && i){
			printf("\n");
		};
	};
}

/*	 Checks rows	*/
bool checkRows(short board[]){
	int count = 0;
	for(int i = 0; i< SIZE; i++){
		count += board[i];
		if((i+1) % 9 == 0 && i){
			if(count != CORRECT_SUM){
				return 0;
			}
			count = 0;
		};
	};
	return 1;
}

/*	 Checks columns	*/
bool checkCols(short board[]){
	int count = 0;
	//int index = 0;
	int step = 0;
	for(int i = 0; i< 9; step += 9){
		if(step >= SIZE){
			if(count != CORRECT_SUM){
				return 0;
			}
			count = 0;
			step = 0;
			i++;
		};
		count += board[i+step];
	};
	return 1;
}

/*	 Checks 3x3 rows, starting at parameter index	*/
bool checkSquare(short board[], int index){
	int count = 0;
	int step = 0;
	for(int i = index; i< 9; step += 9){
		if(step >= 9 * 3){
			if(count != CORRECT_SUM){
				return 0;
			};
			break;
		};
		int j = 2;
		while(j>=0){
			count += board[i+step+j];
			j--;
		};
	};
	return 1;
};

/*	 Checks entire board	*/
bool checkBoard(short board[]){
	/*	 Check rows and cols	*/
	if(!checkCols(board) || !checkRows(board)){
		return 0;
	}
	/*	 Checks 3x3 squares	*/
	int counter = 1;
	for(int i = 0; i< 81; i += 3){
		counter++;
		if(!checkSquare(board, i)){
			return 0;
		}
		if(counter == 3){
			i += 9*2;
			counter = 0;
		}
	};
	return 1;
}
