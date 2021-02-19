#include "../Include/Controllers/sistema/sistema.hpp"
#include <iostream>
#include <memory>

int main() {
    const int option = 1;

    const unsigned int interval = 2000; // miliseconds
    const float speed = 0; // m/s
    const float g = 9.8; // m/s^2
    const unsigned int screenHeight = 1000;
    const unsigned int screenWidth = 1000;
    int const posX = 0; // m
    int const posY = 100; // m

    std::shared_ptr<View> view (new View(screenWidth, screenHeight));
    std::shared_ptr<Mola> mola (new Mola(1));  // coef K (N/m)
    std::shared_ptr<Massa> massa (new Massa(0.5));  // massa m (kg)
    std::shared_ptr<Amortecedor> amortecedor (new Amortecedor(0.3)); // coef B (N.s/m)
    if (option == 0) {

        std::unique_ptr<Sistema> sistema (new Sistema(mola, massa, amortecedor, view));

        sistema->calcularSistema(posX, posY, speed, interval, g); // (posicao inicial, posicao inicial, velocidade, intervalo de tempo, constante gravitacional)

    }

    if (option == 1) {
        std::unique_ptr<Sistema> sistema (new Sistema(mola, massa, amortecedor, view));

        int stateSDL = sistema->setSDLInit();
        if (stateSDL > 0) return 1;

        char const *img1 = "../Assets/capi.png";
        char const *img2 = "../Assets/park.jpeg";

        int stateWindow = view->setWindow(); // Criando uma janela
        int stateRenderer = view->setRenderer(); // Inicializando o renderizador

        if (stateWindow + stateRenderer > 0) return 1;

        std::shared_ptr<Textura> textura1 (new Textura(view->getRenderer(), img1, posX, posY)); // textura 1 (movel)
        std::shared_ptr<Textura> textura2 (new Textura(view->getRenderer(), img2, posX, posY)); // textura 2 (fundo)
        
        std::shared_ptr<Teclado> teclado (new Teclado()); // teclado


        sistema->setTextura(1, textura1);
        sistema->setTextura(2, textura2);

        sistema->setTeclado(teclado);

        sistema->calcularSistema2(speed, g); // (posicao inicial, posicao inicial, velocidade, intervalo de tempo, constante gravitacional)
    }

    return 0;
}