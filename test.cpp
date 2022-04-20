#include "Game/Game.hpp"
#include "Menu/Menu.hpp"

int main() {

	MenuChoice game_choice;
	{
		Menu menu;
		game_choice = menu.WaitChoice();
	}

	switch(game_choice) {
		case MenuChoice::PVP_CHOICE:
		{
			Game game(GameMode::PVP_MODE);
			game.StartGame();
			break;
		}

		case MenuChoice::COMPUTER_CHOICE:
		{
			Game game(GameMode::COMPUTER_MODE);
			game.StartGame();
			break;
		}
	}
	
	return 0;
}