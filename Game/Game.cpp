#include "Game.hpp"

#include <iostream>

void DrawX(CellCoord row, CellCoord column, Window& window) {
	window.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 5, 42, 255, 0, 0);
	window.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 6, 42, 255, 0, 0);

	window.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 47, -42, 255, 0, 0);
	window.DrawDiagonalLine(((int)row)*52 + 5, ((int)column)*52 + 46, -42, 255, 0, 0);
}

void Draw0(CellCoord row, CellCoord column, Window& window) {
	window.DrawCircle(row*52 + 5, column*52 + 5, row*52 + 47, column*52 + 47, 0, 0, 255);
}

Game::Game(GameMode game_mode, 
		   CellCoord width_cells, CellCoord height_cells, CellCoord win_streak_size) :
	window_(Window(50 * width_cells + 2 + (width_cells*2), 50 * height_cells + 2 + (height_cells*2), "TicTacToe")),
	game_map_(GameMap(width_cells, height_cells, win_streak_size)),
	game_mode_(game_mode),
	player_first_(Player(game_map_, CellFlag::PLAYER_FIRST, Turn::PLAYER_FIRST_TURN)),
	player_second_(Player(game_map_, CellFlag::PLAYER_SECOND, Turn::PLAYER_SECOND_TURN)),
	computer_(Computer(game_map_, CellFlag::PLAYER_FIRST, Turn::PLAYER_FIRST_TURN))
{
	window_.Fill(255, 255, 255);
	
	if (game_mode == GameMode::COMPUTER_MODE)
		computer_.DoTurn(window_, DrawX);
}

void Game::DrawNet() {
	for (int i = 0; i <= game_map_.ROW_LEN_; ++i) {
		window_.DrawVerticalLine(i * 52, 0, 0, 0);
		window_.DrawVerticalLine(i * 52 + 1, 0, 0, 0);	
	}

	for (int i = 0; i <= game_map_.COLUMN_LEN_; ++i) {
		window_.DrawGorizontalLine(i * 52, 0, 0, 0);
		window_.DrawGorizontalLine(i * 52 + 1, 0, 0, 0);		
	}
}



bool IsCellClick(std::pair<unsigned short, unsigned short> click) {
	return click.first % 52 > 1 && click.second % 52 > 1; 
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

				if (IsCellClick(click) && game_map_.GetCell(row, column) == CellFlag::UNUSED) {
					if (game_mode_ == GameMode::PVP_MODE) {
						if (game_map_.GetTurn() == Turn::PLAYER_FIRST_TURN)
							player_first_.Set(row, column, window_, DrawX);
						else if (game_map_.GetTurn() == Turn::PLAYER_SECOND_TURN)
							player_second_.Set(row, column, window_, Draw0);
					} else if (game_mode_ == GameMode::COMPUTER_MODE) {
						if (game_map_.GetTurn() == Turn::PLAYER_SECOND_TURN) {
							if (player_second_.Set(row, column, window_, Draw0) == GameStatus::PROCESS)
								computer_.DoTurn(window_, DrawX);
						}
					}
				}
				break;
		}

		window_.DeleteEvents();

		if (quit)
			break;
	}
}
	