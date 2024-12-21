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
#include "../BasedSetup.h"
#include "../LoadObjects.h"
#include "../GUIpopup.h"
#include "MainHall.h"


MainHall::MainHall(int windowx, int windowy, SDL_Renderer* Renderer)
    : PopupGUI(windowx, windowy, renderer){
    renderer = Renderer;
}

// bool &accept, bool &kitchen, bool &upstair, bool &outside, SDL_FRect &outline, SDL_FRect &inlined, SDL_Renderer* &Renderer
SDL_Texture* MainHall::setBackground(Initialization &Setup,  SDL_Renderer* &renderer){

    std::string bgPath = "assets/images/backgrounds/FrontDoorHallway.bmp";
    SDL_Texture* background = loadAsset(bgPath, Setup, renderer);

    return background;
}

void MainHall::displayBackground(SDL_Texture* &background){
    SDL_FRect bgRect = { 0.0f, 0.0f, 3440.0f, 1440.0f}; // Full window
    SDL_RenderTexture(renderer, background, NULL, &bgRect);
}


void MainHall::Teleportation(const int& WindowX, const int& WindowY, float& Xpos, SDL_KeyboardEvent& keyEvent){
    std::cout << "X position: " << Xpos << std::endl;
    if ((Xpos >= 1160.0f) && (Xpos <= 1550.0f) && (keyEvent.key == SDLK_RETURN) && (!Accept)){
        popup = new PopupGUI(WindowX, WindowY, renderer);
        loadPopup(UpstairMsg, Accept, popup, Outline, Inlined, "Would you like to go Upstairs?");
    } else if ((Xpos <= -400) && (keyEvent.key == SDLK_RETURN) && (!Accept)){
        popup = new PopupGUI(WindowX, WindowY, renderer);
        loadPopup(KitchenMsg, Accept, popup, Outline, Inlined, "Would you like to go to the Kitchen?");
    } else if ((Xpos >= 2470) && (keyEvent.key == SDLK_RETURN) && (!Accept)){
        popup = new PopupGUI(WindowX, WindowY, renderer);
        loadPopup(OutsideMsg, Accept, popup, Outline, Inlined, "Would you like to Outside?");
    }
    KeyDecision(UpstairMsg, keyEvent, Accept);
    KeyDecision(KitchenMsg, keyEvent, Accept);
    KeyDecision(OutsideMsg, keyEvent, Accept);
}

void MainHall::PoppedUpGUI(SDL_Color white){
    //GUI
    Notif(KitchenMsg, Accept, popup, Outline, Inlined, white);
    Notif(OutsideMsg, Accept, popup, Outline, Inlined, white);
    Notif(UpstairMsg, Accept, popup, Outline, Inlined, white);
}

void MainHall::loadMusic(){
    Mix_Music *music = loadmusic("assets/audio/bee.mp3");
    Mix_PlayMusic(music, -1);
}