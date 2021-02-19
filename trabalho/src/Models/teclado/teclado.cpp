#include "../../../Include/Models/teclado/teclado.hpp"
#include <iostream>


Teclado::Teclado() {
};

Teclado::~Teclado(){};

const Uint8* Teclado::getState() {
    return state;
}

void Teclado::updateState() {
    SDL_PumpEvents();
}