#include "Computer.hpp"

#include <stdexcept>

GameStatus Computer::DoTurn() {
	if (game_map_.GetTurn() == Turn::END_GAME)
		throw std::runtime_error("Game was end");

	for (CellCoord row = 0; row < GameMapConstant::COLUMN_LEN; ++row)
		for (CellCoord column = 0; column < GameMapConstant::ROW_LEN; ++column)
			if (game_map_.GetCell(row, column) == CellFlag::UNUSED)
				return Set(row, column);

	return GameStatus::INCORRECT;
}