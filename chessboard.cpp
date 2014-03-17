#include "chessboard.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

Chessboard::Chessboard() : m_Rows(8), m_Columns(8)
{
	Init();
}

Chessboard::Chessboard(int rows, int columns) : m_Rows(rows), m_Columns(columns)
{
	if (m_Rows < 1)
		m_Rows = 1;
	if (m_Columns < 1)
		m_Columns = 1;
	Init();
}

bool Chessboard::InBounds(int row, int column) const {
	return 0 <= row && row < m_Rows
		&& 0 <= column && column < m_Columns;
}

void Chessboard::PrintBoard() const
{
	for (int i = 0; i < m_Rows; i++) {
		for (int j = 0; j < m_Columns; j++)
			cout<<Board[i][j].available<<" ";
		cout << endl;
	}
}

void Chessboard::Init()
{
	Board.resize(m_Rows);
	SolutionList.resize(m_Rows);

	for (int i=0; i<m_Rows; ++i) {
		Board[i] = unique_ptr<ChessCell[]>(new ChessCell[m_Columns]);
		SolutionList[i] = -1;
	}
}

void Chessboard::PlacePiece(PieceType type, int row, int column)
{
	if (!InBounds(row,column)) {
		cout << "Can't place piece, it's out of bounds.\n";
		return;
	}
	
	switch(type) {
		
		case QUEEN:
			LeftDiagonal(row, column, 0);
			RightDiagonal(row, column, 0);
			VerticalHorizontal(row, column, 0);
		break;
		
		
	}
}

void Chessboard::RemovePiece(PieceType type, int row, int column)
{
	if (!InBounds(row,column)) {
		cout << "Can't place piece, it's out of bounds.\n";
		return;
	}
	
	switch(type) {
		
		case QUEEN:
			LeftDiagonal(row, column, 1);
			RightDiagonal(row, column, 1);
			VerticalHorizontal(row, column, 1);
		break;
	}
}

void Chessboard::LeftDiagonal(int row, int column, bool value)
{
	int r = row, c = column;
	while (InBounds(r,c))
		ChangeCell(r++, c++, value);
		
	r = row-1;
	c = column-1;
	while (InBounds(r,c))
		ChangeCell(r--, c--, value);
}

void Chessboard::RightDiagonal(int row, int column, bool value)
{
	int r = row, c = column;
	while (InBounds(r,c))
		ChangeCell(r--, c++, value);
		
	r = row+1;
	c = column-1;
	while (InBounds(r,c))
		ChangeCell(r++, c--, value);
	
}

void Chessboard::VerticalHorizontal(int row, int column, bool value)
{

	for (int r = 0; r < m_Rows; r++) 
		ChangeCell(r, column, value);

	for (int c = 0; c < m_Columns; c++)
		ChangeCell(row, c, value);
}

bool Chessboard::PlaceQueenRow(int row)
{
	for (int col = 0; col < m_Columns; col++) {
		if (row == m_Rows)  //Solved
			return true;
		if (Board[row][col].available) {
			PlacePiece(QUEEN, row, col);
			if (PlaceQueenRow(row+1)) {
				cout << "(" << row << ", " << col << ")\n";
				SolutionList[row] = col;
				return true;
			}
			else {
				RemovePiece(QUEEN, row, col);
				SolutionList[row] = -1;
			}
		}
	}
	return false;
}
void Chessboard::PrintEightQueensSolution()
{
	if (PlaceQueenRow(0)) {
		for (int r = 0; r < m_Rows; r++) {
			for (int c = 0; c < m_Columns; c++) {
				if (SolutionList[r] == c)
					cout << "q ";
				else cout << Board[r][c].available << " ";
			}
			cout << endl;
		}
	}
	else cout << "No solution.\n";
}

void Chessboard::ChangeCell(int row, int column, bool value)
{
	if (value == 0) {
		++Board[row][column].count;
		Board[row][column].available = value;
	}

	else {
		if (Board[row][column].count > 0)
			--Board[row][column].count;
		if (Board[row][column].count == 0)
			Board[row][column].available = value;
	}
}
