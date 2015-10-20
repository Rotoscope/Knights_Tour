/* 
 * File:   main.cpp
 * Author: Stanley Seeto
 *
 * Created on October 19, 2015, 10:21 PM
 * CECS282 Project 6 Knight's Tour part B
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>

#define SIZE 8

using namespace std;

bool isValid(int, int);
void display(int (&cb)[SIZE][SIZE]);

/*
 * 
 */
int main(int argc, char** argv) {
    int chessBoard[SIZE][SIZE] = {};

    int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    int currentRow = 3;
    int currentColumn = 4;
    int count, moveNumber = 0;

    for (count = 1; count <= 64; count++) {
	if (count != 1) {
	    moveNumber = 0;

	    do {
		currentRow += horizontal[moveNumber];
		currentColumn += vertical[moveNumber];

		if (!isValid(currentRow, currentColumn) ||
			chessBoard[currentRow][currentColumn] != 0) {
		    currentRow -= horizontal[moveNumber];
		    currentColumn -= vertical[moveNumber];
		    moveNumber++;
		} else {
		    break;
		}
	    } while (moveNumber < 8);
	}

	//tried all possible moves and no where to go
	if (moveNumber > 7) break;

	//Record the latest count in each square the knight moves to.
	chessBoard[currentRow][currentColumn] = count;
    }

    display(chessBoard);
    cout << "Total moves made : " << count - 1;

    system("pause");
    return 0;
}

bool isValid(int currentRow, int currentColumn) {
    return !(currentRow < 0 || currentRow > 7 || currentColumn < 0 || currentColumn > 7);
}

void display(int (&cb)[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	    printf("%02d ", cb[i][j]);
	}
	cout << endl;
    }
    cout << endl;
}
