#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Models/textura/textura.hpp"
#include <memory>

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
        void renderWindow(std::shared_ptr<Textura> textura1, std::shared_ptr<Textura> textura2);

        int setWindow();
        int setRenderer();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();

        unsigned int getScreenWidth();
        unsigned int getScreenHeight();
        void setScreenWidth(unsigned int x);
        void setScreenHeight(unsigned int y);
};