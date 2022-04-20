#include "Game/Game.hpp"

int main() {

	Game game(GameMode::COMPUTER_MODE, 4, 4, 4);
	game.StartGame();

	return 0;
}