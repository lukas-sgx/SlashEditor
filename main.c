#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "window.h"
#include "handle.h"

#define FPS 30
#define INIT_SIZE 16

int main(int argc, char const *argv[]){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Rect textRect;
    SDL_Color GrayColor = {112,112,112,230};
    SDL_Color WhiteColor = {255,255,255,230}; 

    Uint32 frameStart;

    int size = INIT_SIZE;
    int length = 0;
    char *buffer = malloc(size * sizeof(char));
    strcpy(buffer, "Start Typing...");


    initWindow(&window, &renderer, &font);
    codeText(renderer, font, &textTexture, &textRect, GrayColor, buffer);


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
                codeText(renderer, font, &textTexture, &textRect, WhiteColor, SDL_GetKeyName(event.key.keysym.sym));
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