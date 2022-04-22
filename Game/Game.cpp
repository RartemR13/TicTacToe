#include "Game.hpp"
#include "../Liner/Liner.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>

void DrawX(CellCoord row, CellCoord column, Window& window) {
	window.DrawSegment(((int)column)*52 + 5, ((int)row)*52 + 5, 
					   ((int)column)*52 + 5 + 42, ((int)row)*52 + 5 + 42,
					   255, 0, 0);

	window.DrawSegment(((int)column)*52 + 47, ((int)row)*52 + 5,
					   ((int)column)*52 + 47 - 42, ((int)row)*52 + 5 + 42,
					   255, 0, 0);

	window.UpdateSurface();
}

void Draw0(CellCoord row, CellCoord column, Window& window) {
	window.DrawCircle(row*52 + 5, column*52 + 5, row*52 + 47, column*52 + 47, 0, 0, 255);
	window.UpdateSurface();
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

	window_.UpdateSurface();
}

void Game::DrawNet() {
	for (int i = 0; i <= game_map_.ROW_LEN_; ++i) {
		window_.DrawSegment(i * 52, 0, i * 52, window_.height_ - 1, 0, 0, 0);
		window_.DrawSegment(i * 52 + 1, 0, i * 52 + 1, window_.height_ - 1, 0, 0, 0);	
	}

	for (int i = 0; i <= game_map_.COLUMN_LEN_; ++i) {
		window_.DrawSegment(0, i * 52, window_.width_ - 1, i * 52, 0, 0, 0);
		window_.DrawSegment(0, i * 52 + 1, window_.width_ - 1, i * 52 + 1, 0, 0, 0);		
	}

	window_.UpdateSurface();
}

bool IsCellClick(std::pair<unsigned short, unsigned short> click) {
	return click.first % 52 > 1 && click.second % 52 > 1; 
}

CellCoord GetClickRow(std::pair<unsigned short, unsigned short> click) {
	return click.second / 52; 
}

CellCoord GetClickColumn(std::pair<unsigned short, unsigned short> click) {
	return click.first / 52;
}

void Game::DrawWin(CellFlag flag) {
	Liner liner(game_map_.GetStorage());

	auto line = liner.Next();
	while (line != nullptr) {
		int l = 0, r = game_map_.WIN_STREAK_SIZE_;
		while (r <= line->size()) {
			unsigned int cur_streak = 0;
			for (int i = l; i < r; ++i) {
				if ((*line)[i].GetFlag() == flag)
					cur_streak++;
			}

			if (cur_streak == game_map_.WIN_STREAK_SIZE_) {
				std::pair<int, int> first_rect  = liner.GetCoords(l),
					 				second_rect = liner.GetCoords(r-1);

				delete line;

				first_rect.first *= 52;
				first_rect.first += 52 / 2;

				first_rect.second *= 52;
				first_rect.second += 52 / 2;

				second_rect.first *= 52;
				second_rect.first += 52 / 2;

				second_rect.second *= 52;
				second_rect.second += 52 / 2;

//				std::cout << first_rect.first << " " << first_rect.second << std::endl;

				window_.DrawSegment(first_rect.second-1, first_rect.first,
									second_rect.second-1, second_rect.first,
									0, 255, 0);

				window_.DrawSegment(first_rect.second, first_rect.first-1,
									second_rect.second, second_rect.first-1,
									0, 255, 0);

				window_.DrawSegment(first_rect.second, first_rect.first,
									second_rect.second, second_rect.first,
									0, 255, 0);


				window_.UpdateSurface();

				return;	
			}

			l++, r++;
		}

		delete line;
		line = liner.Next();
	}

	throw std::runtime_error("Not win");
}

void Game::StartGame() {

	DrawNet();
	bool quit = false,
		 end_game = false;

	while (true) {
		WindowEvent* event = window_.WaitEvent();
		if (event == nullptr)
			continue;

		switch(event->Type()) {
			case EventType::QUIT_EVENT:
				quit = true;
				break;

			case EventType::CLICK_EVENT:
				if (end_game)
					break;

				auto click = event->GetClick();
				CellCoord row = GetClickRow(click);
				CellCoord column = GetClickColumn(click);

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

					switch(game_map_.CheckGameStatus()) {
						case GameStatus::INCORRECT:
							throw std::runtime_error("Something wrong in game");
							break;

						case GameStatus::PLAYER_FIRST_WIN:
							end_game = true;
							DrawWin(CellFlag::PLAYER_FIRST);
							break;

						case GameStatus::PLAYER_SECOND_WIN:
							end_game = true;
							DrawWin(CellFlag::PLAYER_SECOND);
							break;

						case GameStatus::DRAW:
							end_game = true;
							break;
					}
				}
				break;
		}

		window_.DeleteEvents();

		if (quit)
			break;
	}
}
	