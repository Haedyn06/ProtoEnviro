#include <iostream>
#include <string>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

#include "../MainLoadout/BasedSetup.h"
#include "MainHall.h"


using std::string;
using std::cout;




MainHall::MainHall(const int &windowX, const int &windowY, SDL_Renderer* Renderer)
    : BasedEnvironment(windowX, windowY, Renderer) // Call MainHall's constructor

{       
    
    //loadMusic("assets/audio/bee.mp3");
}

SDL_Texture* MainHall::Setbg(Initialization &Setup){
    return setBackground(Setup, "assets/images/backgrounds/FrontDoorHallway.bmp");
}

void MainHall::Teleportation(SDL_KeyboardEvent& keyEvent, float &charPosX, std::string &NewEnviro){
    GUIon(keyEvent, UpstairMsg, 1160.0f, 1550.0f, "Would you like to go Upstairs?", charPosX, NewEnviro, "Upstairs");
    GUIon(keyEvent, KitchenMsg, -1000.0f, -400.0f, "Would you like to go to the Kitchen?", charPosX, NewEnviro, "Kitchen");
    GUIon(keyEvent, OutsideMsg, 2470, 3000, "Would you like to Outside?", charPosX, NewEnviro, "Outside");
    std::cout << KitchenMsg << ", " <<  UpstairMsg<< ", " << OutsideMsg << std::endl;
}

void MainHall::PopupMessages(SDL_Color white, std::string &NewEnviro) {
    PoppedUpGUI(white, UpstairMsg, NewEnviro, "Upstairs");
    PoppedUpGUI(white, KitchenMsg, NewEnviro, "Kitchen");
    PoppedUpGUI(white, OutsideMsg, NewEnviro, "Outside");
}


void MainHall::DispBg(SDL_Texture* background) {
    displayBackground(background);
}
void MainHall::Deletbg(SDL_Texture* background){
    DestroyBg(background);
}

