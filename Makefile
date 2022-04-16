install: Cell.cpp Cell.hpp GameMap.hpp GameMap.cpp
	g++ Cell.cpp -c -o Cell.o
	g++ GameMap.cpp -c -o GameMap.o

clean:
	rm Cell.o || true
	rm GameMap.o || true
	