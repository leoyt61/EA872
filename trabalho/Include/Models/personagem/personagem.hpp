#include <iostream>
#include <memory>
#include <string>
#include "../textura/textura.hpp"
#include "../../Controllers/imageprocessing/imageprocessing.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../../Controllers/timer/timer.hpp"

using boost::asio::ip::udp;
class Personagem {
    private:
        std::shared_ptr<Textura> textura;
        std::shared_ptr<Timer> powerTimer;
        bool power, ghost;
        int height, width, life;
        unsigned long int score;
        std::string name;
        int x;
        int y;
        bool playing;
        udp::endpoint remote_endpoint;
        bool free;
    public:
        Personagem(int** pac, bool power1, bool ghost1, int width1, int height1, char const* path, std::string name1);
        ~Personagem();
        void setTextura(std::shared_ptr<Textura> textura1);
        std::shared_ptr<Textura> getTextura();
        void setPower();
        bool getPower();
        bool getGhost();
        void setHeight(int height1);
        int getHeight();
        void setWidth(int width1);
        int getWidth();
        void setLife(int life1);
        int getLife();
        void setScore(unsigned long int score1);
        unsigned long int getScore();
        void setName(std::string name1);
        std::string getName();
        std::shared_ptr<Timer> getPowerTimer();
        void setX(int x1);
        int getX();
        void setY(int y1);
        int getY();
        void setPlaying(bool playing1);
        bool getPlaying();
        void setIp(udp::endpoint remote_endpoint1);
        udp::endpoint getIp();
        void setFree(bool free1);
        bool getFree();
};