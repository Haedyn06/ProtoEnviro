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
#include "src/BasedSetup.h"
#include "src/LoadObjects.h"
#include "src/GUIpopup.h"
#include "src/PlayablePlayer.h"
#include "src/Environments/MainHall.h"

using std::string;
using std::cout;

int main() {
    //Variables
    const int WindowX = 3440;
    const int WindowY = 1440;

    SDL_Event event;
    int running = true;
    float Xpos;

    //Initialization
    Initialization Setup(WindowX, WindowY);
    SDL_Renderer* renderer = Setup.getRenderer();
    SDL_Window* window = Setup.getWindow();

    //Load Main Player
    MainPlaya Characterman(renderer);

    //Loads Initial Environment
    MainHall mains(WindowX, WindowY, renderer);

    // Load Font
    Setup.setFont();
    std::string fontPath = "/usr/share/fonts/TTF/DejaVuSans.ttf";
    TTF_Font* font = loadFont(fontPath, 40, Setup);
  
    // Load Music
    Setup.setAudio();
    mains.loadMusic();

    Characterman.loadCharacter(Setup, "assets/images/Charlft.bmp");

    //Load Initilized Background
    SDL_Texture* background;
    background = mains.setBackground(Setup, renderer);
    SDL_SetWindowFullscreen(window, true);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    while (running) {

        Characterman.movementSmoothness();
        Characterman.controls();
        Xpos = Characterman.getCharX();

        //Event Handling
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
                mains.Teleportation(WindowX, WindowY, Xpos, keyEvent);
            }
        }

        SDL_Color white = {255, 255, 255, 255};

        mains.displayBackground(background);

        Characterman.displayCharacter();

        mains.PoppedUpGUI(white);        
        Characterman.loadCoords(font);
        
        //Display Graphics
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Small delay to avoid maxing out CPU
    }
    // Cleanup
    TTF_CloseFont(font);
    Setup.cleanup();

    return 0;
}


//git add . 
//git commit -m "Message"
//git push