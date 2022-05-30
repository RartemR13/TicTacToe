#pragma once //include в файл будет производится лишь раз

enum CellFlag {
	UNUSED, 	  //если в клетке ни 0, ни X
	PLAYER_FIRST, //если в клетке X
	PLAYER_SECOND //если в клетке 0
};

typedef unsigned char CellCoord; //Макрос, CellCoord = unsigned char

//Класс клетка
class Cell {
public:
	Cell();

	void SetFlag(const CellFlag); //Поставить флаг в клетку
	CellFlag GetFlag();			  //Получить флаг

private:
	CellFlag flag_;				  //Поле, в котором храниться сам флаг
};