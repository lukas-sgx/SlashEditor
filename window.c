#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

void initWindow(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow("Slash Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
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

    *font = TTF_OpenFont("assets/CascadiaCode.ttf", 15);
    if (!*font) {
        printf("Erreur chargement police: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

void closeWindow(SDL_Window *window, SDL_Renderer *renderer, char *buffer, TTF_Font *font){
    free(buffer);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void frameDelay(int fps, Uint32 frameStart){
    int frameTime;
    int frameDelay = 1000 / fps;

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime); 
    }
}