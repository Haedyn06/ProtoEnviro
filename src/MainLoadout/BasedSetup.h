#ifndef BASEDSETUPh
#define BASEDSETUPh

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

class Initialization {

private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

public:

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    
    Initialization(int width, int height);
    int setSDL3();
    int setWindow(int width, int height);
    int setRenderer();
    int setFont();
    int setAudio();
    int setBitmap(SDL_Surface* bmpSurface);
    int setTexture(SDL_Texture* texture);
    int failedfontLoad(TTF_Font* font);
    void cleanup();
};



#endif