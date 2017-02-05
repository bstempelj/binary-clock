#include <SDL.h>
#include <stdio.h>

// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// init SDL
int init();

// free memory
void close();

// init bits
void initBits(int n, SDL_Rect arr[]);

// get binary format of a number
void toBin(int n, SDL_Rect arr[], SDL_Renderer* renderer);

// rendering window
SDL_Window* window = NULL;

// window renderer
SDL_Renderer* renderer = NULL;

int init()
{
	// init SDL or exit
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	// init window
	window = SDL_CreateWindow("Binary Clock",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	// set background to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	return 1;
}

void close()
{
	// destroy window and free up resources
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}

void initBits(int n, SDL_Rect arr[]) {
	for (int i = 0; i < n; i++)
	{
		SDL_Rect dot = { 0, 0, 10, 10 };
		arr[i] = dot;
	}
}

void toBin(int n, SDL_Rect arr[], SDL_Renderer* renderer)
{
	int i = 0;

	while (n != 0)
	{
		//printf("%d\n", n % 2);
		if (n % 2 == 1)
		{
			SDL_RenderFillRect(renderer, &arr[i]);
		}

		n /= 2;
		i++;
	}
}

int main(int argc, char* args[])
{
	int quit = 0;
	SDL_Event e;

	// time
	int hours = 0;
	int mins  = 0;
	int secs  = 0;

	// columns
	SDL_Rect secs1[4];
	SDL_Rect secs2[3];
	
	SDL_Rect mins1[4];
	SDL_Rect mins2[3];

	SDL_Rect hours1[4];
	SDL_Rect hours2[2];

	// start SDL
	if (!init()) printf("Failed to initialize!\n");

	// program loop
	while (!quit)
	{
		// event loop
		while (SDL_PollEvent(&e) != 0)
		{
			// user closed the program
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		// init bit rows
		initBits(4, secs1);
		initBits(3, secs2);
		initBits(4, mins1);
		initBits(3, mins2);
		initBits(4, hours1);
		initBits(2, hours2);

		// set secs
		secs1[0].x = 110;
		secs1[0].y = 70;		
		secs1[1].x = 110;
		secs1[1].y = 50;
		secs1[2].x = 110;
		secs1[2].y = 30;
		secs1[3].x = 110;
		secs1[3].y = 10;

		secs2[0].x = 90;
		secs2[0].y = 70;
		secs2[1].x = 90;
		secs2[1].y = 50;
		secs2[2].x = 90;
		secs2[2].y = 30;

		// set mins
		mins1[0].x = 70;
		mins1[0].y = 70;
		mins1[1].x = 70;
		mins1[1].y = 50;
		mins1[2].x = 70;
		mins1[2].y = 30;
		mins1[3].x = 70;
		mins1[3].y = 10;

		mins2[0].x = 50;
		mins2[0].y = 70;
		mins2[1].x = 50;
		mins2[1].y = 50;
		mins2[2].x = 50;
		mins2[2].y = 30;

		// set hours
		hours1[0].x = 30;
		hours1[0].y = 70;
		hours1[1].x = 30;
		hours1[1].y = 50;
		hours1[2].x = 30;
		hours1[2].y = 30;
		hours1[3].x = 30;
		hours1[3].y = 10;

		hours2[0].x = 10;
		hours2[0].y = 70;
		hours2[1].x = 10;
		hours2[1].y = 50;

		// set drawing color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// draw secs
		SDL_RenderDrawRects(renderer, secs1, 4);
		SDL_RenderDrawRects(renderer, secs2, 3);

		// draw mins
		SDL_RenderDrawRects(renderer, mins1, 4);
		SDL_RenderDrawRects(renderer, mins2, 3);

		// draw hours
		SDL_RenderDrawRects(renderer, hours1, 4);
		SDL_RenderDrawRects(renderer, hours2, 2);

		printf("%d:%d:%d\n", hours, mins, secs);
		if (++secs > 59) {
			secs = 0;

			if (++mins > 59) {
				mins = 0;

				if (++hours > 23)
					hours = 0;
			}
		}

		// test
		toBin(secs % 10, secs1, renderer);
		toBin(secs / 10, secs2, renderer);

		toBin(mins % 10, mins1, renderer);
		toBin(mins / 10, mins2, renderer);

		toBin(hours % 10, hours1, renderer);
		toBin(hours / 10, hours2, renderer);

		// update screen
		SDL_RenderPresent(renderer);
		SDL_Delay(500);
	}

	close();

	return 0;
}