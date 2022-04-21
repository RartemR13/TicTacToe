#pragma once //include в файл будет производится лишь раз

#include <vector>
#include <utility> //для подключения pair<T1, T2>

#include "../Cell/Cell.hpp"

typedef std::vector<std::vector<Cell>> GameMapStorage;

enum GameMapConstant {
	CELL_COORD_MAX  = 19
};

enum GameStatus {
	PLAYER_FIRST_WIN,
	PLAYER_SECOND_WIN,
	DRAW,
	PROCESS,
	INCORRECT
};

enum Turn {
	PLAYER_FIRST_TURN,
	PLAYER_SECOND_TURN,
	END_GAME
};

class GameMap {
public:
	GameMap(unsigned char = 19, unsigned char = 19, unsigned char = 5);

	void SetCell(const CellCoord, const CellCoord, const CellFlag);
	CellFlag GetCell(const CellCoord, const CellCoord);

	GameStatus CheckGameStatus();
	Turn GetTurn();

	GameMapStorage& GetStorage();

	const CellCoord ROW_LEN_,
					COLUMN_LEN_,
					WIN_STREAK_SIZE_;
private:
	GameMapStorage storage_;

	bool CheckPlayerWin(const CellFlag);

	bool CheckUnusedCells();
};
