#include "Player.hpp"

#include <stdexcept>

Player::Player(GameMap& game_map, const CellFlag player_flag, const Turn turn) :
	game_map_(game_map),
	player_flag_(player_flag),
	turn_(turn)
{}

GameStatus Player::Set(const CellCoord row, const CellCoord column) {
	if (game_map_.GetTurn() != turn_)
		throw std::runtime_error("Another player's turn");

	game_map_.SetCell(row, column, player_flag_);

	return game_map_.CheckGameStatus();
}