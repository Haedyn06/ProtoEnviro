#include <iostream>

#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "BasedSetup.h"


SDL_Window* Initialization::getWindow() {
    return window;
}

SDL_Renderer* Initialization::getRenderer() {
    return renderer;
}
    
Initialization::Initialization(int width, int height){
    if (setSDL3() != 0) exit(EXIT_FAILURE);
    if (setWindow(width, height) != 0) exit(EXIT_FAILURE);
    if (setRenderer() != 0) exit(EXIT_FAILURE);
}

// Initialize SDL3
int Initialization::setSDL3(){
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

// Creates window
int Initialization::setWindow(int width, int height){
    window = SDL_CreateWindow("Proto Enviro", width, height, 0);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        SDL_Quit();
        return -2;
    }
    return 0;
}

//Create a renderer
int Initialization::setRenderer(){

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -3;
    }
    return 0;
}

//Creates Font
int Initialization::setFont(){
    if (!TTF_Init()) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return -4;
    }
    return 0;
}

//Creates Audio
int Initialization::setAudio(){
    SDL_Log("SDL3 Initialized");

    SDL_AudioSpec desiredSpec{};
    desiredSpec.freq = 44100;              // Sampling frequency
    desiredSpec.format = SDL_AUDIO_S16LE;  // 16-bit little-endian
    desiredSpec.channels = 2;              // Stereo output

    if (!Mix_OpenAudio(0, &desiredSpec)) {  // 0 = default audio device
        std::cerr << "Failed to open audio: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -3;
    }
    return 0;
}

//Creates Graphic
int Initialization::setBitmap(SDL_Surface* bmpSurface){

    if (!bmpSurface) {
    SDL_Log("Failed to load BMP: %s", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
    }
    return 0;
}

//Creates TExture
int Initialization::setTexture(SDL_Texture* texture){
    if (!texture) {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
}
    return 0;
}


int Initialization::failedfontLoad(TTF_Font* font){
    if (!font) {
        SDL_Log("Font load error: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

//Cleans Up
void Initialization::cleanup() {
    SDL_Log("SDL3 Shutdown");
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    Mix_CloseAudio();
}


// if (keyState[SDL_SCANCODE_UP]) Ypos -= speed * deltaTime;
// if (keyState[SDL_SCANCODE_DOWN]) Ypos += speed * deltaTime;
// if (keyState[SDL_SCANCODE_LEFT]){
//     Xpos -= speed * deltaTime;
//     filePath = "assets/images/Charlft.bmp";
//     reloadChar(filePath, texture, renderer);
// } 
// if (keyState[SDL_SCANCODE_RIGHT]){ 
    
//     Xpos += speed * deltaTime;
//     filePath = "assets/images/CharRght.bmp";
//     reloadChar(filePath, texture, renderer);
// }

// if (Ypos <= -45){
//     Ypos = 1180;
// } else if (Ypos >= 1190){
//     Ypos = -30;
// }

// if (Xpos <= -45){
//     Xpos = 1580;
// } else if (Xpos >= 1590){
//     Xpos = -30; 
// }