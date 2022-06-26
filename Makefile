all:
	echo Please chose a valid build option: debug / release
debug:
	g++ -c src/*.cpp -g -Wall -m64 -I include -I C:/SDL/include && g++ *.o -o bin/debug/main -L C:/SDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && start bin/debug/main
release:
	g++ -c src/*.cpp -g -Wall -m64 -I include -I C:/SDL/include && g++ *.o -o bin/release/main -L C:/SDL/lib -L/opt/local/x86_64-w64-mingw32/lib -lSDL2_image -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static && start bin/release/main