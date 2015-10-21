/* 
 * File:   main.cpp
 * Author: Stanley Seeto
 *
 * Created on October 19, 2015, 10:51 PM
 * CECS282 Project 6 Knight's Tour part C
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
    int count = 1, moveNumber = 0, full_tour = 0;

    const int accessibilityBoard[BOARD_SIZE][BOARD_SIZE] = {
	{2, 3, 4, 4, 4, 4, 3, 2},
	{3, 4, 6, 6, 6, 6, 4, 3},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{4, 6, 8, 8, 8, 8, 6, 4},
	{3, 4, 6, 6, 6, 6, 4, 3},
	{2, 3, 4, 4, 4, 4, 3, 2}
    };

    int ab[BOARD_SIZE][BOARD_SIZE];

    for (int tour_number = 0; tour_number < 64; tour_number++) {
	int currentRow = (tour_number / 8) % 8;
	int currentColumn = tour_number % 8;

	//reset the access board
	for (int i = 0; i < BOARD_SIZE; i++) {
	    copy(accessibilityBoard[i], accessibilityBoard[i] + BOARD_SIZE, ab[i]);
	}

	for (count = 0; count < 64; count++) {
	    if (count != 0) {
		moveNumber = getHeuristicMove(currentRow, currentColumn, ab,
			horizontal, vertical);

		if (moveNumber == MOVE_SIZE) break;

		reduceAssess(currentRow, currentColumn, ab,
			horizontal, vertical);

		currentRow += horizontal[moveNumber];
		currentColumn += vertical[moveNumber];
	    }

	    //Record the latest count in each square the knight moves to.
	    chessBoard[currentRow][currentColumn] = count + 1;
	}

	if (count == 64) full_tour++;
	memset(chessBoard, 0, sizeof (chessBoard[0][0]) * BOARD_SIZE * BOARD_SIZE);
    }

    cout << "Total full tours made : " << full_tour << endl;

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
	    }
	}
    }

    return bestMove;
}

bool isValid(int currentRow, int currentColumn) {
    return !(currentRow < 0 || currentRow > 7 || currentColumn < 0 || currentColumn > 7);
}
