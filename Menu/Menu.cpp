#include "Menu.hpp"

#include <iostream>

Menu::Menu() :
	window_(700, 400, "Choice game mode")
{
	window_.Fill(255, 255, 255);

	window_.DrawBMP("computer.bmp", 400, 100);
	window_.DrawBMP("pvp.bmp", 100, 100);

	window_.DrawFrame(90, 90, 310, 310, 255, 255, 0);
	window_.DrawFrame(91, 91, 311, 311, 255, 255, 0);

	window_.DrawFrame(390, 90, 610, 310, 0, 0, 255);
	window_.DrawFrame(391, 91, 611, 311, 0, 0, 255);
}

MenuChoice Menu::WaitChoice() {
	while (true) {
		auto event = window_.WaitEvent();
		if (event == nullptr)
			continue;

		switch(event->Type()) {
			case EventType::QUIT_EVENT:
				return MenuChoice::QUIT_CHOICE;
				break;

			case EventType::CLICK_EVENT:
				auto click = event->GetClick();

				auto x = click.first,
					 y = click.second;

				if (x > 91 && x < 310 && y > 91 && y < 310)
					return MenuChoice::PVP_CHOICE;

				if (x > 391 && x < 610 && y > 91 && y < 310)
					return MenuChoice::COMPUTER_CHOICE;

				break;
		}

		window_.DeleteEvents();
	}
}