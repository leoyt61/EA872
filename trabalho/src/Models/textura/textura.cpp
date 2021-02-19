#include "../../../Include/Models/textura/textura.hpp"
#include <iostream>


Textura::Textura(SDL_Renderer* renderer1, char const *img, int const x, int const y) {
    texture = IMG_LoadTexture(renderer1, img);
    target.x = x;
    target.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);
};

Textura::~Textura(){
    SDL_DestroyTexture(texture);
};

void Textura::setTextura(SDL_Renderer* renderer1, char * img){
    texture = IMG_LoadTexture(renderer1, img);
};

SDL_Texture * Textura::getTextura(){
    return texture;
};

void Textura::setTarget(int x, int y) {
    target.x = x;
    target.y = y;

};

SDL_Rect Textura::getTarget() {
    return target;
};

SDL_Rect * Textura::getTargetAdress() {
    return &target;
};
