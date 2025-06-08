#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initWindow(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font, char *filename){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    char title[256];
    snprintf(title, sizeof(title), "Slash Editor - %s", filename);

    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, SDL_WINDOW_RESIZABLE);
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
    
    SDL_Cursor *ibeamCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    SDL_SetCursor(ibeamCursor);
}

void closeWindow(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font){
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