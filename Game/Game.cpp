#include "Game.hpp"

#include <iostream>

Game::Game(GameMode game_mode) :
	window_(Window(50 * 19 + 40, 50 * 19 + 40, "TicTacToe")),
	game_map_(GameMap()),
	game_mode_(game_mode)
{
	window_.Fill(255, 255, 255);
}

void Game::DrawNet() {

	
	for (int i = 0; i < 20; ++i) {
		window_.DrawVerticalLine(i * 52, 0, 0, 0);
		window_.DrawVerticalLine(i * 52 + 1, 0, 0, 0);

		window_.DrawGorizontalLine(i * 52, 0, 0, 0);
		window_.DrawGorizontalLine(i * 52 + 1, 0, 0, 0);
	}
}

void Game::DrawX(CellCoord row, CellCoord column) {
	window_.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 5, 42, 255, 0, 0);
	window_.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 6, 42, 255, 0, 0);

	window_.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 47, -42, 255, 0, 0);
	window_.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 46, -42, 255, 0, 0);
}

void Game::Draw0(CellCoord row, CellCoord column) {
	window_.DrawCircle(row*52 + 5, column*52 + 5, row*52 + 47, column*52 + 47, 0, 0, 255);
}


bool IsCellClick(std::pair<unsigned short, unsigned short> click) {
	return click.first % 52 && click.second % 52; 
}

CellCoord GetClickRow(std::pair<unsigned short, unsigned short> click) {
	return click.first / 52; 
}

CellCoord GetClickColumn(std::pair<unsigned short, unsigned short> click) {
	return click.second / 52;
}


void Game::StartGame() {

	DrawNet();
	bool quit = false;

	while (true) {
		WindowEvent* event = window_.WaitEvent();
		if (event == nullptr)
			continue;

		switch(event->Type()) {
			case EventType::QUIT_EVENT:
				quit = true;
				break;

			case EventType::CLICK_EVENT:
				auto click = event->GetClick();
				CellCoord row = GetClickRow(click);
				CellCoord column = GetClickColumn(click);

				std::cout << (int)row << " " << (int)column << std::endl;

				if (game_map_.GetCell(row, column) == CellFlag::UNUSED && IsCellClick(click)) {
					if (game_map_.GetTurn() == Turn::PLAYER_FIRST_TURN) {
						DrawX(row, column);
						game_map_.SetCell(row, column, CellFlag::PLAYER_FIRST);
					}
					else if (game_map_.GetTurn() == Turn::PLAYER_SECOND_TURN) {
						Draw0(row, column);
						game_map_.SetCell(row, column, CellFlag::PLAYER_SECOND);
					}
				}
				break;
		}

		window_.DeleteEvents();

		if (quit)
			break;
	}
}
	