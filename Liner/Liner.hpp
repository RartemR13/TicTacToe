#pragma once

#include <vector> //Аналог массива в C++
#include <utility> //там определен pair<..., ...>

#include "../Cell/Cell.hpp"

class Liner {
public:
	Liner(std::vector<std::vector<Cell>>&); //Конструктор, на вход принимает двумерный массив клеток

	std::vector<Cell>* Next(); //Получить линии матрицы
	std::pair<CellCoord, CellCoord> GetCoords(CellCoord); //Получить абсолютные координаты в матрице по относительной координате в линии
private:
	std::vector<std::vector<Cell>> matrix_; //сама матрица
	int liner_status_; //Статус

	CellCoord cur_line_num_; //номер линии
};