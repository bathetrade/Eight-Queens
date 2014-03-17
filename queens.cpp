#include <iostream>
#include <cstdlib>
#include "chessboard.h"
using namespace std;

bool GetDimensions(int argc, char** argv, int& rows, int& cols)
{
	if (argc < 3)
		return false;
	
	if ((rows = atoi(argv[1])) && (cols = atoi(argv[2]))) //atoi returns 0 on failure
		return true;
	else return false;
}

int main(int argc, char** argv)
{
	int rows{};
	int cols{};
	
	if (!GetDimensions(argc, argv, rows, cols)) {
		cout << "Invalid parameters. Using default board (8x8).\n";
		rows = cols = 8;
	}
	
	Chessboard board{rows,cols};
	board.PrintEightQueensSolution();
	
	return 0;
}
