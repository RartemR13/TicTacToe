#include "Computer.hpp"

#include <stdexcept>

Computer::Computer(GameMap& game_map, const CellFlag player_flag, const Turn turn) :
	Player(game_map, player_flag, turn)
{}

GameStatus Computer::DoTurn(Window& window, void (*Draw)(CellCoord, CellCoord, Window&)) {
	if (game_map_.GetTurn() == Turn::END_GAME)
		throw std::runtime_error("Game was end");

	for (CellCoord row = 0; row < game_map_.COLUMN_LEN_; ++row)
		for (CellCoord column = 0; column < game_map_.ROW_LEN_; ++column)
			if (game_map_.GetCell(row, column) == CellFlag::UNUSED)
				return Set(row, column, window, Draw);

	return GameStatus::INCORRECT;
}