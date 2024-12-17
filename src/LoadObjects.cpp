#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include "BasedSetup.h"

Mix_Music* loadmusic(const std::string& Path) {
    Mix_Music* music = Mix_LoadMUS(Path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << SDL_GetError() << std::endl;
    }
    return music;
}


SDL_Texture* loadMan(std::string filePath, Initialization &Setup, SDL_Renderer* renderer){
    SDL_Surface* bmpSurface = SDL_LoadBMP(filePath.c_str());
    Setup.setBitmap(bmpSurface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_DestroySurface(bmpSurface);
    Setup.setTexture(texture);
    return texture;
}

SDL_Texture* loadBG(std::string BGPath, Initialization &Setup, SDL_Renderer* renderer){
    SDL_Texture* background = IMG_LoadTexture(renderer, BGPath.c_str());
    Setup.setTexture(background);
    return background;
}

TTF_Font* loadFont(std::string fontPath, int fontSize, Initialization &Setup){

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    Setup.failedfontLoad(font);
    return font;
}

void reloadChar(const std::string& filePath, SDL_Texture*& texture, SDL_Renderer* renderer) {
    SDL_Surface* newSurface = SDL_LoadBMP(filePath.c_str());
    if (newSurface) {
        if (texture) SDL_DestroyTexture(texture); // Free the old texture
        texture = SDL_CreateTextureFromSurface(renderer, newSurface);
        SDL_DestroySurface(newSurface); // Free the surface
    } else {
        SDL_Log("Failed to load new BMP: %s", SDL_GetError());
    }
}


