#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "src/BasedSetup.h"
#include "src/LoadObjects.h"

using std::string;
using std::cout;

int main() {

    SDL_Event event;
    int running = true;

    float Xpos = 0.0f;
    float Ypos = 0.0f;
    const float speed = 300.0f;

    //Initialization
    Initialization Setup(3440, 1440);
    SDL_Renderer* renderer = Setup.getRenderer();

    // Load Font
    Setup.setFont();
    std::string fontPath = "/usr/share/fonts/TTF/DejaVuSans.ttf";
    TTF_Font* font = loadFont(fontPath, 40, Setup);

    SDL_FRect textBox = {10.0f, 0.0f, 400.0f, 100.0f};
    //Load Music
    Setup.setAudio();
    Mix_Music *music = loadmusic("assets/audio/bee.mp3");
    Mix_PlayMusic(music, -1);

    //Load Character
    std::string filePath = "assets/images/Charlft.bmp";
    SDL_Texture* texture = loadMan(filePath, Setup, renderer);
    SDL_FRect Chpos = { Xpos, Ypos, 200.0f, 125.0f };
    
    //Load Background
    std::string bgPath = "assets/images/background.jpg";
    SDL_Texture* background = loadBG(bgPath, Setup, renderer);


    // Delta time calculation variables
    Uint64 currentTime = SDL_GetTicksNS();
    Uint64 previousTime = currentTime;
    float deltaTime = 0.0f;

    while (running) {

        //Smooth Movement
        currentTime = SDL_GetTicksNS();
        deltaTime = (currentTime - previousTime) / 1e9f;
        previousTime = currentTime;

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
            }
        }

        //Keyboard Controls || X= -65, 3315 Y= -10, 1300
        const bool* keyState = SDL_GetKeyboardState(NULL);
        
        // X Position
        if (keyState[SDL_SCANCODE_LEFT] && Xpos >= -65){       
            Xpos -= speed * deltaTime;
            filePath = "assets/images/Charlft.bmp";
            reloadChar(filePath, texture, renderer);
        }
        if (keyState[SDL_SCANCODE_RIGHT] && Xpos <= 3315){ 
            
            Xpos += speed * deltaTime;
            filePath = "assets/images/CharRght.bmp";
            reloadChar(filePath, texture, renderer);
        }

        // Y Position
        if (keyState[SDL_SCANCODE_UP] && Ypos >= -10){
            Ypos -= speed * deltaTime;
        }
        if (keyState[SDL_SCANCODE_DOWN] && Ypos <= 1300){
            Ypos += speed * deltaTime;
        }  


        Chpos.x = Xpos;
        Chpos.y = Ypos;

        //Display X and Y Position
        string positionText = "X: " + std::to_string((int)Xpos) + "; Y: " + std::to_string((int)Ypos);
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, positionText.c_str(), positionText.length(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);



        //Display Background
        SDL_FRect bgRect = { 0.0f, 0.0f, 3440.0f, 1440.0f }; // Full window
        SDL_RenderTexture(renderer, background, NULL, &bgRect);

        //Display Character
        SDL_RenderTexture(renderer, texture, NULL, &Chpos);

        // Draw text box
        SDL_SetRenderDrawColor(renderer,  49, 179, 233, 0);   // Blue text box
        SDL_RenderRect(renderer, &textBox);
        SDL_FRect textRect = {textBox.x + 20, textBox.y + 30, (float)textSurface->w, (float)textSurface->h};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);


        //Display Graphics
        SDL_RenderPresent(renderer);
        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);
        SDL_Delay(1); // Small delay to avoid maxing out CPU
    }


    

    // Cleanup
    TTF_CloseFont(font);
    Mix_FreeMusic(music);
    Setup.cleanup();

    return 0;
}