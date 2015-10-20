/* 
 * File:   main.cpp
 * Author: Stanley Seeto
 *
 * Created on October 19, 2015, 10:51 PM
 * CECS282 Project 6 Knight's Tour part D
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>

#define BOARD_SIZE 8
#define MOVE_SIZE 8

using namespace std;

void reduceAssess(int, int, int (&ab)[BOARD_SIZE][BOARD_SIZE], int (&h)[MOVE_SIZE], int (&v)[MOVE_SIZE]);
void display(int (&cb)[BOARD_SIZE][BOARD_SIZE]);
int getHeuristicMove(int, int, int (&ab)[BOARD_SIZE][BOARD_SIZE], int (&h)[MOVE_SIZE], int (&v)[MOVE_SIZE]);
bool isValid(int, int);

/*
 * 
 */
int main(int argc, char** argv) {
    int chessBoard[BOARD_SIZE][BOARD_SIZE] = {};

    int horizontal[MOVE_SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[MOVE_SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
    int currentRow = 0;
    int currentColumn = 0;
    int count = 1, moveNumber = 0;

    int accessibilityBoard[BOARD_SIZE][BOARD_SIZE] = {
	{2, 3, 4, 4, 4, 4, 3, 2},
	{3, 4, 6, 6, 6, 6, 4, 3},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{3, 4, 6, 6, 6, 6, 4, 3},
	{2, 3, 4, 4, 4, 4, 3, 2}
    };

    for (count = 1; count <= 64; count++) {
	if (count != 1) {
	    moveNumber = getHeuristicMove(currentRow, currentColumn, accessibilityBoard,
		    horizontal, vertical);

	    if (moveNumber == MOVE_SIZE) break;

	    currentRow += horizontal[moveNumber];
	    currentColumn += vertical[moveNumber];
	}
	reduceAssess(currentRow, currentColumn, accessibilityBoard,
		horizontal, vertical);

	//Record the latest count in each square the knight moves to.
	chessBoard[currentRow][currentColumn] = count;
    }

    display(accessibilityBoard);
    display(chessBoard);
    cout << "Total moves made : " << count - 1;

    system("pause");
    return 0;
}

void reduceAssess(int cr, int cc, int (&ab)[BOARD_SIZE][BOARD_SIZE],
	int (&h)[MOVE_SIZE], int (&v)[MOVE_SIZE]) {
    int newRow, newCol;

    ab[cr][cc] = 0;

    for (int move = 0; move < MOVE_SIZE; move++) {
	newRow = cr + h[move];
	newCol = cc + v[move];

	if (isValid(newRow, newCol) && ab[newRow][newCol] > 0) {
	    ab[newRow][newCol]--;
	}
    }
}

void display(int (&cb)[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
	for (int j = 0; j < BOARD_SIZE; j++) {
	    printf("%02d ", cb[i][j]);
	}
	cout << endl;
    }
    cout << endl;
}

int getBestAccessNum(int cr, int cc, int (&ab)[BOARD_SIZE][BOARD_SIZE],
	int (&h)[MOVE_SIZE], int (&v)[MOVE_SIZE]) {
    int accNum = 0;
    int bestMove = 8;

    for (int move = 0; move < 8; move++) {
	int newRow = cr + h[move];
	int newCol = cc + v[move];

	if (isValid(newRow, newCol) && ab[newRow][newCol] != 0) {
	    if (accNum == 0) {
		accNum = ab[newRow][newCol];
		bestMove = move;
	    } else if (ab[newRow][newCol] < accNum) {
		accNum = ab[newRow][newCol];
		bestMove = move;
	    }
	}
    }
    return accNum;
}

int getHeuristicMove(int cr, int cc, int (&ab)[BOARD_SIZE][BOARD_SIZE],
	int (&h)[MOVE_SIZE], int (&v)[MOVE_SIZE]) {
    //max move number is MOVE_SIZE - 1.
    //move of MOVE_SIZE is invalid move
    int bestMove = MOVE_SIZE;
    int bestAccessNumber = 0;
    int newRow, newCol;

    for (int move = 0; move < MOVE_SIZE; move++) {
	newRow = cr + h[move];
	newCol = cc + v[move];

	if (isValid(newRow, newCol) && ab[newRow][newCol] != 0) {
	    if (bestAccessNumber == 0) {
		bestMove = move;
		bestAccessNumber = ab[newRow][newCol];
	    } else if (ab[newRow][newCol] < bestAccessNumber) {
		bestMove = move;
		bestAccessNumber = ab[newRow][newCol];
	    } else if (ab[newRow][newCol] == bestAccessNumber) {
		//next best move accessibility number for [newRow][newCol]
		int nbmAccNum1 = getBestAccessNum(newRow, newCol, ab, h, v); 
		//next best move accessibility number for current best move
		int nbmAccNum2 = getBestAccessNum(cr + h[bestMove], cc + v[bestMove], ab, h, v);

		if (nbmAccNum1 < nbmAccNum2) {
		    bestMove = move;
		}
	    }

	}
    }

    return bestMove;
}

bool isValid(int currentRow, int currentColumn) {
    return !(currentRow < 0 || currentRow > 7 || currentColumn < 0 || currentColumn > 7);
}
