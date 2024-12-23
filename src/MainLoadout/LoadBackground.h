#ifndef LOADBGh
#define LOADBGh

#include <map>
#include <string>
#include <SDL3/SDL.h>

extern std::map<std::string, SDL_Texture*> gBackgrounds;
bool loadAllBackgrounds(SDL_Renderer* renderer);
void cleanupBackgrounds();


#endif