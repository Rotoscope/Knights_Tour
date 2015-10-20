/* 
 * File:   main.cpp
 * Author: Stanley Seeto
 *
 * Created on October 19, 2015, 10:21 PM
 * CECS282 Project 6 Knight's Tour: Brute Force part A
 */

#include <bitset>
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
    int count, move = 0;
    bitset<8> flags;

    srand(time(NULL));

    int currentRow = rand() % 8;
    int currentColumn = rand() % 8;
    for (count = 1; count <= 64; count++) {
	if (count != 1) {
	    while(flags.count() < 8) {
		do {
		    move = rand() % 8;
		} while (!(flags[move] == 0 || flags.count() == 8));
		
		currentRow += horizontal[move];
		currentColumn += vertical[move];

		if (!isValid(currentRow, currentColumn) ||
			chessBoard[currentRow][currentColumn] != 0) {
		    currentRow -= horizontal[move];
		    currentColumn -= vertical[move];
		    flags[move] = 1;
		} else {
		    break;
		}
	    }
	}

	if (flags.count() == 8) break;

	//Record the latest count in each square the knight moves to.
	chessBoard[currentRow][currentColumn] = count;
	flags.reset();
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
