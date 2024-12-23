#include <iostream>
#include <string>
#include <vector>

#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "BasedSetup.h"
#include "GUIpopup.h"


Mix_Music* loadmusic(const std::string& Path) {
    Mix_Music* music = Mix_LoadMUS(Path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << SDL_GetError() << std::endl;
    }
    return music;
}


SDL_Texture* loadAsset(std::string filePath, Initialization &Setup, SDL_Renderer* renderer){
    SDL_Surface* bmpSurface = SDL_LoadBMP(filePath.c_str());
    Setup.setBitmap(bmpSurface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_DestroySurface(bmpSurface);
    Setup.setTexture(texture);
    return texture;
}



//SDL_Surface* surface = SDL_LoadBMP("path/to/newBackground.bmp");
// SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
// SDL_DestroySurface(surface);

SDL_Texture* loadBG(std::string BGPath, Initialization &Setup, SDL_Renderer* renderer){
    SDL_Texture* background = IMG_LoadTexture(renderer, BGPath.c_str());
    Setup.setTexture(background);
    return background;
}

TTF_Font* loadFont(std::string fontPath, int fontSize, Initialization &Setup){

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    Setup.failedfontLoad(font);
    return font;
}


void LoadTextBox(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_FRect textbox) {
    // Text color
    SDL_Color textColor = {255, 255, 255, 255}; // White

    // Create a surface and texture for the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), message.length(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Draw the box background
    SDL_SetRenderDrawColor(renderer, 49, 179, 233, 255); // Blue background
    SDL_RenderFillRect(renderer, &textbox);

    // Render the text inside the box
    SDL_FRect textRect = {textbox.x + 10, textbox.y + 10, (float)textSurface->w, (float)textSurface->h};
    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

    // Cleanup
    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


bool CheckMouseInside(SDL_FRect button, int mouseX, int mouseY) {
    return mouseX >= button.x && mouseX <= (button.x + button.w) &&
           mouseY >= button.y && mouseY <= (button.y + button.h);
}

void LoadButton(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_FRect button, bool hovered) {
    SDL_Color color = hovered ? SDL_Color{100, 149, 237, 255} : SDL_Color{70, 130, 180, 255}; // Blue shades
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &button);

    SDL_Color textColor = {255, 255, 255, 255}; // White text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), text.length(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FRect textRect = {
        button.x + (button.w - textSurface->w) / 2,
        button.y + (button.h - textSurface->h) / 2,
        (float)textSurface->w, (float)textSurface->h
    };

    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void reloadChar(const std::string& filePath, SDL_Texture*& texture, SDL_Renderer* renderer) {
    SDL_Surface* newSurface = SDL_LoadBMP(filePath.c_str());
    if (newSurface) {
        if (texture) SDL_DestroyTexture(texture); // Free the old texture
        texture = SDL_CreateTextureFromSurface(renderer, newSurface);
        SDL_DestroySurface(newSurface); // Free the surface
    } else {
        SDL_Log("Failed to load new BMP: %s", SDL_GetError());
    }
}

void loadPopup(bool& popsup, bool& Accept, PopupGUI* &popup, SDL_FRect& Outline, SDL_FRect& Inlined, std::string Msg){
    popsup = true;
    Accept = false;
    popup->SetupGUI(Outline, Inlined);
    popup->setEffect(Msg, 25);
}

void Notif(bool& popsup, bool& Accept, PopupGUI*& popup, SDL_FRect& Outline, SDL_FRect& Inlined, SDL_Color& white, std::string &NewEnviro, std::string EnviroType) {
    if (!popsup) return; // Exit early if no popup is active

    if (Accept) {
        // std::cout << "Loaded Accept" << std::endl;
        if (popup) {
            popup->Response();
            if (popup->isFadeComplete()) {
                std::cout << "Fade complete!" << std::endl;
                NewEnviro = EnviroType;
                Accept = false;
                popsup = false;
                delete popup; // Cleanup
                popup = nullptr;


            }
        } else {
            std::cerr << "Popup is null during Response!" << std::endl;
            popsup = false;
            std::cout << popsup << std::endl;
        }
    } else {
        if (popup) {
            popup->renderGUI(Outline, Inlined);
            popup->LoadEffect(white, Inlined, 40, 40);
        } else {
            // std::cerr << "Popup is null during render!" << std::endl;
            // popsup = false;
            // std::cout << popsup << std::endl;
        }
    }
}




void KeyDecision(bool& popsup, SDL_KeyboardEvent& Keyevent, bool& Accept, std::string &NewEnviro, std::string EnviroType){
    if (popsup){
        if (Keyevent.key == SDLK_Y){
            Accept = true;
            // NewEnviro = EnviroType;
        }
        if (Keyevent.key == SDLK_N){
            popsup = false;
            
        }
    }
}