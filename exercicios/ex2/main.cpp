#include "sistema.h"
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<Mola> mola (new Mola(1));  // coef K (N/m)
    std::shared_ptr<Massa> massa (new Massa(0.5));  // massa m (kg)
    std::shared_ptr<Amortecedor> amortecedor (new Amortecedor(0.01)); // coef B (N.s/m)

    std::unique_ptr<Sistema> sistema (new Sistema(mola, massa, amortecedor));

    sistema->calcularSistema(1, 0, 10); // (posicao x , velocidade v, forca externa fi)

    amortecedor->setCoef(0.3);

    sistema->calcularSistema(1, 0, 10); // (posicao x , velocidade v, forca externa fi)

    amortecedor->setCoef(1);

    sistema->calcularSistema(1, 0, 10); // (posicao x , velocidade v, forca externa fi)

    return 0;
}