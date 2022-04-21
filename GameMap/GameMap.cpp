#include "GameMap.hpp"
#include "../Liner/Liner.hpp"

#include <stdexcept> //для бросания исключений
#include <climits>

GameMap::GameMap(CellCoord row_len, CellCoord column_len, 
				 CellCoord win_streak_size) :
	storage_(),
	ROW_LEN_(row_len),
	COLUMN_LEN_(column_len),
	WIN_STREAK_SIZE_(win_streak_size)
{
	if (row_len < win_streak_size)
		throw std::runtime_error("GameMap: row_len < win_streak_size");

	if (column_len < win_streak_size)
		throw std::runtime_error("GameMap: column_len < win_streak_size");

	storage_.resize(COLUMN_LEN_, 
					std::vector<Cell>(ROW_LEN_));
}

void GameMap::SetCell(const CellCoord row, const CellCoord column, 
					  const CellFlag flag) 
{
	if (column >= ROW_LEN_)
		throw std::invalid_argument("SetCell: column >= ROW_LEN_");

	if (row >= COLUMN_LEN_)
		throw std::invalid_argument("SetCell: row >= COLUMN_LEN_");

	storage_[row][column].SetFlag(flag);
}

CellFlag GameMap::GetCell(const CellCoord row, const CellCoord column) {
	if (column >= ROW_LEN_)
		throw std::invalid_argument("GetCell: column >= ROW_LEN_");

	if (row >= COLUMN_LEN_)
		throw std::invalid_argument("GetCell: row >= COLUMN_LEN_");

	return storage_[row][column].GetFlag();	
}

bool GameMap::CheckUnusedCells() {
	if (ROW_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN_ > GameMapConstant::CELL_COORD_MAX");

	if (COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX");

	for (CellCoord row = 0; row < COLUMN_LEN_; ++row)
		for (CellCoord column = 0; column < ROW_LEN_; ++column)
			if (GetCell(row, column) == CellFlag::UNUSED)
				return true;

	return false;	
}

bool GameMap::CheckPlayerWin(const CellFlag flag) {
	if (ROW_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN_ > GameMapConstant::CELL_COORD_MAX");

	if (COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX");

	Liner liner(storage_);
	auto line = liner.Next();

	bool is_win = false;

	while (line != nullptr) {
		CellCoord l = 0, r = WIN_STREAK_SIZE_;
		while (r <= line->size()) {
			unsigned int cur_streak = 0;
			for (CellCoord it = l; it < r; ++it)
				if ((*line)[it].GetFlag() == flag)
					cur_streak++;

			if (cur_streak == WIN_STREAK_SIZE_) {
				is_win = true;
				break;
			}

			l++, r++;
		}

		delete line;
		line = liner.Next();

		if (is_win)
			break;
	}

	return is_win;
}

GameStatus GameMap::CheckGameStatus() {
	if (ROW_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN_ > GameMapConstant::CELL_COORD_MAX");

	if (COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX");

	bool first_win  = false,
		 second_win	= false;

	first_win = (CheckPlayerWin(CellFlag::PLAYER_FIRST));
	second_win = (CheckPlayerWin(CellFlag::PLAYER_SECOND));

	if (first_win && second_win)
		return GameStatus::INCORRECT;

	if (first_win)
		return GameStatus::PLAYER_FIRST_WIN;

	if (second_win)
		return GameStatus::PLAYER_SECOND_WIN;

	if (CheckUnusedCells())
		return GameStatus::PROCESS;

	return GameStatus::DRAW;
}

Turn GameMap::GetTurn() {
	if (ROW_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN_ > GameMapConstant::CELL_COORD_MAX");

	if (COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN_ > GameMapConstant::CELL_COORD_MAX");

	if (CheckGameStatus() != GameStatus::PROCESS)
		return Turn::END_GAME;

	unsigned int first_flags_count  = 0,
				 second_flags_count = 0;

	for (CellCoord row = 0; row < COLUMN_LEN_; ++row)
		for (CellCoord column = 0; column < ROW_LEN_; ++column)
			if (GetCell(row, column) == CellFlag::PLAYER_FIRST)
				first_flags_count++;
			else if (GetCell(row, column) == CellFlag::PLAYER_SECOND)
				second_flags_count++;

	if (abs(static_cast<int>(first_flags_count) - 
		    static_cast<int>(second_flags_count)) > 1 || 
		first_flags_count < second_flags_count)
	{
		throw std::runtime_error("Incorrect GameMap");
	}

	if (first_flags_count > second_flags_count)
		return Turn::PLAYER_SECOND_TURN;

	return Turn::PLAYER_FIRST_TURN;
}

GameMapStorage& GameMap::GetStorage() {
	return storage_;
}