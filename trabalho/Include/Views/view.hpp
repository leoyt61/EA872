#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Models/textura/textura.hpp"
#include <memory>
#include <vector>

class View{
    private:
        unsigned int screenWidth; // pixels y
        unsigned int screenHeight; // pixels x
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        View(int x, int y);
        ~View();
        void render(float t, int x, int y);
        void renderClear();
        void renderBackground(std::shared_ptr<Textura> textura);
        void renderCharacter(std::shared_ptr<Textura> textura);
        void renderPresent();
        void renderMain(std::shared_ptr<Textura> textura);
        int setWindow();
        int setRenderer();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();

        unsigned int getScreenWidth();
        unsigned int getScreenHeight();
        void setScreenWidth(unsigned int x);
        void setScreenHeight(unsigned int y);
};