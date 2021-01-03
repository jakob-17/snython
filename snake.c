#include <SDL2/SDL.h> 	     // for initialization and shutdown
#include <SDL2/SDL_image.h>  // for rendering images/graphics
#include <SDL2/SDL_timer.h>  // for SDL_Delay()    

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("GAME",
					   SDL_WINDOWPOS_CENTERED,
					   SDL_WINDOWPOS_CENTERED,
					   1000, 1000, 0);
	while (1)	;

	return 0;
}
