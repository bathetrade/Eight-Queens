#ifndef CHESS_H
#define CHESS_H

#include <memory>
#include <vector>

enum PieceType : char { QUEEN };

struct ChessCell
{
	int count;
	bool available;
	ChessCell() { available = true; count = 0; }
};


class Chessboard
{
private:
	std::vector<std::unique_ptr<ChessCell[]>> Board;
	int m_Rows, m_Columns;
	std::vector<int> SolutionList;

	void Init();
	void RightDiagonal(int row, int column, bool value);
	void LeftDiagonal(int row, int column, bool value);
	void VerticalHorizontal(int row, int column, bool value);
	bool PlaceQueenRow(int row);
	void ChangeCell(int row, int column, bool value);
public:
	Chessboard();
	Chessboard(int rows, int columns);
	bool InBounds(int row, int column) const;
	void PrintBoard() const;
	void PlacePiece(PieceType type, int row, int column);
	void RemovePiece(PieceType type, int row, int column);
	void PrintEightQueensSolution();
};

#endif
