// Donald J Freiday
// CISC 125 : Computer Science 2
// Eight Queens Assignment
// @file main.cpp

#include <iostream>

#define BOARD_SIZE 8
#define NUM_QUEENS 8
#define DEBUG false
#define DEBUG_VERBOSE false

char board[BOARD_SIZE][BOARD_SIZE]; // int currentPermutation[MAX_PERMUTATION_SIZE+1]

// void initializeCurrentPath()
void initializeBoard();

// void attempt(int n, int level, int possibility)
void attempt(int column, int numQueens, int* numSolutions);

// void addToCurrentPath(int level, int possibility)
void placeQueen(int row, int column);

// void removeFromCurrentPath(int level)
void removeQueen(int row, int column);

// bool currentPathSuccess(int n, int level)
bool allQueensPlaced(int column, int numQueens);

// bool currentPathStillViable(int level)
bool queenIsSafe(int row, int column);

// void processSuccessfulPath(int n)
void displayBoard();

using namespace std;

int main()
{
	cout << "Donald J Freiday \n"
		<< "CISC 125 : Computer Science 2 \n"
		<< "Eight Queens Assignment \n";

	int numSolutions = 0;

	initializeBoard();

	attempt(0, NUM_QUEENS, &numSolutions); // start in leftmost square (0)

	cout << "\nThere are " << numSolutions << " ways to place "
		<< NUM_QUEENS << " Queens on a " << BOARD_SIZE << "x" << BOARD_SIZE << " board.\n";
}

// place numQueens Queens on the board
void attempt(int column, int numQueens, int* numSolutions)
{
	if (DEBUG)
		cout << "attempt(column=" << column << ", numQueens=" << numQueens << ", numSolutions=" << (*numSolutions) << endl; // trace
	if (DEBUG_VERBOSE)
	{
		displayBoard();
		cin.get();
	}

	// We found a solution! Base case. Exit the recursion here if we only want one solution
	if (allQueensPlaced(column, numQueens))
	{
		displayBoard();
		(*numSolutions)++;
		if (DEBUG) { cin.get(); } // pause after each solution
	}

	// for each row in the current column
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		if (queenIsSafe(row, column))
		{
			placeQueen(row, column); // place the queen
			attempt(column + 1, numQueens, numSolutions); // does this placement lead to a solution?
			removeQueen(row, column); // remove the queen (backtrack), and try the next row
		}
	}
}

void placeQueen(int row, int column)
{
	board[row][column] = 'Q';
}

void removeQueen(int row, int column)
{
	board[row][column] = ' ';
}

bool allQueensPlaced(int column, int numQueens)
{
	return column >= numQueens ? true : false;
}

// We only have to look backwards, since the Queen will always be placed in the column to the right
bool queenIsSafe(int row, int column)
{
	// diagonal up-left from Queen
	for (int r = row, c = column; r >= 0 && c >= 0; --r, --c)
	{
		if (board[r][c] == 'Q')
			return false;
	}

	// row to the left of Queen
	for (int c = column; c >= 0; --c)
	{
		if (board[row][c] == 'Q')
			return false;
	}

	// diagonal down-left from Queen
	for (int r = row, c = column; r < BOARD_SIZE&&c >= 0; ++r, --c)
	{
		if (board[r][c] == 'Q')
			return false;
	}

	return true;
}

void initializeBoard()
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int column = 0; column < BOARD_SIZE; column++)
			board[row][column] = ' ';
	}
}

// Scales to any BOARD_SIZE
void displayBoard()
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		cout << "\n+";
		for (int i = 0; i < BOARD_SIZE; i++)
			cout << "--+";
		cout << "\n|";
		for (int column = 0; column < BOARD_SIZE; column++)
			cout << board[row][column] << " |";
	}
	cout << "\n+";
	for (int i = 0; i < BOARD_SIZE; i++)
		cout << "--+";
	cout << "\n";
}