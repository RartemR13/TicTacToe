#pragma once

#include "../GameMap/GameMap.hpp"
#include "../Window/Window.hpp"

class Player {
public:
	Player(GameMap&, const CellFlag, const Turn);

	GameStatus Set(const CellCoord, const CellCoord, 
				   Window&, void (*)(CellCoord, CellCoord, Window&));
protected:
	GameMap& game_map_;
	const CellFlag player_flag_;
	const Turn turn_;
};