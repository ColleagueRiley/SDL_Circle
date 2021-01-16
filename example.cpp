#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_circle.h>

bool running = true;
const Uint8* keys = SDL_GetKeyboardState(NULL);
SDL_Event e;
SDL_Circle circle = {200,300,25};
SDL_Circle circle2 = {200,200,25};
SDL_Rect rect = {400,275,50,50};

int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,500,500,SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    while (running){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
            }
            if (keys[SDL_SCANCODE_ESCAPE]){
                running = false;
            }
            if (keys[SDL_SCANCODE_UP]){
                circle.y = 220;
            }
            if (keys[SDL_SCANCODE_DOWN]){
                circle.y = 300;
            }
            if (keys[SDL_SCANCODE_RIGHT]){
                circle.x = 400;
            }
            if (keys[SDL_SCANCODE_LEFT]){
                circle.x = 200;
            }   
        }
        if (SDL_CircleCollidePoint(circle,{e.motion.x,e.motion.y})){
            std::cout << "Collide" << std::endl;
        }
        else{
            std::cout << std::endl;
        }             
        if (SDL_CircleCollide(circle,circle2)){
            std::cout << "Collide" << std::endl;
        }
        else{
          std::cout << std::endl;
        } 
        if (SDL_CircleCollideRect(circle,rect)){
            std::cout << "Collide" << std::endl;
        }       
        else{
          std::cout << std::endl;
        }
        SDL_RenderClear(renderer);
        
        //draw circle
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawCircle(renderer,circle);
        SDL_RenderFillCircle(renderer,circle);
        
        //draw circle2
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawCircle(renderer,circle2);
        SDL_RenderFillCircle(renderer,circle2);
        
        //draw rect
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawRect(renderer,&rect);
        SDL_RenderFillRect(renderer,&rect);        
        
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderPresent(renderer);
    }
    void SDL_Quit();
}