#include <SDL2/SDL.h>

//source https://gist.github.com/derofim/912cfc9161269336f722
/*
Edits: Removed extra things to turn it into a .h file 
edited the includes
added circle class to make it more like SDL_RendererDrawRect
added circle class to make it look better
renamed some things to clean the code up and make it more like SDL_RendererDrawRect/SDL_RendererFillRect
*/ 

struct SDL_Circle{
	int x;
	int y;
	int radius;
}

//ex. SDL_RenderDrawCircle(renderer,circle)
void SDL_RenderDrawCircle(SDL_Renderer *surface, SDL_Circle cir)
{
	int n_cx = cir.x;
	int n_cy = cir.y;
	int radius = cir.radius;
	
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	while (x >= y)
	{
		SDL_RenderDrawPoint(surface, (int)(cx + x), (int)(cy + y));
		SDL_RenderDrawPoint(surface, (int)(cx + y), (int)(cy + x));

		if (x != 0)
		{
			SDL_RenderDrawPoint(surface, (int)(cx - x), (int)(cy + y));
			SDL_RenderDrawPoint(surface, (int)(cx + y), (int)(cy - x));
		}

		if (y != 0)
		{
			SDL_RenderDrawPoint(surface, (int)(cx + x), (int)(cy - y));
			SDL_RenderDrawPoint(surface, (int)(cx - y), (int)(cy + x));
		}

		if (x != 0 && y != 0)
		{
			SDL_RenderDrawPoint(surface, (int)(cx - x), (int)(cy - y));
			SDL_RenderDrawPoint(surface, (int)(cx - y), (int)(cy - x));
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}

//ex. SDL_RenderFillCircle(renderer,circle)
void SDL_RenderFillCircle(SDL_Renderer* gRenderer, SDL_Circle cir)
{
	int cx = cir.x;
	int cy = cir.y;
	int radius = cir.radius;	
	// Note that there is more to altering the bitrate of this 
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	static const int BPP = 4;

	//double ra = (double)radius;

	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// We are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

		// Grab a pointer to the left-most pixel for each half of the circle
		/*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}*/
	}
}
