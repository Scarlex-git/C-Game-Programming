
main: main.c
	clang -o game `sdl2-config --cflags --libs` main.c gameFunctions.c gameObjects.c -lSDL2_image
clean:
	rm *.o
