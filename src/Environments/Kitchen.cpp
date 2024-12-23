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
#include "../MainLoadout/BasedSetup.h"
#include "../MainLoadout/LoadObjects.h"
#include "../MainLoadout/GUIpopup.h"
#include "SetupEnviro.h"
#include "Kitchen.h"

KitchenEnviro::KitchenEnviro(const int &windowX, const int &windowY, SDL_Renderer* Renderer)
    : BasedEnvironment(windowX, windowY, Renderer) // Call MainHall's constructor

{       
    // background = setBackground(Setup, "assets/images/backgrounds/Kitchen.bmp");
}


SDL_Texture* KitchenEnviro::Setbg(Initialization &Setup){
    return setBackground(Setup, "assets/images/backgrounds/Kitchen.bmp");
    loadMusic("assets/audio/bee.mp3");
}

void KitchenEnviro::Teleportation(SDL_KeyboardEvent& keyEvent, float &charPosX, std::string &NewEnviro){
    GUIon(keyEvent, livinMsg, -1000.0f, -400.0f, "Would you like to go to the Living Room?", charPosX, NewEnviro, "LivingRoom");
    GUIon(keyEvent, mainMsg, 2470, 3000, "Would you like to go to the Main Hallway?", charPosX, NewEnviro, "MainHall");
    std::cout << livinMsg << ", " << mainMsg << std::endl;
}

void KitchenEnviro::PopupMessages(SDL_Color white, std::string &NewEnviro) {
    PoppedUpGUI(white, livinMsg, NewEnviro, "LivingRoom");
    PoppedUpGUI(white, mainMsg, NewEnviro, "MainHall");
}

void KitchenEnviro::DispBg(SDL_Texture* background) {
    displayBackground(background);
    }

