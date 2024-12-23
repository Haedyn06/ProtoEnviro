#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "PlayablePlayer.h"
#include "LoadObjects.h"
#include "BasedSetup.h"
#include "../Environments/MainHall.h"
#include "GUIpopup.h"
#include "LoadBackground.h"


// Define the global map here (so we don't get multiple definitions).
std::map<std::string, SDL_Texture*> gBackgrounds;

bool loadAllBackgrounds(SDL_Renderer* renderer) {
    // We'll store pairs of {keyName, filePath}
    struct BGInfo {
        std::string key;
        std::string filename;
    };

    // List all backgrounds you want to load
    std::vector<BGInfo> bgFiles = {
        {"MainHall",    "assets/images/backgrounds/FrontDoorHallway.bmp"},
        {"Kitchen",     "assets/images/backgrounds/Kitchen.bmp"},
        {"Upstairs",    "assets/images/backgrounds/UpstairHall.bmp"},
        {"Outside",     "assets/images/backgrounds/frondor.bmp"},
        {"LivingRoom",  "assets/images/backgrounds/Livingroom.bmp"},
        {"Bedroom",     "assets/images/backgrounds/Bedroom.bmp"},
        {"Bathroom",    "assets/images/backgrounds/Bathroom.bmp"},
        {"Basement",    "assets/images/backgrounds/Basement.bmp"},
        {"Attic",       "assets/images/backgrounds/Attic.bmp"}
    };

    for (auto& bg : bgFiles) {
        SDL_Surface* surf = SDL_LoadBMP(bg.filename.c_str());
        if (!surf) {
            std::cerr << "Failed to load " << bg.filename
                      << ": " << SDL_GetError() << std::endl;
            // Decide if you want to return false here or keep going
            return false;
        }

        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_DestroySurface(surf);
        if (!tex) {
            std::cerr << "Failed to create texture from " << bg.filename
                      << ": " << SDL_GetError() << std::endl;
            return false;
        }

        // Store in the global map
        gBackgrounds[bg.key] = tex;
    }
    return true;
}

void cleanupBackgrounds() {
    for (auto& pair : gBackgrounds) {
        SDL_DestroyTexture(pair.second);
    }
    gBackgrounds.clear();
}




















// SDL_Texture* MainHallBg = nullptr;
// SDL_Texture* KitchenBg = nullptr;
// SDL_Texture* UpstairBg = nullptr;
// SDL_Texture* OutsideBg = nullptr;
// SDL_Texture* LivingRoomBg = nullptr;
// SDL_Texture* BedroomBg = nullptr;
// SDL_Texture* BathroomBg = nullptr;
// SDL_Texture* BasementBg = nullptr;
// SDL_Texture* AtticBg = nullptr;

// void loadAllBackgrounds(SDL_Renderer* renderer) {
//     // For demonstration, let's say we have 3 backgrounds
//     std::vector<std::string> bgFiles = {
//         "assets/images/backgrounds/FrontDoorHallway.bmp",
//         "assets/images/backgrounds/Kitchen.bmp",
//         "assets/images/backgrounds/bg2.bmp"
//     };

// void Setbackgrounds(SDL_Renderer* renderer){

//     SDL_Surface* MainHallSurf = SDL_LoadBMP("assets/images/backgrounds/FrontDoorHallway.bmp");
//     if (MainHallSurf) {
//         MainHallBg = SDL_CreateTextureFromSurface(renderer, MainHallSurf);
//         SDL_DestroySurface(MainHallSurf);
//     }

//     SDL_Surface* KitchenSurf = SDL_LoadBMP("assets/images/backgrounds/Kitchen.bmp");
//     if (KitchenSurf) {
//         KitchenBg = SDL_CreateTextureFromSurface(renderer, KitchenSurf);
//         SDL_DestroySurface(KitchenSurf);
//     }
//         SDL_Surface* UpstairSurf = SDL_LoadBMP("assets/images/backgrounds/UpstairHall.bmp");
//     if (UpstairSurf) {
//         UpstairBg = SDL_CreateTextureFromSurface(renderer, UpstairSurf);
//         SDL_DestroySurface(UpstairSurf);
//     }
    
//     SDL_Surface* OutsideSurf = SDL_LoadBMP("assets/images/backgrounds/frondor.bmp");
//     if (OutsideSurf) {
//         OutsideBg = SDL_CreateTextureFromSurface(renderer, OutsideSurf);
//         SDL_DestroySurface(OutsideSurf);
//     }
//         SDL_Surface* LivingRMSurf = SDL_LoadBMP("assets/images/backgrounds/Livingroom.bmp");
//     if (LivingRMSurf) {
//         LivingRoomBg = SDL_CreateTextureFromSurface(renderer, LivingRMSurf);
//         SDL_DestroySurface(LivingRMSurf);
//     }
    
//     SDL_Surface* BedroomSurf = SDL_LoadBMP("assets/images/backgrounds/Bedroom.bmp");
//     if (BedroomSurf) {
//         BedroomBg = SDL_CreateTextureFromSurface(renderer, BedroomSurf);
//         SDL_DestroySurface(BedroomSurf);
//     }
//         SDL_Surface* BathroomSurf = SDL_LoadBMP("assets/images/backgrounds/Bathroom.bmp");
//     if (BathroomSurf) {
//         BathroomBg = SDL_CreateTextureFromSurface(renderer, BathroomSurf);
//         SDL_DestroySurface(BathroomSurf);
//     }
    
//     SDL_Surface* BasementSurf = SDL_LoadBMP("assets/images/backgrounds/Basement.bmp");
//     if (BasementSurf) {
//         BasementBg = SDL_CreateTextureFromSurface(renderer, BasementSurf);
//         SDL_DestroySurface(BasementSurf);
//     }

//     SDL_Surface* AtticSurf = SDL_LoadBMP("assets/images/backgrounds/Attic.bmp");
//     if (AtticSurf) {
//         AtticBg = SDL_CreateTextureFromSurface(renderer, AtticSurf);
//         SDL_DestroySurface(AtticSurf);
//     }
// }

