#pragma once

#include "../Player/Player.hpp"

class Computer : Player {
public:
	GameStatus DoTurn();

private:
	GameStatus Set(const CellCoord, const CellCoord);
};