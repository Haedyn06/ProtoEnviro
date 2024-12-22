#ifndef MAINHALLh
#define MAINHALLh


#include <iostream>
#include <vector>

#include "SetupEnviro.h"
#include "../MainLoadout/GUIpopup.h"
#include "../MainLoadout/BasedSetup.h"


class MainHall : protected BasedEnvironment {

private:
    bool UpstairMsg = false, KitchenMsg = false, OutsideMsg = false;
    std::vector<bool> MsgPopups;
    SDL_Texture* background;

public:

    MainHall(const int &windowX, const int &windowY, Initialization &Setup, SDL_Renderer* Renderer);
    void Teleportation(SDL_KeyboardEvent& keyEvent, float &charPosX, std::string &NewEnviro);
    void PopupMessages(SDL_Color white);
    void DispBg();

};

#endif