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

using std::string;
using std::cout;

int main() {

    const int WindowX = 3440;
    const int WindowY = 1440;

    SDL_Event event;
    int running = true;

    float Xpos = 2515.0f;
    float Ypos = 570.0f;
    const float speed = 600.0f;

    //Initialization
    Initialization Setup(WindowX, WindowY);
    SDL_Renderer* renderer = Setup.getRenderer();
    SDL_Window* window = Setup.getWindow();

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
    SDL_Texture* texture = loadAsset(filePath, Setup, renderer);
    SDL_FRect Chpos = { Xpos, Ypos, 1200.0f, 900.0f };
    
    //Load Background
    std::string bgPath = "assets/images/backgrounds/FrontDoorHallway.bmp";
    SDL_Texture* background = loadAsset(bgPath, Setup, renderer);

    SDL_SetWindowFullscreen(window, true);

    // TTF_Font* fonta = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 24);
    // SDL_FRect button = {300, 250, 200, 100};
    // bool buttonHovered = false;

    //Load GUI
    GUIPopup InitialGUI(WindowX, WindowY, 50.0f);
    SDL_FRect gui = InitialGUI.getGUI();
    SDL_FRect buttonY = InitialGUI.getButtonY();
    SDL_FRect buttonN = InitialGUI.getButtonN();

    float slideSpeed = 3.0f;
    bool buttonHoverY = false;
    bool buttonHoverN = false;
    bool clicked = false;

    // Delta time calculation variables
    Uint64 currentTime = SDL_GetTicksNS();
    Uint64 previousTime = currentTime;
    float deltaTime = 0.0f;

    while (running) {

        //Smooth Movement
        currentTime = SDL_GetTicksNS();
        deltaTime = (currentTime - previousTime) / 1e9f;
        previousTime = currentTime;


        float mouseX;
        float mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        buttonHoverY = CheckMouseInside(buttonY, mouseX, mouseY);
        buttonHoverN = CheckMouseInside(buttonN, mouseX, mouseY);
        
        if (buttonHoverY || buttonHoverN ){
            SDL_Cursor* handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
            SDL_SetCursor(handCursor);
        } else{
            SDL_Cursor* handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            SDL_SetCursor(handCursor);
        }


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


                if ((Xpos >= 1160.0f) && (Xpos <= 1550.0f) && (keyEvent.key == SDLK_RETURN)){
                    clicked = true;
                    
                } else if ((Xpos <= -400) && (keyEvent.key == SDLK_RETURN)){
                    clicked = true;
                } else if ((Xpos >= 2470) && (keyEvent.key == SDLK_RETURN)){
                    clicked = true;
                }
            }
            
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                if ((mouseX >= buttonN.x && mouseX <= buttonN.x + buttonN.w) && (mouseY >= buttonN.y && mouseY <= buttonN.y + buttonN.h)) {
                    std::cout << "Clicked" << std::endl;
                    clicked = false;
                    gui.y = WindowY + 100;
                }
            }
        }

        //Keyboard Controls || X= -65, 3315 Y= -10, 1300
        const bool* keyState = SDL_GetKeyboardState(NULL);
        
        // X Position
        if (keyState[SDL_SCANCODE_LEFT] && Xpos >= -470){       
            Xpos -= speed * deltaTime;
            filePath = "assets/images/Charlft.bmp";
            reloadChar(filePath, texture, renderer);
        }
        if (keyState[SDL_SCANCODE_RIGHT] && Xpos <= 2650){ 
            
            Xpos += speed * deltaTime;
            filePath = "assets/images/CharRght.bmp";
            reloadChar(filePath, texture, renderer);
        }

        // Y Position
        // if (keyState[SDL_SCANCODE_UP] && Ypos >= -10){
        //     Ypos -= speed * deltaTime;
        // }
        // if (keyState[SDL_SCANCODE_DOWN] && Ypos <= 1300){
        //     Ypos += speed * deltaTime;
        // }  

        Chpos.x = Xpos;
        Chpos.y = Ypos;




        //Display X and Y Position
        string positionText = "X: " + std::to_string((int)Xpos) + "; Y: " + std::to_string((int)Ypos);
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, positionText.c_str(), positionText.length(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);


        // 1160-1550 = Stairs // X<-470
        //Display Background
        SDL_FRect bgRect = { 0.0f, 0.0f, 3440.0f, 1440.0f}; // Full window
        SDL_RenderTexture(renderer, background, NULL, &bgRect);

        //Display Character
        SDL_RenderTexture(renderer, texture, NULL, &Chpos);

        // Draw text box
        SDL_SetRenderDrawColor(renderer,  49, 179, 233, 0);   // Blue text box
        SDL_RenderRect(renderer, &textBox);
        SDL_FRect textRect = {textBox.x + 20, textBox.y + 30, (float)textSurface->w, (float)textSurface->h};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);


        InitialGUI.popUp("Go to Kitchen?", clicked, slideSpeed, WindowY, renderer, buttonHoverY, buttonHoverN);

        //Display Graphics
        SDL_RenderPresent(renderer);
        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);
        SDL_Delay(1); // Small delay to avoid maxing out CPU
    }

    

    // Cleanup
    TTF_CloseFont(font);
    // Mix_FreeMusic(music);
    Setup.cleanup();

    return 0;
}


//git add . 
//git commit -m "Message"
//git push