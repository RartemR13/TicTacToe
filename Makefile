install: Cell/Cell.cpp Cell/Cell.hpp GameMap/GameMap.hpp GameMap/GameMap.cpp
	g++ Cell/Cell.cpp -c -o Cell.o
	g++ GameMap/GameMap.cpp -c -o GameMap.o

clean:
	rm Cell.o || true
	rm GameMap.o || true
	