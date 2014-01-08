ALL:
	gcc main.c -o main -lSDL_image -lSDL_ttf `sdl-config --cflags --libs`
