# SDL_circle
A addon for SDL2 to make circles and an edit from a github gist by derofim. Orginal Gist: https://gist.github.com/derofim/912cfc9161269336f722

# How to install?

Download the file and move it to where you'd like. You can move it to a include file in your folder so you can just do `#include "../include/SDL_circle.h"`

OR you could move it to your copy of SDL2 so you can just do `#include <SDL2_SDL_circle>` (That'd be `/usr/include/SDL2` for linux)

# objects
   SDL_Circle
      int x - x ver
      int y - y var
      int radius - radius


# functions
  set_pixel(SDL_Renderer *rend, int x, int y, SDL_color c)  - Draws a pixel/point on the renderer
  
  ex.  SDL_RenderSetPixel(renderer, 25, 25, {255,0,0,255});
  
  SDL_RenderDrawCircle(SDL_Renderer *surface, SDL_Circle cir, SDL_color c) - Draws a circle on the renderer
  
  ex. SDL_RenderDrawCircle(renderer, circle,{255,0,0,255});
  
  SDL_RenderFillCircle(SDL_Renderer *surface, SDL_Circle cir, SDL_color c) - Fills circle on the screen
  
  ex. SDL_RenderFillCircle(renderer, circle, {255,0,0,255})
  
