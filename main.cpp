#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <string>

using std::string;
using std::cout;

class Initialization{

private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

public:
    
    SDL_Window* getWindow() {
        return window;
    }
    SDL_Renderer* getRenderer() {
        return renderer;
    }
    
    Initialization(int width, int height){
        if (setSDL3() != 0) exit(EXIT_FAILURE);
        if (setWindow(width, height) != 0) exit(EXIT_FAILURE);
        if (setRenderer() != 0) exit(EXIT_FAILURE);
        if (setFont() != 0) exit(EXIT_FAILURE);
    }

    // Initialize SDL3
    int setSDL3(){
        int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        if (result < 0) {
            SDL_Log("SDL_Init error: %s", SDL_GetError());
            return -1;
        }
        return 0;
    }

    // Creates window
    int setWindow(int width, int height){
        window = SDL_CreateWindow("Smooth Square Movement", width, height, 0);
        if (window == NULL) {
            SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
            SDL_Quit();
            return -2;
        }
        return 0;
    }

    // Create a renderer
    int setRenderer(){
    
        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == NULL) {
            SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -3;
        }
        return 0;
    }

    //Creates Font
    int setFont(){
        if (!TTF_Init()) {
            SDL_Log("TTF_Init failed: %s", SDL_GetError());
            SDL_Quit();
            return -4;
        }
        return 0;
    }

    void cleanup() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
};


void reloadChar(const std::string& filePath, SDL_Texture*& texture, SDL_Renderer* renderer);
Mix_Music* loadmusic(const std::string& Path);
int main() {

    Initialization Setup(3440, 1440);
    SDL_Window* window = Setup.getWindow();
    SDL_Renderer* renderer = Setup.getRenderer();

    // Load Font
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 24);
    if (!font) {
        SDL_Log("Font load error: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Mix_Music *music;

    SDL_Log("SDL3 Initialized");

    SDL_AudioSpec desiredSpec{};
    desiredSpec.freq = 44100;              // Sampling frequency
    desiredSpec.format = SDL_AUDIO_S16LE;  // 16-bit little-endian
    desiredSpec.channels = 2;              // Stereo output

    if (!Mix_OpenAudio(0, &desiredSpec)) {  // 0 = default audio device
        std::cerr << "Failed to open audio: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    // if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
    //     SDL_Log("Failed to initialize required image formats: %s", IMG_GetError());
    //     SDL_Quit();
    //     return -1;
    // }


    //Bitmap Test
    std::string filePath = "assets/images/Charlft.bmp";
    SDL_Surface* bmpSurface = SDL_LoadBMP(filePath.c_str());
    if (!bmpSurface) {
        SDL_Log("Failed to load BMP: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_DestroySurface(bmpSurface); // Free the surface, no longer needed


    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    std::string filPath = "assets/images/background.jpg"; // Path to image
    SDL_Texture* background = IMG_LoadTexture(renderer, filPath.c_str());
    if (!background) {
        SDL_Log("Failed to load background: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Set position and size (repositioned and resized)
     // x, y, width, height


    music = loadmusic("assets/audio/bee.mp3");
    Mix_PlayMusic(music, -1);


    // Square properties
    float Xpos = 0.0f;
    float Ypos = 0.0f;
    SDL_FRect textBox = {10.0f, 0.0f, 400.0f, 100.0f};
    SDL_FRect mans = { Xpos, Ypos, 200.0f, 125.0f };
    const float speed = 300.0f; // Movement speed in pixels per second

    SDL_Event event;
    int running = true;

    // Delta time calculation variables
    Uint64 currentTime = SDL_GetTicksNS();
    Uint64 previousTime = currentTime;
    float deltaTime = 0.0f;

    while (running) {

        currentTime = SDL_GetTicksNS();
        deltaTime = (currentTime - previousTime) / 1e9f; // Convert ns to seconds
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
            //X= -65, 3315 Y= -10, 1300
        // Handle keyboard input for movement
        const bool* keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_UP] && Ypos >= -10)    Ypos -= speed * deltaTime;
        if (keyState[SDL_SCANCODE_DOWN] && Ypos <= 1300)  Ypos += speed * deltaTime;
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
        // if (keyState[SDL_SCANCODE_UP]) Ypos -= speed * deltaTime;
        // if (keyState[SDL_SCANCODE_DOWN]) Ypos += speed * deltaTime;
        // if (keyState[SDL_SCANCODE_LEFT]){
        //     Xpos -= speed * deltaTime;
        //     filePath = "assets/images/Charlft.bmp";
        //     reloadChar(filePath, texture, renderer);
        // } 
        // if (keyState[SDL_SCANCODE_RIGHT]){ 
            
        //     Xpos += speed * deltaTime;
        //     filePath = "assets/images/CharRght.bmp";
        //     reloadChar(filePath, texture, renderer);
        // }

        // if (Ypos <= -45){
        //     Ypos = 1180;
        // } else if (Ypos >= 1190){
        //     Ypos = -30;
        // }

        // if (Xpos <= -45){
        //     Xpos = 1580;
        // } else if (Xpos >= 1590){
        //     Xpos = -30; 
        // }


        // Update square position
        mans.x = Xpos;
        mans.y = Ypos;

        // Convert Xpos and Ypos to text
        string positionText = "X: " + std::to_string((int)Xpos) + ", Y: " + std::to_string((int)Ypos);
        SDL_Color textColor = {255, 255, 255, 255}; // White text
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, positionText.c_str(), positionText.length(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Clear screen
        SDL_FRect bgRect = { 0.0f, 0.0f, 3440.0f, 1440.0f }; // Full window
        SDL_RenderTexture(renderer, background, NULL, &bgRect);

        // Draw square
        SDL_RenderTexture(renderer, texture, NULL, &mans);

        // Draw text box
        SDL_SetRenderDrawColor(renderer,  49, 179, 233, 0);   // Blue text box
        SDL_RenderRect(renderer, &textBox);



        // Draw text inside text box
        SDL_FRect textRect = {textBox.x + 20, textBox.y + 30, (float)textSurface->w, (float)textSurface->h};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        SDL_RenderPresent(renderer);

        // Free text resources
        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_Delay(1); // Small delay to avoid maxing out CPU
    }

    // Cleanup resources
    TTF_CloseFont(font);
    SDL_Log("SDL3 Shutdown");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();


    return 0;
}

Mix_Music* loadmusic(const std::string& Path) {
    Mix_Music* music = Mix_LoadMUS(Path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << SDL_GetError() << std::endl;
    }
    return music;
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
