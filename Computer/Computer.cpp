#include "Computer.hpp"
#include "../Liner/Liner.hpp"

#include <stdexcept>
#include <exception>
#include <iostream>

Computer::Computer(GameMap& game_map, const CellFlag player_flag, const Turn turn) :
	Player(game_map, player_flag, turn)
{}

std::pair<CellCoord, CellCoord> GetWinCoords(GameMap& game_map, CellFlag flag) {
	Liner liner(game_map.GetStorage());

	auto line = liner.Next();
	while (line != nullptr) {
		CellCoord l = 0, r = game_map.WIN_STREAK_SIZE_;
		while (r <= line->size()) {
			unsigned int cur_streak = 0;

			for (CellCoord it = l; it < r; ++it)
				if ((*line)[it].GetFlag() == flag)
					cur_streak++;

			std::pair<CellCoord, CellCoord> ret_coords;
			bool do_ret = false;

			if (cur_streak == game_map.WIN_STREAK_SIZE_ - 1) {
				for (CellCoord it = l; it < r; ++it)
					if ((*line)[it].GetFlag() == CellFlag::UNUSED) {
						do_ret = true;
						ret_coords = liner.GetCoords(it);
						break;
					}
			}

			if (do_ret) {
				delete line;
				//std::cout << (int)ret_coords.first << " " << (int)ret_coords.second << std::endl;
				return ret_coords;
			}

			l++, r++;
		}

		delete line;
		line = liner.Next();
	}
	
	throw std::runtime_error("Win coords not exist");
}

std::pair<CellCoord, CellCoord> GetNeighCoords(GameMap& game_map, CellFlag flag) {
	for (CellCoord row = 0; row < game_map.COLUMN_LEN_; ++row)
		for (CellCoord column = 0; column < game_map.ROW_LEN_; ++column)
			if (game_map.GetCell(row, column) == flag) {
				if (row > 0 && game_map.GetCell(row-1, column) == CellFlag::UNUSED)
					return std::make_pair(row-1, column);

				if (row+1 < game_map.COLUMN_LEN_ && game_map.GetCell(row+1, column) == CellFlag::UNUSED)
					return std::make_pair(row+1, column);

				if (column > 0 && game_map.GetCell(row, column-1) == CellFlag::UNUSED)
					return std::make_pair(row, column-1);

				if (column+1 < game_map.ROW_LEN_ && game_map.GetCell(row, column+1) == CellFlag::UNUSED)
					return std::make_pair(row, column+1);


				if (row > 0 && column > 0 && game_map.GetCell(row-1, column-1) == CellFlag::UNUSED)
					return std::make_pair(row-1, column-1);

				if (row+1 < game_map.COLUMN_LEN_ && column > 0 && game_map.GetCell(row+1, column-1) == CellFlag::UNUSED)
					return std::make_pair(row+1, column-1);

				if (row > 0 && column+1 < game_map.ROW_LEN_ && game_map.GetCell(row-1, column+1) == CellFlag::UNUSED)
					return std::make_pair(row-1, column+1);

				if (row+1 < game_map.COLUMN_LEN_ && column+1 < game_map.ROW_LEN_ && game_map.GetCell(row+1, column+1) == CellFlag::UNUSED)
					return std::make_pair(row+1, column+1);				
			}

	throw std::runtime_error("Neigh coords not exist");
}

GameStatus Computer::DoTurn(Window& window, void (*Draw)(CellCoord, CellCoord, Window&)) {
	if (game_map_.GetTurn() == Turn::END_GAME)
		throw std::runtime_error("Game was end");

	int mid_row    = game_map_.COLUMN_LEN_ / 2,
		mid_column = game_map_.ROW_LEN_ / 2;

	if (game_map_.GetCell(mid_row, mid_column) == CellFlag::UNUSED)
		return Set(mid_row, mid_column, window, Draw);

	try {
		auto win_coords = GetWinCoords(game_map_, CellFlag::PLAYER_FIRST);
		return Set(win_coords.first, win_coords.second, window, Draw);
	} catch(std::exception){}

	try {
		auto win_coords = GetWinCoords(game_map_, CellFlag::PLAYER_SECOND);
		return Set(win_coords.first, win_coords.second, window, Draw);
	} catch(std::exception){}

	try {
		auto neigh_coords = GetNeighCoords(game_map_, CellFlag::PLAYER_FIRST);
		return Set(neigh_coords.first, neigh_coords.second, window, Draw);
	} catch(std::exception){}

	try {
		auto neigh_coords = GetNeighCoords(game_map_, CellFlag::PLAYER_SECOND);
		return Set(neigh_coords.first, neigh_coords.second, window, Draw);
	} catch(std::exception){}

	return GameStatus::INCORRECT;
}