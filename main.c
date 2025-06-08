#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "window.h"
#include "handle.h"

#define INIT_SIZE 16

int main(int argc, char const *argv[]){    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    TTF_Font *font = NULL;

    SDL_Color GrayColor = {112,112,112,230};

    int size = INIT_SIZE;
    char *start = malloc(size * sizeof(char));
    char *buffer = malloc(size * sizeof(char));
    char *filename = "Untitled";

    strcpy(start, "Start Typing...");
    buffer[0] = '\0';

    initWindow(&window, &renderer, &font, filename);
    codeText(renderer, font, GrayColor, start, 1);

    handle(window, renderer, font, buffer, start, filename);

    free(start);
    if(buffer){
        free(buffer);
    }
    closeWindow(window, renderer, font);

    return EXIT_SUCCESS;
}