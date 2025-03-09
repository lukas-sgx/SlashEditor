#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "view.h"

void initWindow();
void closeWindow();

int main(int argc, char const *argv[])
{
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    initWindow(window, renderer);

    closeWindow(window, renderer);

    SDL_Quit();
    return EXIT_SUCCESS;
}


void initWindow(SDL_Window *window, SDL_Renderer *renderer){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);

    if(NULL == window){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
    }

    SDL_Delay(6000);
}

void closeWindow(SDL_Window *window, SDL_Renderer *renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}