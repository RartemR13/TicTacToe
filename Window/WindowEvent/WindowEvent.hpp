#pragma once

#include <utility>

enum EventType {
	CLICK_EVENT,
	QUIT_EVENT,
	UNDEFINED_EVENT
};

class WindowEvent {
public:
	WindowEvent() = default;
	EventType Type();

	virtual std::pair<unsigned short, unsigned short> GetClick(){return {-1, -1};};
	virtual ~WindowEvent(){};
protected:
	EventType type_ = EventType::UNDEFINED_EVENT;
};

class ClickEvent : public WindowEvent {
public:
	std::pair<unsigned short, unsigned short> GetClick();
	ClickEvent(unsigned short, unsigned short);
private:
	ClickEvent() = default;
	std::pair<unsigned short, unsigned short> click_;
};

class QuitEvent : public WindowEvent {
public:
	QuitEvent();
};
