#include "Window/Window.hpp"

int main() {

	Window window(50*19, 50*19, "test");
	window.Fill(255, 255, 255);

	while (true) {
		auto event = window.WaitEvent();
		bool quit = false;

		switch (event.Type()) {
			case EventType::QUIT_EVENT:
				quit = true;
				break;
		}

		if (quit)
			break;
	}

	return 0;
}