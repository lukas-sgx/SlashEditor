#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "tinyfiledialogs.h"

#define FPS 24

// Structure pour stocker les textures en cache
typedef struct {
    SDL_Texture *texture;
    int width;
    int height;
    char *text;
} CachedTexture;

#define MAX_CACHE_SIZE 1000
static CachedTexture textureCache[MAX_CACHE_SIZE];
static int cacheSize = 0;

void clearTextureCache() {
    for (int i = 0; i < cacheSize; i++) {
        if (textureCache[i].texture) {
            SDL_DestroyTexture(textureCache[i].texture);
            free(textureCache[i].text);
        }
    }
    cacheSize = 0;
}

SDL_Texture* getOrCreateTexture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int *w, int *h) {
    // Recherche dans le cache
    for (int i = 0; i < cacheSize; i++) {
        if (strcmp(textureCache[i].text, text) == 0) {
            *w = textureCache[i].width;
            *h = textureCache[i].height;
            return textureCache[i].texture;
        }
    }

    // Création d'une nouvelle texture si non trouvée
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) return NULL;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    *w = surface->w;
    *h = surface->h;
    SDL_FreeSurface(surface);

    if (cacheSize < MAX_CACHE_SIZE) {
        textureCache[cacheSize].texture = texture;
        textureCache[cacheSize].width = *w;
        textureCache[cacheSize].height = *h;
        textureCache[cacheSize].text = strdup(text);
        cacheSize++;
    }

    return texture;
}

void codeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor, const char *text, int showCursor) {
    const char *lineStart = text;
    const char *ptr = text;

    int line_y = 10;
    int last_line_w = 0;
    int last_line_h = TTF_FontHeight(font);

    char lineBuffer[2048];

    while (*ptr) {
        if (*ptr == '\n') {
            int len = ptr - lineStart;
            if (len >= sizeof(lineBuffer)) len = sizeof(lineBuffer) - 1;
            memcpy(lineBuffer, lineStart, len);
            lineBuffer[len] = '\0';

            int w, h;
            SDL_Texture *texture = getOrCreateTexture(renderer, font, lineBuffer, textColor, &w, &h);
            if (texture) {
                SDL_Rect textRect = {10, line_y, w, h};
                SDL_RenderCopy(renderer, texture, NULL, &textRect);
                last_line_w = 0;
                last_line_h = h;
            }

            line_y += last_line_h;
            lineStart = ptr + 1;
        }
        ptr++;
    }

    if (lineStart < ptr) {
        int len = ptr - lineStart;
        if (len >= sizeof(lineBuffer)) len = sizeof(lineBuffer) - 1;
        memcpy(lineBuffer, lineStart, len);
        lineBuffer[len] = '\0';

        int w, h;
        SDL_Texture *texture = getOrCreateTexture(renderer, font, lineBuffer, textColor, &w, &h);
        if (texture) {
            SDL_Rect textRect = {10, line_y, w, h};
            SDL_RenderCopy(renderer, texture, NULL, &textRect);
            last_line_w = w;
            last_line_h = h;
        }
    }

    if (showCursor) {
        SDL_Rect cursorRect = {
            10 + last_line_w,
            line_y,
            2.5,
            last_line_h
        };
        SDL_SetRenderDrawColor(renderer, 46, 149, 211, 255);
        SDL_RenderFillRect(renderer, &cursorRect);
    }
}

void handle(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, char *buffer, const char *start, char *filename) {
    SDL_Color GrayColor = {112, 112, 112, 230};
    SDL_Color WhiteColor = {255, 255, 255, 230};
    
    SDL_Event event;

    Uint32 frameStart;
    Uint32 lastCursorToggle = SDL_GetTicks();
    int running = 1;
    int ctrl_pressed = 0;
    int cursor_visible = 1;
    int nSave = 0;

    SDL_StartTextInput();

    while (running) {
        frameStart = SDL_GetTicks();

        if (SDL_GetTicks() - lastCursorToggle >= 500) {
            cursor_visible = !cursor_visible;
            lastCursorToggle = SDL_GetTicks();
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_TEXTINPUT: {
                    int len = strlen(buffer);
                    int textLen = strlen(event.text.text);

                    char *newBuffer = realloc(buffer, len + textLen + 1);
                    if (newBuffer) {
                        buffer = newBuffer;
                        memcpy(&buffer[len], event.text.text, textLen);
                        buffer[len + textLen] = '\0';
                    }
                    break;
                }

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
                                        newBuffer = realloc(buffer, 1);
                                        buffer = newBuffer;
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
                                len = strlen(buffer);
                                char *newBuffer = realloc(buffer, len + 2); // \n + \0
                                if (newBuffer) {
                                    buffer = newBuffer;
                                    buffer[len] = '\n';
                                    buffer[len + 1] = '\0';
                                }
                                break;

                            default:
                                break;
                        }
                    }

                    if (ctrl_pressed && event.key.keysym.sym == SDLK_q) {
                        running = 0;
                    }else if( ctrl_pressed && event.key.keysym.sym == SDLK_s) {
                        if (nSave == 0){       
                            char *path = tinyfd_saveFileDialog(
                                "Save File",
                                "",           
                                0,
                                NULL,
                                NULL
                            );

                            if (path){
                                FILE *file = fopen(path, "w");

                                if(file){
                                    fputs(buffer, file);
                                    fclose(file);

                                    char title[256];
                                    char *filenameAff = strrchr(path, '/');
                                    
                                    filename = path;

                                    if (filenameAff){
                                        filenameAff++;
                                    } else {
                                        filenameAff = path;
                                    }
                                    
                                    snprintf(title, sizeof(title), "Slash Editor - %s", filenameAff);
                                    SDL_SetWindowTitle(window, title);

                                    nSave = 1;
                                }
                            }
                        }else{
                            FILE *file = fopen(filename, "w");

                            if(file){
                                fputs(buffer, file);

                                fclose(file);
                            }
                        }
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
                        char *path = tinyfd_openFileDialog(
                            "Open File",   // title
                            "",            // default directory
                            0, NULL,       // allowed extensions (0 = all)
                            NULL,          // extension description
                            0              // do not allow multiple selection
                        );

                        if (path) {
                            FILE *file = fopen(path, "r");
                            if (file) {
                                fseek(file, 0, SEEK_END);
                                long fsize = ftell(file);
                                rewind(file);

                                char *newBuffer = malloc(fsize + 1);

                                size_t read = fread(newBuffer, 1, fsize, file);
                                newBuffer[read] = '\0';

                                buffer = newBuffer;

                                fclose(file);

                                char title[256];
                                char *filenameAff = strrchr(path, '/');
                                
                                filename = path;

                                if (filenameAff){
                                    filenameAff++;
                                } else {
                                    filenameAff = path;
                                }
                                
                                snprintf(title, sizeof(title), "Slash Editor - %s", filenameAff);
                                SDL_SetWindowTitle(window, title);
                                
                                nSave = 1;
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
            codeText(renderer, font, WhiteColor, buffer, cursor_visible);
        } else {
            codeText(renderer, font, GrayColor, start, cursor_visible);
        }

        SDL_RenderPresent(renderer);
        frameDelay(FPS, frameStart);
    }

    SDL_StopTextInput();
    clearTextureCache();
}
