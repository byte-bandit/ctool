#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

TTF_Font *font;
SDL_Surface *screen;
SDL_Surface *images[2];

void drawText(char *text, int x, int y);
void drawPic(SDL_Surface *surface, int x, int y);
void draw(void);
void init(void);

enum IMAGES
{
	GOLD = 0,
	HOUSE = 1,
	MAN = 2,
	TIME = 3,
	FOOD = 4,
};

void drawText(char *text, int x, int y)
{
	SDL_Color color = {255, 255, 255};
	SDL_Surface *textsf;
	textsf = TTF_RenderText_Solid(font, text, color);
	drawPic(textsf, x, y);
	SDL_FreeSurface(textsf);
}

void drawPic(SDL_Surface *surface, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_BlitSurface(surface, NULL, screen, &rect);
}

void init(void)
{
	images[GOLD] = IMG_Load("gold.png");
	images[HOUSE] = IMG_Load("house.png");
	images[TIME] = IMG_Load("time.png");
	images[MAN] = IMG_Load("man.png");
	images[FOOD] = IMG_Load("food.png");
}

void draw(void)
{
	drawPic(images[GOLD], 16, 16);
	drawText("100", 38, 16);

	drawPic(images[TIME], 128, 16);
	drawText("1", 150, 16);

	drawPic(images[MAN], 256, 16);
	drawText("5", 278, 16);

	drawPic(images[FOOD], 384, 16);
	drawText("20", 406, 16);

	drawPic(images[HOUSE], 16, 42);
	drawText("0", 38, 42);
	SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
	SDL_Event event;
	int done = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Can't init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(640,480,16,SDL_HWSURFACE);
	if (screen == NULL)
	{
		printf("Can't set video mode: %s\n", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() != 0)
	{
		printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
		exit(1);
	}

	font = TTF_OpenFont("DejaVuSansMono.ttf", 12);
	if (font == NULL)
	{
		printf("Can't open font: %s\n", SDL_GetError());
		exit(1);
	}

	init();


	//TODO: This needs to sleep for 50ms per frame, then continue pooling
	// Only draw if an event has ben catched.
	while (!done)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("Button down: %d\n", event.button.button);
					break;
				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		draw();
	}

	SDL_Quit();
	return 0;
}
