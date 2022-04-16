#include "Cell.hpp"

#include <stdexcept>

Cell::Cell() :
	flag_(CellFlag::UNUSED) //по умолчанию клетка пустая
{}

void Cell::SetFlag(const CellFlag flag) {
	if (flag_ != CellFlag::UNUSED)
		throw std::runtime_error("Cell is occupied");

	flag_ = flag;
}

CellFlag Cell::GetFlag() {
	return flag_;
}
