#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "window.h"

#define FPS 30
#define INIT_SIZE 10

void initCodeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect, SDL_Color textColor);
void handle(SDL_Event *event);

int main(int argc, char const *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Rect textRect;
    SDL_Color textColor = {112,112,112,255};

    Uint32 frameStart;

    int size = INIT_SIZE;
    int length = 0;
    char *buffer = malloc(size * sizeof(char));

    buffer[0] = '\0';

    printf("%s", buffer);

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

    closeWindow(window, renderer, buffer, font);

    return EXIT_SUCCESS;
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