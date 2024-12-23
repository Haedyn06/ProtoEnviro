#ifndef LOADOBJh
#define LOADOBJh

#include <iostream>

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "BasedSetup.h"
#include "GUIpopup.h"

Mix_Music* loadmusic(const std::string& Path);
TTF_Font* loadFont(std::string fontPath, int fontSize, Initialization &Setup);
SDL_Texture* loadBG(std::string BGPath, Initialization &Setup, SDL_Renderer* renderer);
SDL_Texture* loadAsset(std::string filePath, Initialization &Setup, SDL_Renderer* renderer);
void LoadTextBox(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_FRect textbox);
bool CheckMouseInside(SDL_FRect button, int mouseX, int mouseY);
void LoadButton(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_FRect button, bool hovered);
void reloadChar(const std::string& filePath, SDL_Texture*& texture, SDL_Renderer* renderer);
void loadPopup(bool& popsup, bool& Accept, PopupGUI* &popup, SDL_FRect& Outline, SDL_FRect& Inlined, std::string Msg);
void Notif(bool& popsup, bool& Accept, PopupGUI*& popup, SDL_FRect& Outline, SDL_FRect& Inlined, SDL_Color& white, std::string &NewEnviro, std::string EnviroType);
void KeyDecision(bool& popsup, SDL_KeyboardEvent& Keyevent, bool& Accept, std::string &NewEnviro, std::string EnviroType);


#endif