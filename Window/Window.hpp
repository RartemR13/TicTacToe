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


	void DrawVerticalLine(unsigned short,
						  unsigned char, unsigned char, unsigned char);

	void DrawGorizontalLine(unsigned short,
							unsigned char, unsigned char, unsigned char);
private:
	Window() = default;

	void SetPixel(unsigned short, unsigned short,
			  	  unsigned char, unsigned char, unsigned char);

	unsigned short width_,
				   height_;

	void* window_;
	void* surface_;

	unsigned int windowID_;
};