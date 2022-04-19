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

	Window  window_;
	GameMap game_map_;
	GameMode game_mode_;

	Player player_first_;
	Player player_second_;
	Computer computer_;
};