#ifndef SETENVIROh
#define SETENVIROh

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../MainLoadout/GUIpopup.h"


class BasedEnvironment : private PopupGUI{

private:
    SDL_Renderer* renderer;
    bool Accept = false;
    int WindowX, WindowY;
    SDL_FRect Outline, Inlined;
    PopupGUI* popup;
    bool tpCompleted = false;

public:
    BasedEnvironment(const int &windowx, const int &windowy, SDL_Renderer* Renderer);
    SDL_Texture* setBackground(Initialization &Setup, std::string bgPath);
    void displayBackground(SDL_Texture* background);
    void DestroyBg(SDL_Texture* background);
    void GUIon(SDL_KeyboardEvent& keyEvent, bool &MsgType, float AreaBarrier1, float AreaBarrier2, std::string Dialogue, float &CharXpos, std::string &NewEnviro, std::string EnviroType);
    void PoppedUpGUI(SDL_Color white, bool &MsgType, std::string &NewEnviro, std::string EnviroType);
    void loadMusic(std::string Musictype);
};

#endif