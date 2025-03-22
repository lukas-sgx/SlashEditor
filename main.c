#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "view.h"

void initWindow(SDL_Window **window, SDL_Renderer **renderer);
void closeWindow(SDL_Window *window, SDL_Renderer *renderer);

int main(int argc, char const *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    initWindow(&window, &renderer);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_RenderClear(renderer); 
        SDL_RenderPresent(renderer);
    }

    closeWindow(window, renderer);

    return EXIT_SUCCESS;
}


void initWindow(SDL_Window **window, SDL_Renderer **renderer){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow("NoText V1.0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
    if (!*window) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void closeWindow(SDL_Window *window, SDL_Renderer *renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}