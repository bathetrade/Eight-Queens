#ifndef CHESS_H
#define CHESS_H
#define QUEEN 0

struct ChessCell
{
	int count;
	bool available;
	ChessCell() { available = true; count = 0; }
};


class Chessboard
{
private:
	ChessCell **mpp_TheBoard;
	int m_Rows, m_Columns;
	int *mp_SolutionList;

	void Init();
	void RightDiagonal(int row, int column, bool value);
	void LeftDiagonal(int row, int column, bool value);
	void VerticalHorizontal(int row, int column, bool value);
	bool PlaceQueenRow(int row);
	void ChangeCell(int row, int column, bool value);
public:
	Chessboard();
	Chessboard(int rows, int columns);
	~Chessboard();
	bool InBounds(int row, int column) const;
	void PrintBoard() const;
	void PlacePiece(int type, int row, int column);
	void RemovePiece(int type, int row, int column);
	void PrintEightQueensSolution();
};

#endif
