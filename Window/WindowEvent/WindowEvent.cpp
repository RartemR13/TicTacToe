#include "WindowEvent.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

std::pair<unsigned short, unsigned short> ClickEvent::GetClick() {
	return click_;
}

EventType WindowEvent::Type() {
	return type_;
}

ClickEvent::ClickEvent(unsigned short x, unsigned short y) :
	WindowEvent(),
	click_(std::make_pair(x, y))
{
	type_ = EventType::CLICK_EVENT;
}

QuitEvent::QuitEvent() :
	WindowEvent()
{
	type_ = EventType::QUIT_EVENT;
}