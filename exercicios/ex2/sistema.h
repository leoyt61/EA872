#include "mola.h"
#include "massa.h"
#include "amortecedor.h"
#include <iostream>
#include <memory>

class Sistema{
    private:
        std::shared_ptr<Mola> mola;
        std::shared_ptr<Massa> massa;
        std::shared_ptr<Amortecedor> amortecedor;
    public:
        Sistema(std::shared_ptr<Mola> mola, std::shared_ptr<Massa> massa, std::shared_ptr<Amortecedor> amortecedor);
        ~Sistema();
        void calcularSistema(float x0, float v0, float fi); // x0: posicao inicial; v0: velocidade inicial, forca externa fi;
};