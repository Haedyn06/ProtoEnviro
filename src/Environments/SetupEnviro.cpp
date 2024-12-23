#include <iostream>
#include <string>
#include <vector>

#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "../MainLoadout/PlayablePlayer.h"
#include "../MainLoadout/LoadObjects.h"
#include "../MainLoadout/BasedSetup.h"
#include "../MainLoadout/GUIpopup.h"
#include "SetupEnviro.h"


using std::string;
using std::cout;


BasedEnvironment::BasedEnvironment(const int &windowx, const int &windowy, SDL_Renderer* Renderer)
    : PopupGUI(windowx, windowy, renderer){
    renderer = Renderer;
    WindowX = windowx;
    WindowY = windowy;
}

SDL_Texture* BasedEnvironment::setBackground(Initialization &Setup, std::string bgPath) {
    return loadAsset(bgPath, Setup, renderer);
}

void BasedEnvironment::displayBackground(SDL_Texture* background){
    SDL_FRect bgRect = { 0.0f, 0.0f, 3440.0f, 1440.0f};
    SDL_RenderTexture(renderer, background, NULL, &bgRect);
}

void BasedEnvironment::DestroyBg(SDL_Texture* background){
    SDL_DestroyTexture(background);
}

void BasedEnvironment::GUIon(SDL_KeyboardEvent& keyEvent, bool &MsgType, float AreaBarrier1, float AreaBarrier2, std::string Dialogue, float &CharXpos, std::string &NewEnviro, std::string EnviroType){
    
    if ((CharXpos >= AreaBarrier1) && (CharXpos <= AreaBarrier2) && (keyEvent.key == SDLK_RETURN) && (!Accept)){
        popup = new PopupGUI(WindowX, WindowY, renderer);
        loadPopup(MsgType, Accept, popup, Outline, Inlined, Dialogue);
        std::cout << Dialogue << std::endl;
        if (tpCompleted){
            NewEnviro = EnviroType;
            std::cout << "Switched to" << EnviroType << std::endl;
        }
    }
    KeyDecision(MsgType, keyEvent, Accept, NewEnviro, EnviroType);

}

void BasedEnvironment::PoppedUpGUI(SDL_Color white,  bool &MsgType, std::string &NewEnviro, std::string EnviroType) {
    Notif(MsgType, Accept, popup, Outline, Inlined, white, NewEnviro, EnviroType);
}

void BasedEnvironment::loadMusic(std::string Musictype){
    Mix_Music *music = loadmusic(Musictype);
    Mix_PlayMusic(music, -1);
}