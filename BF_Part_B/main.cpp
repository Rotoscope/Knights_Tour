/* 
 * File:   main.cpp
 * Author: Stanley Seeto
 *
 * Created on October 19, 2015, 10:21 PM
 * CECS282 Project 6 Knight's Tour: Brute Force part B
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
    int tour_count[64] = {};
    bitset<8> flags;

    srand(time(NULL));

    for (int tours = 0; tours < 1000; tours++) {
	int currentRow = rand() % 8;
	int currentColumn = rand() % 8;
	for (count = 0; count < 64; count++) {
	    if (count != 0) {
		while (flags.count() < 8) {
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
	    chessBoard[currentRow][currentColumn] = count + 1;
	    flags.reset();
	}

	tour_count[count]++;

	//tour finished so reset flags and board
	flags.reset();
	memset(chessBoard, 0, sizeof(chessBoard[0][0]) * SIZE * SIZE);
    }

    for (int i = 0; i < 64; i++) {
	if (tour_count[i] != 0)
	    cout << "There were " << tour_count[i] << " tours of " << i + 1 << " moves.\n";
    }

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
