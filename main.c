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
    char *buffer = malloc(size * sizeof(char));
    strcpy(buffer, "Start Typing...");


    initWindow(&window, &renderer, &font);
    codeText(renderer, font, &textTexture, &textRect, GrayColor, buffer);

    buffer[0] = '\0';

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
                char const *key;
                int lenKey;
                int len = strlen(buffer);

                switch (event.key.keysym.sym){
                    case SDLK_SPACE:
                        key = " ";
                        lenKey = 1;

                        buffer = realloc(buffer, len+lenKey+1);
                        buffer[len] = key[0];
                        buffer[len+1] = '\0';
                        break;
                    case SDLK_BACKSPACE:
                        if (len > 0){
                            len--;
                            if (len > 0){
                                buffer[len] = '\0';
                                buffer = realloc(buffer, len + 1);
                            }else{
                                buffer = realloc(buffer, 1);
                                buffer[0] = '\0';
                            }
                        }
                        break;
                    default:
                        key = SDL_GetKeyName(event.key.keysym.sym);
                        lenKey = strlen(SDL_GetKeyName(event.key.keysym.sym));

                        buffer = realloc(buffer, len+lenKey+1);
                        buffer[len] = key[0];
                        buffer[len+1] = '\0';
                        break;  
                }                             

                codeText(renderer, font, &textTexture, &textRect, WhiteColor, buffer);
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