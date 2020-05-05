
main: main.c
	clang -o game `sdl2-config --cflags --libs` main.c gameFunctions.c gameObjects.c debug.c -lSDL2_image -lSDL2_ttf
clean:
	rm *.o
