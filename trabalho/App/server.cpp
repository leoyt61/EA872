#include "../Include/Controllers/jogo/jogo.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector> 

int main() {
    srand(time(0));
    const unsigned int screenHeight = 630;
    const unsigned int screenWidth = 750;

    std::shared_ptr<View> view (new View(screenWidth, screenHeight));
    std::shared_ptr<Teclado> teclado (new Teclado()); // teclado
    std::unique_ptr<Jogo> jogo (new Jogo());
 
    jogo->iniciarServidor(view, teclado);

    return 0;
}