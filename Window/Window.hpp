#pragma once

#include <string>
#include <vector>

#include "WindowEvent/WindowEvent.hpp"

enum WindowConst {
	MAX_HEIGHT = 1080, 
	MAX_WIDTH  = 1920
};

typedef unsigned short WindowSize;

class Window {
public:
	Window(const WindowSize, const WindowSize, std::string);
	~Window();
	void Sleep(unsigned int); //Заснуть на кол-во секунд в аргументе
	void Fill(unsigned char, unsigned char, unsigned char); //Закрасить окно в цвет r, g, b

	void DrawBMP(std::string, unsigned short, unsigned short); //Нарисовать изображение
//Путь к изображению, координата по x, координата по y

	WindowEvent* WaitEvent(); //Получить ивент
	void DeleteEvents(); //Удалить сохраненные ивенты

	void DrawCircle(unsigned short, unsigned short,
					unsigned short, unsigned short,
					unsigned char, unsigned char, unsigned char); //Нарисовать круг

//Координаты левого нижнего угла
//Координаты правого верхнего угла
//Цвет круга

	void DrawFrame(unsigned short, unsigned short,
				   unsigned short, unsigned short,
				   unsigned char, unsigned char, unsigned char);

//Нарисовать рамку (координаты углов, цвет)

	void DrawSegment(unsigned short, unsigned short,
					 unsigned short, unsigned short,
					 unsigned char, unsigned char, unsigned char);
//Нарисовать отрезок (координаты концов, цвет)

	void UpdateSurface();

//Обновить экран (после любого изменения, чтобы пользователь его увидел, надо обновить)

	unsigned short width_, //ширина окна
				   height_; //высота окна
private:
	Window() = default; //Конструктор по умолчанию (все поля по умолчанию)

	void SetPixel(unsigned short, unsigned short,
			  	  unsigned char, unsigned char, unsigned char);

//Поставить пиксель (координаты, цвет)

	void* window_; //указатель на структуру окно в SDL2
	void* surface_; //указатель на стркутуру поверхность

	unsigned int windowID_; //Юзелес

	std::vector<WindowEvent*> events_; //Массив ивентов
};