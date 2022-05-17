g++ -m64 -O2 -std=c++17 Cell\Cell.cpp -c -o Cell.o
g++ -m64 -O2 -std=c++17 Liner\Liner.cpp -c -o Liner.o
g++ -m64 -O2 -std=c++17 GameMap\GameMap.cpp -c -o GameMap.o
g++ -m64 -O2 -std=c++17 Player\Player.cpp -c -o Player.o
g++ -m64 -O2 -std=c++17 Computer\Computer.cpp -c -o Computer.o

g++ -m64 -Ifor_WINDOWS\include -O2 -std=c++17 Window\Window.cpp -c -o Window.o
g++ -m64 -Ifor_WINDOWS\include -std=c++17 Window\WindowEvent\WindowEvent.cpp -c -o WindowEvent.o

g++ -m64 -O2 -std=c++17 Game\Game.cpp -c -o Game.o
g++ -m64 -O2 -std=c++17 Menu\Menu.cpp -c -o Menu.o

g++ -m64 -O2 -std=c++17 test.cpp -o test.exe ^
	Window.o WindowEvent.o Game.o GameMap.o Cell.o Player.o Computer.o Menu.o Liner.o ^
	-lSDL2 -lSDL2main -Lfor_WINDOWS\lib