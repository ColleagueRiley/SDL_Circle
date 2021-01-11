#include <chrono>
#include <thread>
#include <future>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <vector>

//source https://gist.github.com/derofim/912cfc9161269336f722
/*
Edits: Removed extra things to turn it into a c++ file 
edited the includes
added circle class to make it more like SDL_RendererDrawRect
added circle class to make it look better
renamed some things
*/ 



//The window renderer
SDL_Renderer* gRenderer = NULL;


struct SDL_Circle{
	int x;
	int y;
	int radius;
};

struct SDL_color{int r;int g;int b;int a;};

void SDL_RenderSetPixel(SDL_Renderer *rend, int x, int y, SDL_Color c)
{
	Uint8 r = c.r;
	Uint8 g = c.g;
	Uint8 b = c.b;
	Uint8 a = c.a;
	SDL_SetRenderDrawColor(rend, r,g,b,a);
	SDL_RenderDrawPoint(rend, x, y);
}

//ex. SDL_RenderDrawCircle(renderer,circle,{0,0,0,255})
void SDL_RenderDrawCircle(SDL_Renderer *surface, SDL_Circle cir, SDL_Color c)
{
	int n_cx = cir.x;
	int n_cy = cir.y;
	int radius = cir.radius;
	Uint8 r = c.r;
	Uint8 g = c.g;
	Uint8 b = c.b;
	Uint8 a = c.a;
	
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
		SDL_RenderSetPixel(surface, (int)(cx + x), (int)(cy + y), {r, g, b, a});
		SDL_RenderSetPixel(surface, (int)(cx + y), (int)(cy + x), {r, g, b, a});

		if (x != 0)
		{
			SDL_RenderSetPixel(surface, (int)(cx - x), (int)(cy + y), {r, g, b, a});
			SDL_RenderSetPixel(surface, (int)(cx + y), (int)(cy - x), {r, g, b, a});
		}

		if (y != 0)
		{
			SDL_RenderSetPixel(surface, (int)(cx + x), (int)(cy - y), {r, g, b, a});
			SDL_RenderSetPixel(surface, (int)(cx - y), (int)(cy + x), {r, g, b, a});
		}

		if (x != 0 && y != 0)
		{
			SDL_RenderSetPixel(surface, (int)(cx - x), (int)(cy - y), {r, g, b, a});
			SDL_RenderSetPixel(surface, (int)(cx - y), (int)(cy - x), {r, g, b, a});
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
		/*
		// sleep for debug
		SDL_RenderPresent(gRenderer);
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
		*/
	}
}

//ex. SDL_RenderFillCircle(renderer,circle,{0,0,0,255})
void SDL_RenderFillCircle(SDL_Renderer *surface, SDL_Circle cir, SDL_Color c)
{
	int cx = cir.x;
	int cy = cir.y;
	int radius = cir.radius;	
	Uint8 r = c.r;
	Uint8 g = c.g;
	Uint8 b = c.b;
	Uint8 a = c.a;
	
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

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
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
		/*
		// sleep for debug
		SDL_RenderPresent(gRenderer);
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
		*/
	}
}
