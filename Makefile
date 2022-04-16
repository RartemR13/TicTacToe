install: Cell/Cell.cpp Cell/Cell.hpp GameMap/GameMap.hpp GameMap/GameMap.cpp Player/Player.cpp Player/Player.hpp
	g++ Cell/Cell.cpp -c -o Cell.o
	g++ GameMap/GameMap.cpp -c -o GameMap.o
	g++ Player/Player.cpp -c -o Player.o

clean:
	rm Cell.o || true
	rm GameMap.o || true
	rm Player.o || true
	