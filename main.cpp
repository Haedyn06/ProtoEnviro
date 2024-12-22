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

#include "src/MainLoadout/PlayablePlayer.h"
#include "src/MainLoadout/LoadObjects.h"
#include "src/MainLoadout/BasedSetup.h"
#include "src/Environments/MainHall.h"
#include "src/MainLoadout/GUIpopup.h"


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

    //Load Main Player
    MainPlaya Characterman(renderer);
    Characterman.loadCharacter(Setup, "assets/images/Charlft.bmp");

    MainHall mainHall(WindowX, WindowY, Setup, renderer);
    SDL_SetWindowFullscreen(window, true);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    while (running) {

        Characterman.movementSmoothness();
        Characterman.controls();
        Xpos = Characterman.getCharX();

        //Event Handlings
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
                // mains.Teleportation(WindowX, WindowY, Xpos, keyEvent);
                mainHall.Teleportation(keyEvent, Xpos, CurrentEnviro);
            }
        }

        SDL_Color white = {255, 255, 255, 255};

        // mains.displayBackground(background);
        mainHall.DispBg();
        Characterman.displayCharacter();

        // mains.PoppedUpGUI(white);        
        Characterman.loadCoords(font);
        mainHall.PopupMessages(white);        
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