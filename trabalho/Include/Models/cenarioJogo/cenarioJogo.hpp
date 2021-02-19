#include <iostream>
#include <memory>
#include "../textura/textura.hpp"
#include "../../Controllers/imageprocessing/imageprocessing.hpp"

class CenarioJogo {
    private:
        std::shared_ptr<Textura> textura;
        int **map;
        int width, height;
    public:
        CenarioJogo(int** mapa1);
        ~CenarioJogo();
        void setMap(int** mapa1);
        int** getMap();
        void setTextura(std::shared_ptr<Textura> textura1);
        std::shared_ptr<Textura> getTextura();
        void setWidth(int w);
        int getWidth();
        void setHeight(int h);
        int getHeight();
};