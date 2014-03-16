#include <iostream>
#include <stdlib.h>
#include "chessboard.h"
using namespace std;

bool CheckCommandLine(int argc, char** argv)
{
	if (argc < 3)
		return false;
	
	if (atoi(argv[1]) && atoi(argv[2]))
		return true;
	else return false;
}
int main(int argc, char** argv)
{
	Chessboard *pClass = 0;
	if (CheckCommandLine(argc, argv)) 
		pClass = new Chessboard((short)atoi(argv[1]), (short)atoi(argv[2]));
	else {
		cout << "Invalid parameters. Using default board (8x8).\n";
		pClass = new Chessboard;
	}
	pClass->PrintEightQueensSolution();
	if (pClass)
		delete pClass;
	return 0;
}
