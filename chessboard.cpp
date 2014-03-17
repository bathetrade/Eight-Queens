#include "chessboard.h"
#include <iostream>
using namespace std;

Chessboard::Chessboard()
{
	m_Rows = m_Columns = 8;
	Init();

}

Chessboard::Chessboard(int rows, int columns)
{
	m_Rows    = rows;
	m_Columns = columns;
	if (m_Rows < 1)
		m_Rows = 1;
	if (m_Columns < 1)
		m_Columns = 1;
	Init();
}

Chessboard::~Chessboard()
{
	for (int i = 0; i < m_Rows; i++)
		delete[] mpp_TheBoard[i];
	delete[] mpp_TheBoard;
	mpp_TheBoard = 0;
	
	delete mp_SolutionList;
}

void Chessboard::PrintBoard()
{
	for (int i = 0; i < m_Rows; i++) {
		for (int j = 0; j < m_Columns; j++)
			cout<<mpp_TheBoard[i][j].available<<" ";
		cout << endl;
	}
}

void Chessboard::Init()
{
	mp_SolutionList = new int[m_Rows];
	mpp_TheBoard = new ChessCell*[m_Rows];

	for (int i = 0; i < m_Rows; i++) {
		mpp_TheBoard[i]    = new ChessCell[m_Columns];
		mp_SolutionList[i] = -1;
	}
}

void Chessboard::PlacePiece(int type, int row, int column)
{
	if (row >= m_Rows || column >= m_Columns || row < 0 || column < 0) {
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

void Chessboard::RemovePiece(int type, int row, int column)
{
	if (row >= m_Rows || column >= m_Columns || row < 0 || column < 0) {
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
	while (r < m_Rows && c < m_Columns) {
		ChangeCell(r, c, value);
		r++;
		c++;
	}
	r = row-1;
	c = column-1;
	while (r >= 0 && c >= 0) {
		ChangeCell(r, c, value);
		r--;
		c--;
	}
}

void Chessboard::RightDiagonal(int row, int column, bool value)
{
	int r = row, c = column;
	while (r >= 0 && c < m_Columns) {
		ChangeCell(r, c, value);
		r--;
		c++;
	}
	r = row+1;
	c = column-1;
	while (r < m_Rows && c >= 0) {
		ChangeCell(r, c, value);
		r++;
		c--;
	}
	
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
		if (mpp_TheBoard[row][col].available) {
			PlacePiece(QUEEN, row, col);
			if (PlaceQueenRow(row+1)) {
				cout << "(" << row << ", " << col << ")\n";
				mp_SolutionList[row] = col;
				return true;
			}
			else {
				RemovePiece(QUEEN, row, col);
				mp_SolutionList[row] = -1;
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
				if (mp_SolutionList[r] == c)
					cout << "q ";
				else cout << mpp_TheBoard[r][c].available << " ";
			}
			cout << endl;
		}
	}
	else cout << "No solution.\n";
}

void Chessboard::ChangeCell(int row, int column, bool value)
{
	if (value == 0) {
		mpp_TheBoard[row][column].count++;
		mpp_TheBoard[row][column].available = value;
	}

	else {
		if (mpp_TheBoard[row][column].count > 0)
			mpp_TheBoard[row][column].count--;
		if (mpp_TheBoard[row][column].count == 0)
			mpp_TheBoard[row][column].available = value;
	}
}
