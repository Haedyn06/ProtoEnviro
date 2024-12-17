#ifndef LOADOBJh
#define LOADOBJh

#include <iostream>
#include "BasedSetup.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

Mix_Music* loadmusic(const std::string& Path);
TTF_Font* loadFont(std::string fontPath, int fontSize, Initialization &Setup);
SDL_Texture* loadBG(std::string BGPath, Initialization &Setup, SDL_Renderer* renderer);
SDL_Texture* loadMan(std::string filePath, Initialization &Setup, SDL_Renderer* renderer);
void reloadChar(const std::string& filePath, SDL_Texture*& texture, SDL_Renderer* renderer);




#endif