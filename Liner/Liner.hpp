#pragma once

#include <vector>
#include <utility>

#include "../Cell/Cell.hpp"

class Liner {
public:
	Liner(std::vector<std::vector<Cell>>&);

	std::vector<Cell>* Next();
	std::pair<CellCoord, CellCoord> GetCoords(CellCoord);

private:
	std::vector<std::vector<Cell>> matrix_;
	int liner_status_;

	CellCoord cur_line_num_;
};