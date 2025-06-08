void initWindow(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font, char *filename);
void closeWindow(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
void frameDelay(int fps, Uint32 frameStart);