#include "GameMap.hpp"

#include <stdexcept> //для бросания исключений

GameMap::GameMap() {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	storage_.resize(GameMapConstant::COLUMN_LEN, 
					std::vector<Cell>(GameMapConstant::ROW_LEN));
}

void GameMap::SetCell(const CellCoord row, const CellCoord column, 
					  const CellFlag flag) 
{
	if (row >= GameMapConstant::ROW_LEN)
		throw std::invalid_argument("row >= ROW_LEN");

	if (column >= GameMapConstant::COLUMN_LEN)
		throw std::invalid_argument("column >= COLUMN_LEN");

	storage_[row][column].SetFlag(flag);
}

CellFlag GameMap::GetCell(const CellCoord row, const CellCoord column) {
	if (row >= GameMapConstant::ROW_LEN)
		throw std::invalid_argument("row >= ROW_LEN");

	if (column >= GameMapConstant::COLUMN_LEN)
		throw std::invalid_argument("column >= COLUMN_LEN");

	return storage_[row][column].GetFlag();	
}

bool GameMap::CheckRowsGameStatus(const CellFlag check_flag) {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	for (CellCoord row = 0; row < GameMapConstant::COLUMN_LEN; ++row) {
		unsigned char cur_streak = 0;

		for (CellCoord column = 0; column < GameMapConstant::ROW_LEN; ++column) {
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}

	return false;
}

bool GameMap::CheckColumnsGameStatus(const CellFlag check_flag) {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	for (CellCoord column = 0; column < GameMapConstant::ROW_LEN; ++column) {
		unsigned char cur_streak = 0;

		for (CellCoord row = 0; row < GameMapConstant::COLUMN_LEN; ++row) {
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}	

	return false;
}

bool GameMap::CheckMainDiagonalCollinearsGameStatus(const CellFlag check_flag) {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	for (CellCoord start_row = 0; start_row < GameMapConstant::COLUMN_LEN; ++start_row) {
		CellCoord column = 0;
		unsigned char cur_streak = 0;

		for (CellCoord row = start_row; 
			 row < GameMapConstant::COLUMN_LEN && column < GameMapConstant::ROW_LEN;
			 ++row, ++column) 
		{
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}

	for (CellCoord start_column = 0; start_column < GameMapConstant::ROW_LEN; ++start_column) {
		CellCoord row = 0;
		unsigned char cur_streak = 0;

		for (CellCoord column = start_column;
			 row < GameMapConstant::COLUMN_LEN && column < GameMapConstant::ROW_LEN;
			 ++row, ++column) 
		{
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}

	return false;
}

bool GameMap::CheckSideDiagonalCollinearsGameStatus(const CellFlag check_flag) {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	if (GameMapConstant::ROW_LEN == 0)
		return false;

	for (CellCoord start_row = 0; start_row < GameMapConstant::COLUMN_LEN; ++start_row) {
		CellCoord column = GameMapConstant::ROW_LEN - 1;
		unsigned char cur_streak = 0;

		for (CellCoord row = start_row; 
			 row < GameMapConstant::COLUMN_LEN && column >= 0;
			 ++row, --column) 
		{
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}

	for (CellCoord start_column = GameMapConstant::ROW_LEN - 1; start_column >= 0; --start_column) {
		CellCoord row = 0;
		unsigned char cur_streak = 0;

		for (CellCoord column = start_column;
			 row < GameMapConstant::COLUMN_LEN && column >= 0;
			 ++row, --column) 
		{
			if (GetCell(row, column) == check_flag)
				cur_streak++;
			else
				cur_streak = 0;

			if (cur_streak == GameMapConstant::WIN_STREAK_SIZE)
				return true;
		}
	}

	return false;
}

bool GameMap::CheckUnusedCells() {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	for (CellCoord row = 0; row < GameMapConstant::COLUMN_LEN; ++row)
		for (CellCoord column = 0; column < GameMapConstant::ROW_LEN; ++column)
			if (GetCell(row, column) == CellFlag::UNUSED)
				return true;

	return false;	
}

GameStatus GameMap::CheckGameStatus() {
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	bool first_win  = false,
		 second_win	= false;

	first_win = (CheckRowsGameStatus(CellFlag::PLAYER_FIRST) || 
				 CheckColumnsGameStatus(CellFlag::PLAYER_FIRST) ||
				 CheckMainDiagonalCollinearsGameStatus(CellFlag::PLAYER_FIRST) || 
				 CheckSideDiagonalCollinearsGameStatus(CellFlag::PLAYER_FIRST));

	second_win = (CheckRowsGameStatus(CellFlag::PLAYER_SECOND) || 
				  CheckColumnsGameStatus(CellFlag::PLAYER_SECOND) ||
				  CheckMainDiagonalCollinearsGameStatus(CellFlag::PLAYER_SECOND) || 
				  CheckSideDiagonalCollinearsGameStatus(CellFlag::PLAYER_SECOND));

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
	if (GameMapConstant::ROW_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("ROW_LEN > CELL_COORD_MAX");

	if (GameMapConstant::COLUMN_LEN > GameMapConstant::CELL_COORD_MAX)
		throw std::runtime_error("COLUMN_LEN > CELL_COORD_MAX");

	if (CheckGameStatus() != GameStatus::PROCESS)
		return Turn::END_GAME;

	unsigned int first_flags_count  = 0,
				 second_flags_count = 0;

	for (CellCoord row = 0; row < GameMapConstant::COLUMN_LEN; ++row)
		for (CellCoord column = 0; column < GameMapConstant::ROW_LEN; ++column)
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