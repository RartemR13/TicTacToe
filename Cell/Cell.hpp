#pragma once //include в файл будет производится лишь раз

enum CellFlag {
	UNUSED, 	  //если в клетке ни 0, ни X
	PLAYER_FIRST, //если в клетке X
	PLAYER_SECOND //если в клетке 0
};

typedef unsigned char CellCoord;

class Cell {
public:
	Cell();

	void SetFlag(const CellFlag);
	CellFlag GetFlag();

private:
	CellFlag flag_;
};