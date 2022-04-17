#pragma once

#include <string>

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
	void Sleep(unsigned int);
	void Fill(unsigned char, unsigned char, unsigned char);

	WindowEvent WaitEvent();
private:
	Window() = default;

	void* window_;
	void* surface_;

	unsigned int windowID_;
};