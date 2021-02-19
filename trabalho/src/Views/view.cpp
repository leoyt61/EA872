#include "../../Include/Views/view.hpp"
#include <iostream>


View::View(int x, int y){
    screenWidth = x;
    screenHeight = y;
};

View::~View(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void View::render(float t, int x, int y){
    std::cout << "Tempo: " << t << "; Coordenadas: (" << x << ", " << y << ");" << std::endl;
};

void View::renderClear() {
    SDL_RenderClear(renderer);
}

void View::renderBackground(std::shared_ptr<Textura> textura) {
    SDL_RenderCopyEx(renderer, textura->getTextura(), nullptr, nullptr, 180, nullptr, SDL_FLIP_NONE);
}

void View::renderCharacter(std::shared_ptr<Textura> textura){
    SDL_RenderCopy(renderer, textura->getTextura(), nullptr, textura->getTargetAdress());

};

void View::renderPresent() {
    SDL_RenderPresent(renderer);
}

void View::renderMain(std::shared_ptr<Textura> textura){
    SDL_RenderCopy(renderer, textura->getTextura(), nullptr, nullptr);

};

int View::setWindow(){
    window = SDL_CreateWindow("Pac-Men",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      screenWidth,
      screenHeight,
      SDL_WINDOW_SHOWN);
    if (window==nullptr) { // Em caso de erro...
        std::cout << SDL_GetError();
        SDL_Quit();
        return 1;
    }
    return 0;
}

int View::setRenderer(){
    renderer = SDL_CreateRenderer(
      window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) { // Em caso de erro...
        SDL_DestroyWindow(window);
        std::cout << SDL_GetError();
        SDL_Quit();
        return 1;
    }
    return 0;
}

SDL_Window* View::getWindow(){
    return window;
}

SDL_Renderer* View::getRenderer(){
    return renderer;
}


unsigned int View::getScreenWidth() {
    return screenWidth;
};

unsigned int View::getScreenHeight() {
    return screenHeight;
};

void View::setScreenWidth(unsigned int x) {
    screenWidth = x;
};

void View::setScreenHeight(unsigned int y) {
    screenHeight = y;
};
