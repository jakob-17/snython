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

	SDL_SetWindowTitle(win, "Snython");
	
	// triggers program that controls graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// renders images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates surface to load an image into main memory
	SDL_Surface* surface;

	// path to image
	surface = IMG_Load("workofart.png");

	// loads image into graphics hardware memory
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

	// clears main memory
	SDL_FreeSurface(surface);

	// allows for controlling image position
	SDL_Rect dest;

	// connects the texture with 'dest' to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// adjust height and width of the image box
	dest.w /= 6;
	dest.h /= 6;

	// set initial x-position and y-position
	dest.x = (1000 - dest.w) / 2;	
	dest.y = (1000 - dest.h) / 2;

	// controls animation loop
	int close = 0;

	// speed of box
	int speed = 300;

	// animation loop
	while (!close)
	{
		SDL_Event event;

		// events management
		while (SDL_PollEvent(&event))
		{
			// turn off compiler warnings of unused switch cases
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wswitch"
			switch (event.type)
			{
				case SDL_QUIT:
					// handling of close button
					close = 1;
					break;

				case SDL_KEYDOWN:
					// keyboard API for key pressed
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							dest.y -= speed / 30;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							dest.x -= speed / 30;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							dest.y += speed / 30;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							dest.x += speed / 30;
							break;
					}	
			}
			
			#pragma GCC diagnostic pop	
		}
	


		// right boundary
		if (dest.x + dest.w > 1000)
			dest.x = 1000 - dest.w;
		
		// left boundary
		if (dest.x < 0)
			dest.x = 0;

		// bottom boundary
		if (dest.y + dest.h > 1000)
			dest.y = 1000 - dest.h;

		// upper boundary
		if (dest.y < 0)
			dest.y = 0;

		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, tex, NULL, &dest);

		// triggers the double buffers for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	SDL_DestroyTexture(tex);

	SDL_DestroyRenderer(rend);

	SDL_DestroyWindow(win);	

	return 0;
}
