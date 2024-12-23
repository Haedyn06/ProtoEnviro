#ifndef KITCHENh
#define KITCHENh

#include <iostream>
#include "SetupEnviro.h"
#include "../MainLoadout/BasedSetup.h"

class KitchenEnviro : protected BasedEnvironment{

private:
    bool mainMsg = false, livinMsg = false;
    

public:

    KitchenEnviro(const int &windowX, const int &windowY, SDL_Renderer* Renderer);
    SDL_Texture* Setbg(Initialization &Setup);
    void Teleportation(SDL_KeyboardEvent& keyEvent, float &charPosX, std::string &NewEnviro);
    void PopupMessages(SDL_Color white, std::string &NewEnviro);
    void DispBg(SDL_Texture* background);


};



#endif