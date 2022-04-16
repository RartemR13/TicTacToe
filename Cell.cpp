#include "Cell.hpp"

Cell::Cell() :
	flag_(CellFlag::UNUSED) //по умолчанию клетка пустая
{}

void Cell::SetFlag(const CellFlag flag) {
	flag_ = flag;
}

CellFlag Cell::GetFlag() {
	return flag_;
}
