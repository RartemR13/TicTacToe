install: Cell/Cell.cpp Cell/Cell.hpp \
		 GameMap/GameMap.hpp GameMap/GameMap.cpp \
		 Player/Player.cpp Player/Player.hpp \
		 Window/Window.cpp Window/Window.hpp
	g++ Cell/Cell.cpp -c -o Cell.o
	g++ GameMap/GameMap.cpp -c -o GameMap.o
	g++ Player/Player.cpp -c -o Player.o
	g++ Computer/Computer.cpp -c -o Computer.o
	g++ Window/Window.cpp -c -o Window.o
	g++ Window/WindowEvent/WindowEvent.cpp -c -o WindowEvent.o
	g++ test.cpp -lSDL2 -lSDL2main -o test Window.o WindowEvent.o

clean:
	rm *.o || true
	rm test || true
	