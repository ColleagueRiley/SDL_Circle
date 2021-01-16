#include <SDL2/SDL.h>
#include <math.h>
//source https://gist.github.com/derofim/912cfc9161269336f722
/*
Edits: Removed extra things to turn it into a .h file 
edited the includesc
added circle class to make it more like SDL_RendererDrawRect
added circle class to make it look better
renamed some things to clean the code up and make it more like SDL_RendererDrawRect/SDL_RendererFillRect

biggest addition:
	added collision checking functions
*/ 

typedef struct SDL_Circle{
	int x;
	int y;
	int radius;
} SDL_Circle;

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
	}
}

int SDL_CircleCollide(SDL_Circle cir1,SDL_Circle cir2){
	float distanceBetweenCircles = (float)sqrt(
	(cir2.x - cir1.x) * (cir2.x - cir1.x) + 
    (cir2.y - cir1.y) * (cir2.y - cir1.y)
  	);
	if (distanceBetweenCircles > cir1.radius + cir2.radius){return 0;}else{return 1;}
}

int SDL_CircleCollideRect(SDL_Circle c, SDL_Rect r){
  float testX = c.x; float testY = c.y;

  if (c.x < r.x) {testX = r.x;}  else if (c.x > r.x+r.w) {testX = r.x+r.w;}
  if (c.y < r.y) {testY = r.y;}  else if (c.y > r.y+r.h) {testY = r.y+r.h;} 
  
  return (sqrt( ( (c.x-testX) * (c.x-testX) ) + ( (c.y-testY) *(c.y-testY) ) )  <= c.radius);
}

int SDL_CircleCollidePoint(SDL_Circle c, SDL_Rect p){
	float testX = c.x; float testY = c.y;

  	if (c.x < p.x) {testX = p.x;}  else if (c.x > p.x+p.w) {testX = p.x+p.w;}
  	if (c.y < p.y) {testY = p.y;}  else if (c.y > p.y+p.h) {testY = p.y+p.h;} 
  
  	return (sqrt( ( (c.x-testX) * (c.x-testX) ) + ( (c.y-testY) *(c.y-testY) ) )  <= c.radius);
}	