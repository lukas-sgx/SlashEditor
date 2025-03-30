#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void codeText(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect, SDL_Color textColor, char const *text){
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
    *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    textRect->x = 10;
    textRect->y = 10;
    textRect->w = textSurface->w;
    textRect->h = textSurface->h;


    SDL_FreeSurface(textSurface);
    // SDL_DestroyTexture(*textTexture);
}

void handle(){

}