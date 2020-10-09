#include "sistema.h"
#include <iostream>
#include <memory>
#include <cmath>

// namespace Sistema{

// };

Sistema::Sistema(std::shared_ptr<Mola> mola1, std::shared_ptr<Massa> massa1, std::shared_ptr<Amortecedor> amortecedor1) {
    mola = mola1;
    massa = massa1;
    amortecedor = amortecedor1;
};

Sistema::~Sistema(){};

void Sistema::calcularSistema(float x0, float v0, float fi) {
    float x = x0;
    float v = v0;
    float time = 0.01;

    for (int n = 0; n < 2000; n++) {
        std::cout << time*n << "/" << x << "/" << v << "|";
        float prevX = x;
        float prevV = v;
        v+=(-amortecedor->getCoef()*v -mola->getCoef()*prevX + fi)*(time/massa->getM());
        x+=time*prevV;
    }

    std::cout << ";";
};