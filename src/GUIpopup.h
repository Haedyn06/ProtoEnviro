#ifndef GUIPOPUPh
#define GUIPOPUPh

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class GUIPopup {

private:
    SDL_Color color;
    SDL_Color GUIcolor = {91, 195, 250, 0};
    SDL_Color txtColor {255, 255, 255, 255};
    SDL_Color colorPY = {35, 89, 117, 0};
    SDL_Color colorHY = {56, 181, 33, 0};

    SDL_Color colorPN = {35, 89, 117, 0};
    SDL_Color colorHN = {255, 75, 63, 0};
    TTF_Font* Promptfont = TTF_OpenFont("/usr/share/fonts/TTF/Super Morning.ttf", 100);

    SDL_FRect gui;
    SDL_FRect buttonY;
    SDL_FRect buttonN;

    float Gwidth;
    float Gheight;
    float GposX;
    float GposY;

public:
    SDL_FRect getGUI();
    SDL_FRect getButtonY();
    SDL_FRect getButtonN();

    GUIPopup(const int WindowX, const int WindowY, float Padding);
    void declareGUI(int WindowX, int WindowY, float Padding);
    void buildGUI(std::string message, SDL_Renderer* renderer, bool buttonHoverY, bool buttonHoverN);
    void popUp(std::string message, bool clicked, float slideSpeed, const int WindowY, SDL_Renderer* renderer, bool buttonHoverY, bool buttonHoverN);
};


#endif