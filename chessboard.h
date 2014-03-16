#ifndef CHESS_H
#define CHESS_H
#define QUEEN 0

struct ChessCell
{
	bool available;
	short count;
	ChessCell() { available = 1; count = 0; }
};


class Chessboard
{
private:
	ChessCell **mpp_TheBoard;
	short m_Rows, m_Columns;
	short *mp_SolutionList;

	void Init();
	void RightDiagonal(short row, short column, bool value);
	void LeftDiagonal(short row, short column, bool value);
	void VerticalHorizontal(short row, short column, bool value);
	bool PlaceQueenRow(short row);
	void ChangeCell(short row, short column, bool value);
public:
	Chessboard();
	Chessboard(short rows, short columns);
	~Chessboard();
	void PrintBoard();
	void PlacePiece(int type, short row, short column);
	void RemovePiece(int type, short row, short column);
	void PrintEightQueensSolution();
};

#endif
