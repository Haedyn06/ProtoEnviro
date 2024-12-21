#ifndef PLAYABLEPLAYAh
#define PLAYABLEPLAYAh


#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "BasedSetup.h"

class MainPlaya{

private:

    float Xpos = 2515.0f;
    float Ypos = 570.0f;
    const float speed = 600.0f;
    SDL_FRect textBox = {10.0f, 0.0f, 400.0f, 100.0f};

    Uint64 currentTime = SDL_GetTicksNS();
    Uint64 previousTime = currentTime;
    float deltaTime = 0.0f;

    SDL_Renderer* renderer;
    std::string filePath;
    SDL_Texture* texture;
    SDL_FRect Chpos;


public:

    void setCharX(float xpos);
    void setCharY(float ypos);
    float getCharX();
    float getCharY();
    MainPlaya(SDL_Renderer* Renderer);
    void loadCharacter(Initialization &Setup, std::string Path);
    void movementSmoothness();
    void controls();
    void loadCoords(TTF_Font* &font);
    void displayCharacter();



};



#endif