#include "Window.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

#include <iostream>

Window::Window(const WindowSize width, const WindowSize height, std::string title) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error(SDL_GetError());

	width_  = width;
	height_ = height;

	window_ = SDL_CreateWindow(title.c_str(), 
							   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							   width, height, 
							   SDL_WINDOW_SHOWN);
	if (window_ == nullptr)
		throw std::runtime_error(SDL_GetError());

	surface_ = SDL_GetWindowSurface(static_cast<SDL_Window*>(window_));
	if (surface_ == nullptr)
		throw std::runtime_error(SDL_GetError());

	windowID_ = SDL_GetWindowID(static_cast<SDL_Window*>(window_));
	if (windowID_ == 0)
		throw std::runtime_error(SDL_GetError());
}

Window::~Window() {
	SDL_DestroyWindow(static_cast<SDL_Window*>(window_));
	SDL_Quit();
}

void Window::Sleep(unsigned int delay) {
	SDL_Delay(delay);
}

void Window::Fill(unsigned char r, unsigned char g, unsigned char b) {
	SDL_FillRect(static_cast<SDL_Surface*>(surface_), 
				 NULL, 
				 SDL_MapRGB(static_cast<SDL_Surface*>(surface_)->format, r, g, b));

	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_));
}

void Window::SetPixel(unsigned short x, unsigned short y,
			  		  unsigned char r, unsigned char g, unsigned char b) 
{
	Uint32 * const target_pixel = (unsigned int*)((unsigned char*)(static_cast<SDL_Surface*>(surface_)->pixels)
	                                         + y * static_cast<SDL_Surface*>(surface_)->pitch
	                                         + x * static_cast<SDL_Surface*>(surface_)->format->BytesPerPixel);

	unsigned char pixel[4] = {};

	pixel[0] = b;
	pixel[1] = g;
	pixel[2] = r;

	*target_pixel = *(unsigned int*)pixel;
}

void Window::DrawCircle(unsigned short x1, unsigned short y1,
						unsigned short x2, unsigned short y2,
						unsigned char r, unsigned char g, unsigned char b)
{
	for (int i = x1; i <= x2; ++i)
		for (int j = y1; j <= y2; ++j)
			if (19 >= 
				abs(((x2 + x1) / 2ll - i) * ((x2 + x1) / 2ll - i) + 
				((y2 + y1) / 2ll - j) * ((y2 + y1) / 2ll - j) - 
				((x2 - x1) / 2ll) * ((x2 - x1) / 2ll))) 
			{
				SetPixel(j, i, r, g, b);
			}

	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_));
}

void Window::DrawFrame(unsigned short x1, unsigned short y1,
			   		   unsigned short x2, unsigned short y2,
			   		   unsigned char r, unsigned char g, unsigned char b) 
{

	DrawSegment(x1, y1, x1, y2, r, g, b);
	DrawSegment(x2, y2, x2, y1, r, g, b);

	DrawSegment(x2, y2, x1, y2, r, g, b);
	DrawSegment(x1, y1, x2, y1, r, g, b);

	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_));
}

WindowEvent* Window::WaitEvent() {
	SDL_Event event = {};
	if (SDL_WaitEvent(&event) == 0)
		throw std::runtime_error(SDL_GetError());

	switch(event.type) {
		case SDL_QUIT:
			events_.push_back(new QuitEvent());
			return &(*events_.back());
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				events_.push_back(new ClickEvent(event.button.x, event.button.y));
				return &(*events_.back());
			}
			break;
	}

	return nullptr;
}

void Window::DeleteEvents() {
	while (!events_.empty()) {
		delete events_.back();
		events_.pop_back();
	}
}

void Window::DrawBMP(std::string path, unsigned short x, unsigned short y) {
	SDL_Surface *img = SDL_LoadBMP(path.c_str());
	if (img == nullptr)
		throw std::runtime_error(SDL_GetError());

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	if (SDL_BlitSurface(img, NULL, static_cast<SDL_Surface*>(surface_), &dest) != 0)
		throw std::runtime_error(SDL_GetError());

	SDL_FreeSurface(img);
	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_));
}

void Window::DrawSegment(unsigned short x1, unsigned short y1,
						 unsigned short x2, unsigned short y2,
						 unsigned char r, unsigned char g, unsigned char b)
{

	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}


	auto dl = [&](int x1_, int y1_, int x2_, int y2_) {
				 	return (x1_ - x2_) * (x1_ - x2_) + (y1_ - y2_) * (y1_ - y2_); 
				 };

	int eps = sqrt(dl(x1, y1, x2, y2));

	int A = (y1 - y2),
		B = -(x1 - x2);

	int C = -(A*x1 + B*y1);
	

	if (y1 == y2) {
		for (int i = x1; i <= x2; ++i)
			SetPixel(i, y1, r, g, b);
	} else if (x1 == x2) {
		if (y1 > y2)
			std::swap(y1, y2);

		for (int i = y1; i <= y2; ++i)
			SetPixel(x1, i, r, g, b);
	} else { 
		int last = y1;
		int cur = y1;
		for (int i = x1+1; i <= x2; ++i) {
			for (int j = std::max(last - eps, 0); j <= std::min(last + eps, height_-1); ++j)
				if (abs(B*j + A*i + C) < eps) {
					SetPixel(i, j, r, g, b);
					if (abs(B*j + A*i + C) + eps / 3 < abs(B*cur + A*i + C) && y1 > y2)
						cur = j;
					else if (abs(B*j + A*i + C)  < abs(B*cur + A*i + C) + eps / 3)
						cur = j;
				}

			last = cur;
		}
	}

	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_));
}