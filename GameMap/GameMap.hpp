#pragma once //include в файл будет производится лишь раз

#include <vector>
#include <utility> //для подключения pair<T1, T2>

#include "../Cell/Cell.hpp"

typedef std::vector<std::vector<Cell>> GameMapStorage;

enum GameMapConstant {
	COLUMN_LEN 		= 19,
	ROW_LEN    		= 19,
	WIN_STREAK_SIZE = 5,
	CELL_COORD_MAX  = (1u << (sizeof(CellCoord) * 8))
};

enum GameStatus {
	PLAYER_FIRST_WIN,
	PLAYER_SECOND_WIN,
	DRAW,
	PROCESS,
	INCORRECT
};

class GameMap {
public:
	GameMap();

	void SetCell(const CellCoord, const CellCoord, const CellFlag);
	CellFlag GetCell(const CellCoord, const CellCoord);

	GameStatus CheckGameStatus();
private:
	GameMapStorage storage_; 

	bool CheckRowsGameStatus(const CellFlag);
	bool CheckColumnsGameStatus(const CellFlag);

	bool CheckMainDiagonalCollinearsGameStatus(const CellFlag);
	bool CheckSideDiagonalCollinearsGameStatus(const CellFlag);

	bool CheckUnusedCells();
};
