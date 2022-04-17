#include "Window.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

Window::Window(const WindowSize height, const WindowSize width, std::string title) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error(SDL_GetError());

	window_ = SDL_CreateWindow(title.c_str(), 
							   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
							   height, width, 
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

WindowEvent Window::WaitEvent() {
	SDL_Event event = {};
	if (SDL_WaitEvent(&event) == 0)
		throw std::runtime_error(SDL_GetError());

	switch(event.type) {
		case SDL_QUIT:
			return QuitEvent();
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				return ClickEvent(event.button.x, event.button.y);
			break;
	}

	return WindowEvent();
}