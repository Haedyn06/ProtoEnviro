#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>
#include <string>
#include "BasedSetup.h"
#include "LoadObjects.h"
#include "GUIpopup.h"
#include "PlayablePlayer.h"

using std::string;
using std::cout;



void MainPlaya::setCharX(float xpos){
    Xpos = xpos;
}
void MainPlaya::setCharY(float ypos){
    Ypos = ypos;
}

float MainPlaya::getCharX(){
    return Xpos;
}
float MainPlaya::getCharY(){
    return Ypos;
}


MainPlaya::MainPlaya(SDL_Renderer* Renderer){
    renderer = Renderer;
}


void MainPlaya::loadCharacter(Initialization &Setup, std::string Path){
    filePath = Path; // "assets/images/Charlft.bmp";
    texture = loadAsset(filePath, Setup, renderer);
    Chpos = { Xpos, Ypos, 1200.0f, 900.0f };
}

void MainPlaya::movementSmoothness() {
    currentTime = SDL_GetTicksNS();
    deltaTime = (currentTime - previousTime) / 1e9f; // Convert nanoseconds to seconds
    previousTime = currentTime;
}

void MainPlaya::controls() {
    const bool* keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_LEFT] && Xpos >= -470) {
        Xpos -= speed * deltaTime; // Update Xpos
        filePath = "assets/images/Charlft.bmp";
        reloadChar(filePath, texture, renderer);
    }
    if (keyState[SDL_SCANCODE_RIGHT] && Xpos <= 2650) {
        Xpos += speed * deltaTime; // Update Xpos
        filePath = "assets/images/CharRght.bmp";
        reloadChar(filePath, texture, renderer);
    }

    Chpos.x = Xpos;
    Chpos.y = Ypos;



    // Y Position
    // if (keyState[SDL_SCANCODE_UP] && Ypos >= -10){
    //     Ypos -= speed * deltaTime;
    // }
    // if (keyState[SDL_SCANCODE_DOWN] && Ypos <= 1300){
    //     Ypos += speed * deltaTime;
    // }  
}

void MainPlaya::loadCoords(TTF_Font* &font){

    string positionText = "X: " + std::to_string((int)Xpos) + "; Y: " + std::to_string((int)Ypos);
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, positionText.c_str(), positionText.length(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_SetRenderDrawColor(renderer,  49, 179, 233, 0);   // Blue text box
    SDL_RenderRect(renderer, &textBox);
    SDL_FRect textRect = {textBox.x + 20, textBox.y + 30, (float)textSurface->w, (float)textSurface->h};
    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);


    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void MainPlaya::displayCharacter(){
    SDL_RenderTexture(renderer, texture, NULL, &Chpos);
}
