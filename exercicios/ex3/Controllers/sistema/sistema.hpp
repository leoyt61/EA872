#include "../../Models/mola/mola.hpp"
#include "../../Models/massa/massa.hpp"
#include "../../Models/amortecedor/amortecedor.hpp"
#include "../../Models/teclado/teclado.hpp"
#include "../../Views/view.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

class Sistema{
    private:
        std::shared_ptr<Mola> mola;
        std::shared_ptr<Massa> massa;
        std::shared_ptr<Amortecedor> amortecedor;
        std::shared_ptr<Textura> textura1;
        std::shared_ptr<Textura> textura2;
        std::shared_ptr<Teclado> teclado;
        std::shared_ptr<View> view;
        SDL_Event evento;
    public:
        Sistema(std::shared_ptr<Mola> mola, std::shared_ptr<Massa> massa, std::shared_ptr<Amortecedor> amortecedor, std::shared_ptr<View> view);
        ~Sistema();
        
        SDL_Event getEvent();
        SDL_Event * getEventAdress();

        void setTextura(int index, std::shared_ptr<Textura> textura);
        void setTeclado(std::shared_ptr<Teclado> teclado1);
        int setSDLInit();
        void calcularSistema(int x0, int y0, float sp, float interval, float g); // x0: posicao x inicial; y0: posicao y inicial; sp: velocidade inicial; interval: intervalo de tempo (ms); g: constante g;
        void calcularSistema2(float sp, float g); // x0: posicao x inicial; y0: posicao y inicial; sp: velocidade inicial; interval: intervalo de tempo (ms); g: constante g; ft: forca aplicada;
};