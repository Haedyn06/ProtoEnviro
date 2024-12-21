#ifndef MAINHALLh
#define MAINHALLh

#include "../GUIpopup.h"
#include "../BasedSetup.h"

class MainHall : private PopupGUI {

private:
    SDL_Renderer* renderer;
    bool Accept = false;
    bool KitchenMsg;
    bool UpstairMsg;
    bool OutsideMsg;
    SDL_FRect Outline, Inlined;
    // SDL_Texture* background;
    PopupGUI* popup;

public:

    MainHall(int windowx, int windowy, SDL_Renderer* Renderer);
    SDL_Texture* setBackground(Initialization &Setup,  SDL_Renderer* &renderer);
    void displayBackground(SDL_Texture* &background);
    void Teleportation(const int& WindowX, const int& WindowY, float& Xpos, SDL_KeyboardEvent& keyEvent);
    void PoppedUpGUI(SDL_Color white);
    void loadMusic();


};



#endif