# SDL_circle
A addon for SDL2 to make circles and an edit from a github gist by derofim (added Circle, edited functions and turned it into a headerfile). Orginal Gist: https://gist.github.com/derofim/912cfc9161269336f722

# How to install?

Download the file and move it to where you'd like. You can move it to a include file in your folder so you can just do `#include "../include/SDL_circle.h"`

OR you could move it to your copy of SDL2 so you can just do `#include <SDL2_SDL_circle>` (That'd be `/usr/include/SDL2` for linux)

# objects
   SDL_Circle
      int x - x var
      
      int y - y var
      
      int radius - radius


# Draw/Fill functions
  SDL_RenderDrawCircle(SDL_Renderer *surface, SDL_Circle cir) - Draws a circle on the renderer
  
  ex. SDL_RenderDrawCircle(renderer, circle);
  
  SDL_RenderFillCircle(SDL_Renderer *surface, SDL_Circle cir) - Fills circle on the screen
  
  ex. SDL_RenderFillCircle(renderer, circle)
  

# Collision functions
   int SDL_CircleCollide(SDL_Circle cir1,SDL_Circle cir2) - If circle collides with circle return 1 else return 0
   
   ex. if (SDL_CircleCollide(circle,circle2)){//do something}
   
   int SDL_CircleCollideRect(SDL_Circle c, SDL_Rect r) - If circle collides with rect return 1 else return 0
   
   ex. if (SDL_CircleCollideRect(circle,rect)){//do something}
   
   int SDL_CircleCollidePoint(SDL_Circle c, SDL_Rect p) - If circle collides with point return 1 else return 0
   
   ex. if (SDL_CircleCollideRect(circle,{example.x,example.y})){//do something}

   for mouse collide checking you can do:

   if (SDL_CircleCollideRect(circle,{e.motion.x,e.motion.y})){//do something}

   in this case e would be "SDL_Event e;"
