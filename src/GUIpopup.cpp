#include <iostream>
#include <cmath>
#include <string>
#include <thread>
#include <chrono>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>

#include "BasedSetup.h"
#include "GUIpopup.h"
#include "LoadObjects.h"


using std::string;
using std::cout;
void loadFontInside(std::string msg, TTF_Font* font, SDL_FRect gui, int paddX, int paddY, SDL_Color Color, SDL_Renderer* renderer);

PopupGUI::PopupGUI(float windowx, float windowy, SDL_Renderer* Renderer){
    WindowX = windowx;
    WindowY = windowy;
    renderer = Renderer;
}

void PopupGUI::SetupGUI(SDL_FRect &Outline, SDL_FRect &Main) {
    float OutlineH = WindowY / 3;
    Outline = {0, WindowY - OutlineH, WindowX, OutlineH};
    Main = {Outline.x + 10, Outline.y + 10, Outline.w - 20, Outline.h - 20};
}

void PopupGUI::renderGUI(SDL_FRect outline, SDL_FRect inlined) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200); // Semi-transparent white
    SDL_RenderFillRect(renderer, &outline);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);       // Solid black
    SDL_RenderFillRect(renderer, &inlined);
}

void PopupGUI::setEffect(std::string Text, int DelayMS){
    text = Text;
    delayMs = DelayMS;
}

void PopupGUI::LoadEffect(SDL_Color white, SDL_FRect Gui, int paddX, int paddY){

    if (textIndex < text.size()) {
        currentText += text[textIndex++];
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    } else{
        loadFontInside("(Y/N)", fontDialogue, Gui, 30, 20, white, renderer);
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(fontDialogue, currentText.c_str(), currentText.length(), white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FRect textRects = {
        std::round(Gui.x + paddX),
        std::round(Gui.y + paddY),
        std::round(static_cast<float>(textWidth)),
        std::round(static_cast<float>(textHeight))
    };

    SDL_RenderTexture(renderer, textTexture, nullptr, &textRects);
}


void PopupGUI::Fadingin(){
    alpha -= fadeStep;
    if (alpha <= 0) {
        alpha = 0;
        // fadingOut = false; // Switch to fade in
    }

    // Render a semi-transparent rectangle overlay
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha); // Black with variable alpha
    SDL_FRect fadeRect = {0, 0, WindowX, WindowY};    // Full-screen rectangle
    SDL_RenderFillRect(renderer, &fadeRect);
}



void PopupGUI::Fadingout(){
    alpha += fadeStep;
    if (alpha >= 255) {
        alpha = 255;
        SDL_Delay(1200);
        fadingOut = false; // Switch to fade out
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha); // Black with variable alpha
    SDL_FRect fadeRect = {0, 0, WindowX, WindowY};    // Full-screen rectangle
    SDL_RenderFillRect(renderer, &fadeRect);

}


void PopupGUI::Response(){
    fadingOut ? Fadingout() : Fadingin();
}


bool PopupGUI::isFadeComplete() {
    return (alpha == 0); // Fade is complete when alpha is fully in or out
}

void loadFontInside(std::string msg, TTF_Font* font, SDL_FRect gui, int paddX, int paddY, SDL_Color Color, SDL_Renderer* renderer){

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, msg.c_str(), msg.length() ,Color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FRect GUItxt = {std::round((gui.x + gui.w) - (textWidth + paddX)), std::round((gui.y + gui.h) - (textHeight + paddY)), std::round(static_cast<float>(textWidth)), std::round(static_cast<float>(textHeight))};
    SDL_RenderTexture(renderer, textTexture, nullptr, &GUItxt);
}