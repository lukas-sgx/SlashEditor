#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "view.h"

#define FPS 30
#define MAX_LENGTH 256

void initWindow(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);
void closeWindow(SDL_Window *window, SDL_Renderer *renderer);
void initCodeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect, SDL_Color textColor);
void frameDelay(int fps, Uint32 frameStart);
void handle(SDL_Event *event);

int main(int argc, char const *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Rect textRect;
    SDL_Color textColor = {112,112,112,255};

    Uint32 frameStart;

    initWindow(&window, &renderer, &font);
    initCodeText(renderer, font, &textTexture, &textRect, textColor);

    int running = 1;
    SDL_Event event;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                handle(&event);
                break;
            default:
                break;
            } 
        }

        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer); 
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);

        frameDelay(FPS, frameStart);
    }

    closeWindow(window, renderer);

    return EXIT_SUCCESS;
}


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

void closeWindow(SDL_Window *window, SDL_Renderer *renderer){
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

void initCodeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect, SDL_Color textColor){
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Start Typing...", textColor);
    *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    
    textRect->x = 10;
    textRect->y = 10;
    textRect->w = textSurface->w;
    textRect->h = textSurface->h;

    // SDL_DestroyTexture(*textTexture);
}

void handle(SDL_Event *event){
    // if(event->key.)
    
    printf("%s\n", SDL_GetKeyName(event->key.keysym.sym));
}