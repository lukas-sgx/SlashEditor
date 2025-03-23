#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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