#pragma once

#include "../Window/Window.hpp"

enum MenuChoice {
	PVP_CHOICE,
	COMPUTER_CHOICE,
	QUIT_CHOICE
};

class Menu {
public:
	Menu();

	MenuChoice WaitChoice();
private:
	Window window_;
};