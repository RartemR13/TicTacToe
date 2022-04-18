#include "Game.hpp"

Game::Game(GameMode game_mode) :
	window_(Window(50 * 19 + 34, 50 * 19 + 34, "TicTacToe")),
	game_map_(GameMap()),
	game_mode_(game_mode)
{
	window_.Fill(255, 255, 255);
}

void Game::DrawNet() {
	for (int i = 0; i < 18; ++i) {
		window_.DrawVerticalLine(i * 52 + 50, 0, 0, 0);
		window_.DrawVerticalLine(i * 52 + 51, 0, 0, 0);

		window_.DrawGorizontalLine(i * 52 + 50, 0, 0, 0);
		window_.DrawGorizontalLine(i * 52 + 51, 0, 0, 0);
	}

	window_.Sleep(15000);
}