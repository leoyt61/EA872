#include "../../../Include/Controllers/sistema/sistema.hpp"
#include <iostream>
#include <memory>
#include <cmath>

Sistema::Sistema(std::shared_ptr<Mola> mola1, std::shared_ptr<Massa> massa1, std::shared_ptr<Amortecedor> amortecedor1, std::shared_ptr<View> view1) {
    mola = mola1;
    massa = massa1;
    amortecedor = amortecedor1;
    view = view1;
};

Sistema::~Sistema(){};


SDL_Event Sistema::getEvent() {
    return evento;
}

SDL_Event * Sistema::getEventAdress() {
    return &evento;
}

void Sistema::setTextura(int index, std::shared_ptr<Textura> textura) {
    if (index == 1) textura1 = textura;
    else if (index == 2) textura2 = textura;
}

void Sistema::setTeclado(std::shared_ptr<Teclado> teclado1) {
    teclado = teclado1;
}

int Sistema::setSDLInit() {
    if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
        std::cout << SDL_GetError();
    return 1;
  }
  return 0;
}


void Sistema::calcularSistema(int x0, int y0, float sp, float interval, float g) {
    const float fi = massa->getM() * g;

    const int h = view->getScreenHeight();
    const int b = view->getScreenWidth();

    float x = x0;
    float y = y0;
    float v = sp;
    float time = 0.01;

    for (int n = 0; n < interval; n++) {
        view->render(n*time, x+(b/2), (h/2)-y);
        float prevY = y;
        float prevV = v;
        v+=(-amortecedor->getCoef()*v -mola->getCoef()*prevY - fi)*(time/massa->getM());
        y+=time*prevV;
    }
};

void Sistema::calcularSistema2(float sp,float g) {

    const float peso = massa->getM() * g;

    const unsigned int h = view->getScreenHeight();
    const unsigned int b = view->getScreenWidth();

    textura1->setTarget(textura1->getTarget().x + (b/2) - 104, textura1->getTarget().y);
    
    bool rodando = true;

    float v = sp;
    float time = 0.1;

    int ft = 0;

    while(rodando) {
        teclado->updateState();
        if ((teclado->getState())[SDL_SCANCODE_UP]) ft+=10;
        if ((teclado->getState())[SDL_SCANCODE_DOWN]) ft-=10;
        if (!(teclado->getState())[SDL_SCANCODE_UP] && !(teclado->getState())[SDL_SCANCODE_DOWN]) {
            ft = 0;
        }

        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                rodando = false;
            }
        }

        textura1->setTarget(textura1->getTarget().x, ((h-243)/2) - textura1->getTarget().y);
        view->renderWindow(textura1, textura2);
        std::cout << "x = " << textura1->getTarget().x << "; y = " << textura1->getTarget().y << std::endl;
        textura1->setTarget(textura1->getTarget().x, ((h-243)/2) - textura1->getTarget().y);

        float prevY = textura1->getTarget().y;
        float prevV = v;
        v+=(-amortecedor->getCoef()*v -mola->getCoef()*prevY - peso + ft)*(time/massa->getM());
        textura1->setTarget(textura1->getTarget().x, textura1->getTarget().y + time*prevV);

        SDL_Delay(10);
    }
};