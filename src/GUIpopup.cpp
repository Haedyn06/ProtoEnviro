#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_mouse.h>
#include <cmath>
#include "GUIpopup.h"


void loadFontInside(std::string msg, TTF_Font* font, SDL_FRect gui, int paddX, int paddY, float Width, float Height, SDL_Color Color, SDL_Renderer* renderer);
void LoadButton(SDL_Renderer* renderer, SDL_FRect button, bool hovered, SDL_Color color, SDL_Color ColorPrimary, SDL_Color ColorHover, float cornerRadius);
void DrawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
void DrawRoundedRect(SDL_Renderer* renderer, SDL_FRect rect, float radius);
bool CheckMouseInside(SDL_FRect button, int mouseX, int mouseY);

SDL_FRect GUIPopup::getGUI(){
    return gui;
}
SDL_FRect GUIPopup::getButtonY(){
    return buttonY;
}
SDL_FRect GUIPopup::getButtonN(){
    return buttonN;
}



GUIPopup::GUIPopup(const int WindowX, const int WindowY, float Padding){
    declareGUI(WindowX, WindowY, Padding);
}

void GUIPopup::declareGUI(int WindowX, int WindowY, float Padding){

    Gwidth = (WindowX/2);
    Gheight = (WindowY/2);
    GposX = (WindowX/2) - (Gwidth/2);
    GposY = (WindowY/2) - (Gheight/2);

    const float Bwidth = Gwidth/3;
    const float Bheight = Gheight/5;
    const float BposY =  (GposY + Gheight) - (Bheight + Padding);
    const float BYesXpos = (GposX + Padding);
    const float BNoXpos = (GposX + Gwidth) - (Bwidth + Padding);

    gui = {GposX, GposY, Gwidth, Gheight};
    buttonY = {BYesXpos, BposY, Bwidth, Bheight};
    buttonN = {BNoXpos, BposY, Bwidth, Bheight};
}

void GUIPopup::buildGUI(std::string message, SDL_Renderer* renderer, bool buttonHoverY, bool buttonHoverN){

    SDL_SetRenderDrawColor(renderer, GUIcolor.r, GUIcolor.g, GUIcolor.b, GUIcolor.a);
    DrawRoundedRect(renderer, gui, 20.0f);
    loadFontInside(message, Promptfont, gui, 50, 20, 400, 64, txtColor, renderer);

    LoadButton(renderer, buttonY, buttonHoverY, color, colorPY, colorHY, 20.0f);
    loadFontInside("Ok", Promptfont, buttonY, 80, 15, buttonY.w - 250, buttonY.h - 30, txtColor, renderer);

    LoadButton(renderer, buttonN, buttonHoverN, color, colorPN, colorHN, 20.0f);
    loadFontInside("Cancel", Promptfont, buttonN, 30, 15, buttonN.w - 100, buttonN.h - 2, txtColor, renderer);
}


void GUIPopup::popUp(std::string message, bool clicked, float slideSpeed, const int WindowY, SDL_Renderer* renderer, bool buttonHoverY, bool buttonHoverN) {
    if (clicked) {
        if (gui.y > GposY) { // Slide up
            gui.y -= slideSpeed;
        }
    } else {
        if (gui.y < WindowY + 100) { // Slide back down
            gui.y += slideSpeed;
        }
    }

    // Always recalculate button positions relative to gui
    buttonY.y = gui.y + Gheight - buttonY.h - 50;
    buttonN.y = gui.y + Gheight - buttonN.h - 50;

    // Draw GUI and buttons
    buildGUI(message, renderer, buttonHoverY, buttonHoverN);
}

void loadFontInside(std::string msg, TTF_Font* font, SDL_FRect gui, int paddX, int paddY, float Width, float Height, SDL_Color Color, SDL_Renderer* renderer){
    SDL_FRect GUItxt = {gui.x + paddX, gui.y + paddY, Width, Height};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, msg.c_str(), msg.length() ,Color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderTexture(renderer, textTexture, nullptr, &GUItxt);
}

// Function to draw a filled circle (needed for rounded corners)
void DrawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w <= radius * 2; w++) {
        for (int h = 0; h <= radius * 2; h++) {
            int dx = radius - w; // Distance from center x
            int dy = radius - h; // Distance from center y
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Function to draw a rounded rectangle
void DrawRoundedRect(SDL_Renderer* renderer, SDL_FRect rect, float radius) {
    // Ensure the radius does not exceed half the width/height
    if (radius > rect.w / 2.0f) radius = rect.w / 2.0f;
    if (radius > rect.h / 2.0f) radius = rect.h / 2.0f;

    // Draw center rectangle (main body without corners)
    SDL_FRect centerRect = { rect.x + radius, rect.y, rect.w - 2 * radius, rect.h };
    SDL_RenderFillRect(renderer, &centerRect);

    SDL_FRect verticalRect = { rect.x, rect.y + radius, rect.w, rect.h - 2 * radius };
    SDL_RenderFillRect(renderer, &verticalRect);

    // Draw 4 filled circles for the corners
    DrawFilledCircle(renderer, rect.x + radius, rect.y + radius, radius);                        // Top-left
    DrawFilledCircle(renderer, rect.x + rect.w - radius, rect.y + radius, radius);              // Top-right
    DrawFilledCircle(renderer, rect.x + radius, rect.y + rect.h - radius, radius);              // Bottom-left
    DrawFilledCircle(renderer, rect.x + rect.w - radius, rect.y + rect.h - radius, radius);     // Bottom-right
}

bool CheckMouseInside(SDL_FRect button, float mouseX, float mouseY) {
    return mouseX >= button.x && mouseX <= (button.x + button.w) &&
           mouseY >= button.y && mouseY <= (button.y + button.h);
}

void LoadButton(SDL_Renderer* renderer, SDL_FRect button, bool hovered, SDL_Color color, SDL_Color ColorPrimary, SDL_Color ColorHover, float cornerRadius) {

    if (hovered){
        color = ColorHover;
    } else{
        color = ColorPrimary;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // SDL_RenderFillRect(renderer, &button);
    DrawRoundedRect(renderer, button, cornerRadius);
}
