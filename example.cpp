#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_circle.h"

bool running = true;
const Uint8* keys = SDL_GetKeyboardState(NULL);
SDL_Event e;
SDL_Circle circle = {200,200,25};

int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("SDL Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,500,500,SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    while (running){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
            }
            if (keys[SDL_SCANCODE_ESCAPE]){
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawCircle(renderer,&circle);
        SDL_RenderFillCircle(renderer,&circle);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderPresent(renderer);
    }
    void SDL_Quit();
}
