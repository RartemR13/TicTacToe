install: Cell/Cell.cpp Cell/Cell.hpp \
		 GameMap/GameMap.hpp GameMap/GameMap.cpp \
		 Player/Player.cpp Player/Player.hpp \
		 Window/Window.cpp Window/Window.hpp
	g++ -O2 -std=c++17 Cell/Cell.cpp -c -o Cell.o #-fsanitize=address
	g++ -O2 -std=c++17 Liner/Liner.cpp -c -o Liner.o #-fsanitize=address
	g++ -O2 -std=c++17 GameMap/GameMap.cpp -c -o GameMap.o #-fsanitize=address
	g++ -O2 -std=c++17 Player/Player.cpp -c -o Player.o #-fsanitize=address
	g++ -O2 -std=c++17 Computer/Computer.cpp -c -o Computer.o #-fsanitize=address
	g++ -O2 -std=c++17 Window/Window.cpp -c -o Window.o #-fsanitize=address
	g++ -O2 -std=c++17 Window/WindowEvent/WindowEvent.cpp -c -o WindowEvent.o #-fsanitize=address
	g++ -O2 -std=c++17 Game/Game.cpp -c -o Game.o #-fsanitize=address
	g++ -O2 -std=c++17 Menu/Menu.cpp -c -o Menu.o #-fsanitize=address
	g++ -O2 -std=c++17 test.cpp -lSDL2 -lSDL2main -o test Window.o WindowEvent.o Game.o GameMap.o Cell.o Player.o Computer.o Menu.o Liner.o #-fsanitize=address

clean:
	rm *.o || true
	rm test || true
	