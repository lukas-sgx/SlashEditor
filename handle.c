#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "tinyfiledialogs.h"

#define FPS 30

void codeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor, const char *text) {
    char buffer[strlen(text) + 1];
    strcpy(buffer, text);

    char *line = strtok(buffer, "\n");
    int line_y = 10;

    while (line) {
        SDL_Texture *textTexture = NULL;
        SDL_Rect textRect;
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, line, textColor);

        if (!textSurface) return;

        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        textRect.x = 10;
        textRect.y = line_y;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);

        line_y += textSurface->h;
        SDL_FreeSurface(textSurface);
        line = strtok(NULL, "\n");
    }
}

void handle(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *buffer, const char *start) {
    SDL_Color GrayColor = {112, 112, 112, 230};
    SDL_Color WhiteColor = {255, 255, 255, 230};

    Uint32 frameStart;
    int running = 1;
    int ctrl_pressed = 0;
    SDL_Event event;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if ((event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)) {
                        ctrl_pressed = 1;
                    } else {
                        int len = strlen(buffer);
                        const char *key = NULL;
                        int lenKey = 0;
                        char *newBuffer = NULL;

                        switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                key = " ";
                                lenKey = 1;
                                break;

                            case SDLK_BACKSPACE:
                                if (len > 0) {
                                    len--;
                                    buffer[len] = '\0'; 
                                    if (len == 0) {
                                        free(buffer);
                                        buffer = malloc(1 * sizeof(char));
                                        buffer[0] = '\0';
                                    } else {
                                        newBuffer = realloc(buffer, len + 1);
                                        if (newBuffer) {
                                            buffer = newBuffer;
                                        }
                                    }
                                }
                                break;

                            case SDLK_RETURN:
                                key = "\n";
                                lenKey = 1;
                                break;

                            default:
                                if (ctrl_pressed != 1 && event.key.keysym.sym < 128) {
                                    key = SDL_GetKeyName(event.key.keysym.sym);
                                    lenKey = strlen(key);
                                }
                                break;
                        }

                        if (key) {
                            newBuffer = realloc(buffer, len + lenKey + 1);
                            if (newBuffer) {
                                buffer = newBuffer;
                                memcpy(&buffer[len], key, lenKey);
                                buffer[len + lenKey] = '\0';
                            }
                        }
                    }

                    if (ctrl_pressed && event.key.keysym.sym == SDLK_q) {
                        running = 0;
                    }else if( ctrl_pressed && event.key.keysym.sym == SDLK_s) {
                        // Save functionality can be implemented here
                    } else if (ctrl_pressed && event.key.keysym.sym == SDLK_c) {
                        // Copy functionality can be implemented here
                    } else if (ctrl_pressed && event.key.keysym.sym == SDLK_v) {
                        // Paste functionality can be implemented here
                    }
                    else if (ctrl_pressed && event.key.keysym.sym == SDLK_x) {
                        // Cut functionality can be implemented here
                    }
                    else if (ctrl_pressed && event.key.keysym.sym == SDLK_a) {
                        // Select all functionality can be implemented here
                    }
                    else if (ctrl_pressed && event.key.keysym.sym == SDLK_z) {
                        // Undo functionality can be implemented here
                    }
                    else if (ctrl_pressed && event.key.keysym.sym == SDLK_o) {
                        const char *path = tinyfd_openFileDialog(
                            "Open File",   // title
                            "",            // default directory
                            0, NULL,       // allowed extensions (0 = all)
                            NULL,          // extension description
                            0              // do not allow multiple selection
                        );

                        if (path) {
                            FILE *file = fopen(path, "r");
                            if (file) {
                                char title[256];
                                const char *filename = strrchr(path, '/');
                                if (filename)
                                    filename++;
                                else
                                    filename = path;
                                snprintf(title, sizeof(title), "Slash Editor - %s", filename);
                                SDL_SetWindowTitle(window, title);
                                char *line = NULL;
                                line = malloc(1024 * sizeof(char));
                                free(buffer);
                                buffer = malloc(1 * sizeof(char));
                                buffer[0] = '\0';

                                while(fgets(line, 1024, file)) {
                                    char *newBuffer = NULL;
                                    int len = strlen(buffer);
                                    newBuffer = realloc(buffer, len + strlen(line) + 1);
                                    if (newBuffer) {
                                        buffer = newBuffer;
                                        memcpy(&buffer[len], line, strlen(line));
                                        buffer[len + strlen(line)] = '\0';
                                    }   
                                }

                                fclose(file);
                            } else {
                                perror("Error opening file");
                            }
                        }
                    }
                    break;

                case SDL_KEYUP:
                    if ((event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)) {
                        ctrl_pressed = 0;
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); 
        SDL_RenderClear(renderer);

        if (buffer[0] != '\0') {
            codeText(renderer, font, WhiteColor, buffer);
        } else {
            codeText(renderer, font, GrayColor, start);
        }

        SDL_RenderPresent(renderer);
        frameDelay(FPS, frameStart);
    }
}
