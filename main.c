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
    char *start = malloc(size * sizeof(char));
    char *buffer = malloc(size * sizeof(char));

    strcpy(start, "Start Typing...");
    buffer[0] = '\0';

    initWindow(&window, &renderer, &font);
    codeText(renderer, font, &textTexture, &textRect, GrayColor, start);

    // free(start);

    int running = 1;
    SDL_Event event;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    int len = strlen(buffer);
                    char const *key;
                    int lenKey;
                    char *newBuffer = NULL;

                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            key = " ";
                            lenKey = 1;

                            newBuffer = realloc(buffer, len + lenKey + 1);
                            buffer = newBuffer;

                            buffer[len] = key[0];
                            buffer[len + 1] = '\0';
                            break;

                        case SDLK_BACKSPACE:
                            if (len > 0) {
                                len--;
                                buffer[len] = '\0';  
                                    
                                newBuffer = realloc(buffer, len + 1);
                                if (newBuffer) {
                                    buffer = newBuffer;
                                }
                            }

                            break;

                        default:
                            key = SDL_GetKeyName(event.key.keysym.sym);
                            lenKey = strlen(key);

                            newBuffer = realloc(buffer, len + lenKey + 1);
                            buffer = newBuffer;

                            buffer[len] = key[0];
                            buffer[len + 1] = '\0';
                            break;
                        
                    }

                        if (textTexture) {
                            SDL_DestroyTexture(textTexture);
                        }

                        if(buffer[0] != '\0'){
                            codeText(renderer, font, &textTexture, &textRect, WhiteColor, buffer);
                        }else{
                            codeText(renderer, font, &textTexture, &textRect, GrayColor, start);
                        }

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

    free(start);
    closeWindow(window, renderer, buffer, font);

    return EXIT_SUCCESS;
}