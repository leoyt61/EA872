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
    int stateSDL = jogo->setSDLInit();
    if (stateSDL > 0) return 1;

    int stateWindow = view->setWindow(); // Criando uma janela
    int stateRenderer = view->setRenderer(); // Inicializando o renderizador

    if (stateWindow + stateRenderer > 0) return 1;
 
    jogo->iniciarJogo(view, teclado);

    return 0;
}