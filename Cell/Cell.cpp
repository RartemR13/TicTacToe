#include "Cell.hpp"

#include <stdexcept> //Заголочный файл, в котором определены исключения

Cell::Cell() : //конструктор
	flag_(CellFlag::UNUSED) //по умолчанию клетка пустая
{}

void Cell::SetFlag(const CellFlag flag) {
	if (flag_ != CellFlag::UNUSED)
		throw std::runtime_error("Cell is occupied"); //Бросаю исключение, если клетка занята

	flag_ = flag; //Ставлю в клетку значение
}

CellFlag Cell::GetFlag() {
	return flag_; //Возвращаю поле флаг
}
