#pragma once

#include "../GameMap/GameMap.hpp"

class Player {
public:
	Player(GameMap&, const CellFlag, const Turn);

	GameStatus Set(const CellCoord, const CellCoord);
private:
	GameMap& game_map_;
	const CellFlag player_flag_;
	const Turn turn_;
};