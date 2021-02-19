#include <iostream>
#include <memory>
#include "../textura/textura.hpp"
#include "../../Controllers/imageprocessing/imageprocessing.hpp"

class Bolinha {
    private:
        std::shared_ptr<Textura> textura;
        bool power;
        int size;
        bool display;
        unsigned long int score;
        bool oldDisplay;
    public:
        Bolinha(int** ball, bool power1, int size1, char const* path);
        ~Bolinha();
        void setTextura(std::shared_ptr<Textura> textura1);
        std::shared_ptr<Textura> getTextura();
        void setPower(bool power1);
        bool getPower();
        void setDisplay(bool display1);
        bool getDisplay();
        void setOldDisplay(bool oldDisplay1);
        bool getOldDisplay();
        void setSize(int size1);
        int getSize();
        unsigned long int getScore();
        void setScore(unsigned long int score1);
};