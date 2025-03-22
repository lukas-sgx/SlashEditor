#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "view.h"

void initWindow(SDL_Window **window, SDL_Renderer **renderer);
void closeWindow(SDL_Window *window, SDL_Renderer *renderer);
void keyboard(SDL_KeyboardEvent *key);

int main(int argc, char const *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    initWindow(&window, &renderer);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                keyboard(event.key.keysym.sym);
            
            default:
                break;
            } 
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

    if (TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow("Slash Editor V1.0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
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

void keyboard(SDL_KeyboardEvent *key){

}