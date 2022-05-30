#include "Liner.hpp"

#include <climits> //INT_MAX ...
#include <stdexcept> 

enum LinerStatus {
	ROW,
	COLUMN,
	MAIN_DIOGANAL_LOW,
	MAIN_DIOGANAL_UP,
	SIDE_DIOGANAL_LOW,
	SIDE_DIOGANAL_UP,
	END
};

Liner::Liner(std::vector<std::vector<Cell>>& matrix) :
	matrix_(matrix),
	liner_status_(LinerStatus::ROW),
	cur_line_num_(0)
{}

std::vector<Cell>* Liner::Next() {
	if (matrix_.size() == 0 || liner_status_ == LinerStatus::END) 
	{
		return nullptr;
	}

	std::vector<Cell>* ret = new std::vector<Cell>();
	switch(liner_status_) {
		case LinerStatus::ROW:
			for (CellCoord it = 0; it < matrix_[cur_line_num_].size(); ++it)
				ret->push_back(matrix_[cur_line_num_][it]);

			cur_line_num_++;
			if (cur_line_num_ == matrix_.size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;

		case LinerStatus::COLUMN:
			for (CellCoord it = 0; it < matrix_.size(); ++it)
				ret->push_back(matrix_[it][cur_line_num_]);

			cur_line_num_++;
			if (cur_line_num_ == matrix_[0].size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;

		case LinerStatus::MAIN_DIOGANAL_LOW:
			for (CellCoord row = cur_line_num_, column = 0; 
				 row < matrix_.size() && column < matrix_[row].size(); 
				 ++row, ++column)
			{
				ret->push_back(matrix_[row][column]);
			}

			cur_line_num_++;
			if (cur_line_num_ == matrix_.size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;

		case LinerStatus::MAIN_DIOGANAL_UP:
			for (CellCoord column = cur_line_num_, row = 0;
				 row < matrix_.size() && column < matrix_[row].size();
				 ++row, ++column)
			{
				ret->push_back(matrix_[row][column]);
			}

			cur_line_num_++;
			if (cur_line_num_ == matrix_[0].size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;

		case LinerStatus::SIDE_DIOGANAL_LOW:
			for (CellCoord column = matrix_[0].size() - 1, row = cur_line_num_;
				 row < matrix_.size() && column < UCHAR_MAX;
				 ++row, --column)
			{
				ret->push_back(matrix_[row][column]);
			}

			cur_line_num_++;
			if (cur_line_num_ == matrix_.size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;

		case LinerStatus::SIDE_DIOGANAL_UP:
			for (CellCoord column = matrix_[0].size() - cur_line_num_ - 1, row = 0;
				 row < matrix_.size() && column < UCHAR_MAX;
				 ++row, --column)
			{
				ret->push_back(matrix_[row][column]);
			}

			cur_line_num_++;
			if (cur_line_num_ == matrix_[0].size()) {
				liner_status_++;
				cur_line_num_ = 0;
			}
			break;
	}

	return ret;
}

std::pair<CellCoord, CellCoord> Liner::GetCoords(CellCoord ind) {
	auto liner_status = liner_status_;
	auto cur_line_num = cur_line_num_;

	if (liner_status == 0 && cur_line_num == 0)
		throw std::runtime_error("Empty matrix or not used Next()");

	if (cur_line_num == 0) {
		liner_status--;
		if (liner_status % 2 == 0)
			cur_line_num = matrix_.size() - 1;
		else
			cur_line_num_ = matrix_[0].size() - 1;
	} else {
		cur_line_num--;
	}

	switch(liner_status) {
		case LinerStatus::ROW:
			return std::make_pair(static_cast<CellCoord>(cur_line_num), 
								  static_cast<CellCoord>(ind));

		case LinerStatus::COLUMN:
			return std::make_pair(static_cast<CellCoord>(ind), 
								  static_cast<CellCoord>(cur_line_num));

		case LinerStatus::MAIN_DIOGANAL_LOW:
			return std::make_pair(static_cast<CellCoord>(cur_line_num + ind), 
								  static_cast<CellCoord>(ind));

		case LinerStatus::MAIN_DIOGANAL_UP:
			return std::make_pair(static_cast<CellCoord>(ind), 
								  static_cast<CellCoord>(cur_line_num + ind));

		case LinerStatus::SIDE_DIOGANAL_LOW:
			return std::make_pair(static_cast<CellCoord>(cur_line_num + ind), 
								  static_cast<CellCoord>(matrix_.size() - ind - 1));

		case LinerStatus::SIDE_DIOGANAL_UP:
			return std::make_pair(static_cast<CellCoord>(ind), 
								  static_cast<CellCoord>(matrix_.size() - ind - cur_line_num - 1));
	}

	throw std::runtime_error("Liner END");
}
