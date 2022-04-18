#pragma once

#include "../GameMap/GameMap.hpp"
#include "../Window/Window.hpp"
#include "../Player/Player.hpp"
#include "../Computer/Computer.hpp"

enum GameMode {
	PVP_MODE, 
	COMPUTER_MODE
};

class Game {
public:
	Game(GameMode);

	void StartGame();

private:

	void DrawNet();

	void DrawX(CellCoord, CellCoord);
	void Draw0(CellCoord, CellCoord);

	Window  window_;
	GameMap game_map_;
	GameMode game_mode_;
};