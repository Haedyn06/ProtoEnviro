#include <iostream>
#include <string>
#include <vector>

#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "src/MainLoadout/LoadBackground.h"
#include "src/MainLoadout/PlayablePlayer.h"
#include "src/MainLoadout/LoadObjects.h"
#include "src/MainLoadout/BasedSetup.h"
#include "src/Environments/MainHall.h"
#include "src/MainLoadout/GUIpopup.h"
#include "src/Environments/Kitchen.h"


using std::string;
using std::cout;


int main() {
    //Variables

    std::string CurrentEnviro = "MainHall";


    const int WindowX = 3440;
    const int WindowY = 1440;

    SDL_Event event;
    int running = true;
    float Xpos;

    //Initialization
    Initialization Setup(WindowX, WindowY);
    SDL_Renderer* renderer = Setup.getRenderer();
    SDL_Window* window = Setup.getWindow();

    Setup.setFont();
    TTF_Font* font = loadFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 40, Setup);
    
  
    Setup.setAudio();
    // std::string currentEnv = "Kitchen";
    // SDL_Texture* currentBG = nullptr; 
    SDL_SetWindowFullscreen(window, true);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (!loadAllBackgrounds(renderer)) {
        std::cerr << "Some backgrounds failed to load.\n";
    }

    MainHall mainHall(WindowX, WindowY, renderer);
    KitchenEnviro kitch(WindowX, WindowY, renderer);

    MainPlaya Characterman(renderer);
    Characterman.loadCharacter(Setup, "assets/images/Charlft.bmp");

    while (running) {

        Characterman.movementSmoothness();
        Characterman.controls();
        Xpos = Characterman.getCharX();

        // Event Handlings
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                SDL_KeyboardEvent& keyEvent = event.key;

                if (keyEvent.key == SDLK_ESCAPE) {
                    std::cout << "Escape key pressed! Exiting..." << std::endl;
                    running = false;
                }

                if (CurrentEnviro == "MainHall"){
                    mainHall.Teleportation(keyEvent, Xpos, CurrentEnviro);
                } else if (CurrentEnviro == "Kitchen"){
                    kitch.Teleportation(keyEvent, Xpos, CurrentEnviro);
                }
                
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (gBackgrounds.find(CurrentEnviro) != gBackgrounds.end()) {
            SDL_Texture* bgTex = gBackgrounds[CurrentEnviro];
            if (bgTex) {
                SDL_FRect bgRect = {0, 0, WindowX, WindowY};
                SDL_RenderTexture(renderer, bgTex, NULL, &bgRect);
            }
        }
        
        Characterman.displayCharacter();        
        Characterman.loadCoords(font);


        SDL_Color white = {255, 255, 255, 255};
        if (CurrentEnviro == "MainHall") {
            mainHall.PopupMessages(white, CurrentEnviro);
        } else {
            kitch.PopupMessages(white, CurrentEnviro);
        }  
        //Display Graphics
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Small delay to avoid maxing out CPU
        cout << CurrentEnviro << std::endl;
    }

    // Cleanup
    TTF_CloseFont(font);
    Setup.cleanup();

    return 0;
}


//git add . 
//git commit -m "Message"
//git push