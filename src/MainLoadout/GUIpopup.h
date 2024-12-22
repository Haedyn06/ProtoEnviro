#ifndef GUIPOPUPh
#define GUIPOPUPh

#include <string>

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>


class PopupGUI {
private:
    float WindowX;
    float WindowY;
    SDL_Renderer* renderer;
    

    TTF_Font* fontDialogue = TTF_OpenFont("/usr/share/fonts/TTF/DePixelHalbfett.ttf", 45);
    std::string currentText = "";
    size_t textIndex = 0;
    std::string text;
    int delayMs;

    bool fadingOut = true;
    int alpha = 0;
    int fadeStep = 3;   

public:
    PopupGUI(float windowx, float windowy, SDL_Renderer* Renderer);
    void SetupGUI(SDL_FRect &Outline, SDL_FRect &Main);
    void renderGUI(SDL_FRect outline, SDL_FRect inlined);
    void setEffect(std::string Text, int DelayMS);
    void LoadEffect(SDL_Color white, SDL_FRect Gui, int paddX, int paddY);
    void Fadingin();
    void Fadingout();
    void Response();
    bool isFadeComplete();
};


#endif