#include "../../../Include/Controllers/servidor/servidor.hpp"
#include <iostream>
#include <memory>
#include <cmath>
std::mutex foo;
boost::asio::io_service my_io_service_receive; // Conecta com o SO

udp::endpoint local_endpoint_receive(udp::v4(), 9001); // endpoint: contem
                                                // conf. da conexao (ip/port)

udp::socket meu_socket_receive(my_io_service_receive,   // io service
                        local_endpoint_receive); // endpoint

udp::endpoint remote_endpoint_receive; // vai conter informacoes de quem conectar

Servidor::Servidor() {};

Servidor::~Servidor(){};

void Servidor::setBallsPositions(std::shared_ptr<CenarioJogo> cenarioJogo, std::vector<std::shared_ptr<Bolinha>> &bolinhas) {
    int cont = 0;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 25; j++) {
            if (cenarioJogo->getMap()[i*30][j*30] == 3 || cenarioJogo->getMap()[i*30][j*30] == 6) {
                std::shared_ptr<Textura> textura = bolinhas[cont]->getTextura();
                textura->setTarget(j*30, i*30);
                bolinhas[cont]->setTextura(textura);
                cont++;
            }
        }
    }
}

void Servidor::setInitialPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo) {
    int b = 0;
    for (unsigned long int i = 0; i < cenarioJogo->getHeight(); i++) {
        for (unsigned long int j = 0; j < cenarioJogo->getWidth(); j++) {
            if ((personagem->getGhost() == false && cenarioJogo->getMap()[i][j] == 4) || (personagem->getGhost() == true && cenarioJogo->getMap()[i][j] == 5)) {
                std::shared_ptr<Textura> textura = personagem->getTextura();
                textura->setTarget(j, i);
                personagem->setTextura(textura);
                b = 1;
                break;
            }
        }
        if (b == 1) break;
    }
}

int Servidor::setCharacterPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo, int x, int y, int oldX, int oldY){
    int **mapa = cenarioJogo->getMap();
    if (personagem->getGhost() == false) {
        if ((x != 0 || y != 0) && (x != oldX || y != oldY)) {
            std::shared_ptr<Textura> textura = personagem->getTextura();
            int tx = textura->getTarget().x;
            int ty = textura->getTarget().y;
            if ((mapa[ty+y][tx+x] == 3 || mapa[ty+y][tx+x] == 4 || mapa[ty+y][tx+x] == 6) && (mapa[ty+personagem->getHeight()-1+y][tx+x] == 3 || mapa[ty+personagem->getHeight()-1+y][tx+x] == 4 || mapa[ty+personagem->getHeight()-1+y][tx+x] == 6) && (mapa[ty+y][tx+personagem->getWidth()-1+x] == 3 || mapa[ty+y][tx+personagem->getWidth()-1+x] == 4 || mapa[ty+y][tx+personagem->getWidth()-1+x] == 6) && (mapa[ty+personagem->getHeight()-1+y][tx+personagem->getWidth()-1+x] == 3 || mapa[ty+personagem->getHeight()-1+y][tx+personagem->getWidth()-1+x] == 4 || mapa[ty+personagem->getHeight()-1+y][tx+personagem->getWidth()-1+x] == 6)) {
                textura->setTarget(tx+x, ty+y);
                personagem->setTextura(textura);    
                return 0;
            }
            else if ((mapa[ty+oldY][tx+oldX] == 3 || mapa[ty+oldY][tx+oldX] == 4 || mapa[ty+oldY][tx+oldX] == 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 3 || mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 4 || mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 6) && (mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 3 || mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 4 || mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 3 || mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 4 || mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 6)) {
                textura->setTarget(tx+oldX, ty+oldY);
                personagem->setTextura(textura); 
                return 1;
            }
        }
        else  {
            std::shared_ptr<Textura> textura = personagem->getTextura();
            int tx = textura->getTarget().x;
            int ty = textura->getTarget().y;
            if ((mapa[ty+oldY][tx+oldX] == 3 || mapa[ty+oldY][tx+oldX] == 4 || mapa[ty+oldY][tx+oldX] == 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 3 || mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 4 || mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] == 6) && (mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 3 || mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 4 || mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] == 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 3 || mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 4 || mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] == 6)) {
                textura->setTarget(tx+oldX, ty+oldY);
                personagem->setTextura(textura);    
                return 1;
            }
            return 0;
        }
    }
    else {
        if ((x != 0 || y != 0) && (x != oldX || y != oldY)) {
            std::shared_ptr<Textura> textura = personagem->getTextura();
            int tx = textura->getTarget().x;
            int ty = textura->getTarget().y;
            if ((mapa[ty+y][tx+x] >= 2 && mapa[ty+y][tx+x] <= 6) && (mapa[ty+personagem->getHeight()-1+y][tx+x] >= 2 && mapa[ty+personagem->getHeight()-1+y][tx+x] <= 6) && (mapa[ty+y][tx+personagem->getWidth()-1+x] >= 2 && mapa[ty+y][tx+personagem->getWidth()-1+x] <= 6) && (mapa[ty+personagem->getHeight()-1+y][tx+personagem->getWidth()-1+x] >= 2 && mapa[ty+personagem->getHeight()-1+y][tx+personagem->getWidth()-1+x] <= 6)) {
                textura->setTarget(tx+x, ty+y);
                personagem->setTextura(textura);    
                return 0;
            }
            else if ((mapa[ty+oldY][tx+oldX] >= 2 && mapa[ty+oldY][tx+oldX] <= 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] >= 2 && mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] <= 6) && (mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] >= 2 && mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] <= 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] >= 2 && mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] <= 6)) {
                textura->setTarget(tx+oldX, ty+oldY);
                personagem->setTextura(textura); 
                return 1;
            }
        }
        else  {
            std::shared_ptr<Textura> textura = personagem->getTextura();
            int tx = textura->getTarget().x;
            int ty = textura->getTarget().y;
            if ((mapa[ty+oldY][tx+oldX] >= 2 && mapa[ty+oldY][tx+oldX] <= 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] >= 2 && mapa[ty+personagem->getHeight()-1+oldY][tx+oldX] <= 6) && (mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] >= 2 && mapa[ty+oldY][tx+personagem->getWidth()-1+oldX] <= 6) && (mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] >= 2 && mapa[ty+personagem->getHeight()-1+oldY][tx+personagem->getWidth()-1+oldX] <= 6)) {
                textura->setTarget(tx+oldX, ty+oldY);
                personagem->setTextura(textura);    
                return 1;
            }
            return 0;
        }
    }
}

void Servidor::characterControl(std::shared_ptr<Personagem> personagem, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, int vertical, int horizontal, std::shared_ptr<Timer> timer) { 
    int newX = horizontal;
    int newY = vertical;

    if (personagem->getPowerTimer()->elapsedSeconds() > 10) {

        if (personagem->getPower() == true) personagem->setPower();
        personagem->getPowerTimer()->stop();
    }

    int i = setCharacterPosition(personagem, cenarioJogo, newX, newY, personagem->getX(), personagem->getY());
    if (i == 0) {
        personagem->setX(newX);
        personagem->setY(newY);
    }
}

void Servidor::allCharactersControl(std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Timer> timer) {
    for (int k = 0; k < inimigos.size(); k++) {
        if (inimigos[k]->getLife() >= 0) {
            int xpse = inimigos[k]->getTextura()->getTarget().x;
            int ypse = inimigos[k]->getTextura()->getTarget().y;
            int xpid = inimigos[k]->getTextura()->getTarget().x+29;
            int ypid = inimigos[k]->getTextura()->getTarget().y+29;
            for (int i = 0; i < bolinhas.size(); i++) {
                int xbse = bolinhas[i]->getTextura()->getTarget().x;
                int ybse = bolinhas[i]->getTextura()->getTarget().y;
                int xbid = bolinhas[i]->getTextura()->getTarget().x+29;
                int ybid = bolinhas[i]->getTextura()->getTarget().y+29;
                if ((xbse == xpse && ((ypse <= ybid-10 && ypse >= ybse+10) || (ypid <= ybid-10 && ypid >= ybse+10))) || (ybse == ypse && ((xpse <= xbid-10 && xpse >= xbse+10) || (xpid <= xbid-10 && xpid >= xbse+10)))) {
                    if (bolinhas[i]->getDisplay() == true) {
                        bolinhas[i]->setDisplay(false);
                        inimigos[k]->setScore(inimigos[k]->getScore()+bolinhas[i]->getScore());
                        bolinhas[i]->setOldDisplay(false);
                        if (bolinhas[i]->getPower() == true && inimigos[k]->getPower() == false) {
                            inimigos[k]->setPower();
                            timer->start();
                            inimigos[k]->getPowerTimer()->start();
                        }
                    }
                }
            }

            for (int i = k+1; i < inimigos.size(); i++) {
                int xise = inimigos[i]->getTextura()->getTarget().x;
                int yise = inimigos[i]->getTextura()->getTarget().y;
                int xiid = inimigos[i]->getTextura()->getTarget().x+29;
                int yiid = inimigos[i]->getTextura()->getTarget().y+29;


                if (((xpse <= xise && xpid >= xise) || (xpse <= xiid && xpid >= xiid)) && ((ypse <= yise && ypid >= yise) || (ypse <= yiid && ypid >= yiid))) {
                    if (inimigos[i]->getLife() >= 0) {
                        if (inimigos[k]->getPower() == true && inimigos[i]->getPower() == false) {
                            inimigos[i]->setLife(inimigos[i]->getLife()-1);
                            inimigos[k]->setScore(inimigos[k]->getScore()+(100*(i+1)));
                            if(inimigos[i]->getLife() >= 0) {
                                setInitialPosition(inimigos[i], cenarioJogo);
                            }
                        }
                        else if (inimigos[k]->getPower() == false && inimigos[i]->getPower() == true) {
                            inimigos[k]->setLife(inimigos[k]->getLife()-1);
                            inimigos[i]->setScore(inimigos[i]->getScore()+(100*(i+1)));
                            if(inimigos[k]->getLife() >= 0) {
                                setInitialPosition(inimigos[k], cenarioJogo);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Servidor::criarCenario(std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<View> view) {

    int mapa1[21][25] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 2
            {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 3
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 4
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 5
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 6
            {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1}, // 7
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 8
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 9
            {1, 3, 3, 3, 3, 3, 3, 3, 1, 5, 5, 5, 5, 5, 5, 5, 1, 3, 3, 3, 3, 3, 3, 3, 1}, // 10
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 11
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 12
            {1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1}, // 13
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 14
            {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 15
            {1, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 1}, // 16
            {1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1}, // 17
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 18
            {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1}, // 19
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 20
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // 21
        };

    int **mapa = (int**)malloc(21*sizeof(int*));
    for (int i = 0; i < 21; i++) {
        mapa[i] = (int*)malloc(25*sizeof(int));
        for (int j = 0; j < 25; j++) {
            mapa[i][j] = mapa1[i][j];
        }
    }

    char const *img2 = "./assets/mapinha.jpg";
    std::shared_ptr<CenarioJogo> novoCenarioJogo (new CenarioJogo(mapa));
    std::shared_ptr<Textura> textura2 (new Textura(view->getRenderer(), img2, 0, 0)); // textura 2 (fundo)
    novoCenarioJogo->setTextura(textura2);
    cenarioJogo.push_back(novoCenarioJogo);
}


void Servidor::criarBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<View> view) {

    int mapa1[21][25] =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 2
            {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 3
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 4
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 5
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 6
            {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1}, // 7
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 8
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 9
            {1, 3, 3, 3, 3, 3, 3, 3, 1, 5, 5, 5, 5, 5, 5, 5, 1, 3, 3, 3, 3, 3, 3, 3, 1}, // 10
            {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 11
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 12
            {1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1}, // 13
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 14
            {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 15
            {1, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 1}, // 16
            {1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1}, // 17
            {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 18
            {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1}, // 19
            {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 20
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // 21
        };


    int **ball = (int**)malloc(sizeof(int*));
    ball[0] = (int*)malloc(sizeof(int));
    ball[0][0] = 6;
    char const* ball_name = "./assets/bolinha.jpg";
    char const* ball_name1 = "./assets/bolao.jpg";
    int **mapa = (int**)malloc(21*sizeof(int*));
    for (int i = 0; i < 21; i++) {
        mapa[i] = (int*)malloc(25*sizeof(int));
        for (int j = 0; j < 25; j++) {
            mapa[i][j] = mapa1[i][j];
            if (mapa[i][j] == 3) {
                std::shared_ptr<Bolinha> bolinha (new Bolinha(ball, false, 6, ball_name));
                std::shared_ptr<Textura> texturaB (new Textura(view->getRenderer(), ball_name, 0, 0));
                bolinha->setTextura(texturaB);
                bolinhas.push_back(bolinha);
            }
            else if (mapa[i][j] == 6) {
                std::shared_ptr<Bolinha> bolinha (new Bolinha(ball, true, 6, ball_name1));
                std::shared_ptr<Textura> texturaB (new Textura(view->getRenderer(), ball_name1, 0, 0));
                bolinha->setTextura(texturaB);
                bolinhas.push_back(bolinha);
            }
        }
    }

}

void Servidor::criarInimigos(std::vector<std::shared_ptr<Personagem>> &inimigos, int quantidade, std::shared_ptr<View> view) {

    int pacman[10][10] = {
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    };

    int **npc1 = (int**)malloc(sizeof(int*)*10);
    for (int i = 0; i < 10; i++) {
        npc1[i] = (int*)malloc(sizeof(int)*10);
        for (int j = 0; j < 10; j++) {
            npc1[i][j] = pacman[i][j];
        }
    }

    char buffer2[100] = ".jpg";
    for (int i = 0; i < quantidade; i++) {
        char buffer[100] = "./assets/npc";
        std::string num = std::to_string(i);
        strcat(buffer, num.c_str());
        strcat(buffer, buffer2);
        std::string name = "local";
        std::shared_ptr<Personagem> inimigo (new Personagem(npc1, true, true, 30, 30, buffer, name));
        std::shared_ptr<Textura> textura12 (new Textura(view->getRenderer(), buffer, 0, 0));
        inimigo->setTextura(textura12);
        inimigos.push_back(inimigo);
    }

}

std::shared_ptr<Personagem> Servidor::criarPersonagem(std::vector<std::shared_ptr<Personagem>> &personagens,std::shared_ptr<View> view, std::string name) {
    
    int pacman2[10][10] = {
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    };
    
    char const *img1 = "./assets/pacman.jpg";
    int **pacman = (int**)malloc(sizeof(int*)*10);
    for (int i = 0; i < 10; i++) {
        pacman[i] = (int*)malloc(sizeof(int)*10);
        for (int j = 0; j < 10; j++) {
            pacman[i][j] = pacman2[i][j];
        }
    }
    std::shared_ptr<Personagem> personagem (new Personagem(pacman, false, false, 30, 30, img1, name));
    std::shared_ptr<Textura> textura1 (new Textura(view->getRenderer(), img1, 0, 0)); // textura 1 (movel)
    personagem->setTextura(textura1);
    personagens.push_back(personagem);
    return personagem;

}

void Servidor::darPoderParaBolinha(std::shared_ptr<Bolinha> bolinha, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<View> view, std::shared_ptr<int> cont) {
    bolinha->setOldDisplay(bolinha->getDisplay());  
    bolinha->setDisplay(true);
    bolinha->setPower(true);
    bolinha->setScore(50);
    int x = bolinha->getTextura()->getTarget().x;
    int y = bolinha->getTextura()->getTarget().y;
    char const* ball_name1 = "./assets/bolao.jpg";
    std::shared_ptr<Textura> texturaBolaComPoder (new Textura(view->getRenderer(), ball_name1, x, y));

    std::cout << "x: " << x << "; y: " << y << std::endl;

    int **mapa = cenarioJogo->getMap();
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            mapa[y+i][x+j] = 6;
        }
    }
    cenarioJogo->setMap(mapa);
    bolinha->setTextura(texturaBolaComPoder);
}

bool Servidor::aindaTemBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas) {
    bool temBolinhas = false;
    for (int i = 0; i < bolinhas.size(); i++) {
        if (bolinhas[i]->getPower() == false && bolinhas[i]->getDisplay()) {
            temBolinhas = true;
            break;
        }
    }
    return temBolinhas;
}

void Servidor::iniciarServidor(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado) {

    auto inserirJogadores = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::shared_ptr<CenarioJogo> cenarioJogo) {
        udp::endpoint local_remote_endpoint;
        char v[1000];
        while(1) {
            memset(v, 0, 1000);
            meu_socket_receive.receive_from(boost::asio::buffer(v, 1000), // Local do buffer
                            remote_endpoint_receive);            // Confs. do Cliente
            foo.lock();
            local_remote_endpoint = remote_endpoint_receive;

            json j = json::parse(v);
            
            std::string s1 = j["request"].get<std::string>();
            std::string s2 = "connect";
            if (s1.compare(s2) == 0) {
                std::string name = j["name"].get<std::string>();
                std::cout << "IP: " << local_remote_endpoint << " - connected successfully" << std::endl;
                bool notConnected = true;
                bool reconnect = false;
                for (int i = 0; i < personagens.size(); i++) {
                    if (name.compare(personagens[i]->getName()) == 0) {
                        if (personagens[i]->getLife() >= 0) {
                            notConnected = false;
                            std::cout << "IP already connected!" << std::endl;
                            break;
                        }
                        else {
                            personagens[i]->setLife(2);
                            setInitialPosition(personagens[i], cenarioJogo);
                            personagens[i]->setIp(local_remote_endpoint);
                            reconnect = true;
                            personagens[i]->setFree(true);
                            break;
                        }
                    }
                }
                json j2;
                j2["request"] = "ip_already_connected";
                if (notConnected) {
                    if (reconnect == false) {
                        std::shared_ptr<Personagem> personagem = criarPersonagem(personagens, view, name);
                        setInitialPosition(personagem, cenarioJogo);
                        personagem->setIp(local_remote_endpoint);
                        std::cout << "character: " << name << " created successfully!" << std::endl;
                        personagem->setFree(true);
                    }
                    j2["request"] = "success";
                }
                std::string s = j2.dump();
                std::cout << s << std::endl;
                meu_socket_receive.send_to(boost::asio::buffer(s), local_remote_endpoint);
            }
            foo.unlock();
        }
    };

    auto controlarPersonagem = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {

        char v[100000];
        udp::endpoint local_remote_endpoint;
        while(1) {
            memset(v, 0, 100000);
            meu_socket_receive.receive_from(boost::asio::buffer(v, 100000), // Local do buffer
                            remote_endpoint_receive);            // Confs. do Cliente
            local_remote_endpoint = remote_endpoint_receive;
            json j = json::parse(v);
            std::string s1 = j["request"].get<std::string>();
            std::string s2 = "play";
            std::string s3 = "remove";
            if (s1.compare(s2) == 0) {
                std::string name = j["name"].get<std::string>();
                if (timer->elapsedSeconds() > 10) {
                    int randomBall = rand() % (bolinhas.size()-1);
                    if (randomBall < 0) randomBall = 0;
                    else if (randomBall >= bolinhas.size()) randomBall = bolinhas.size() - 1;
                    darPoderParaBolinha(bolinhas[randomBall], cenarioJogo[0], view, 0);
                    timer->stop();
                }
                for (int i = 0; i < personagens.size(); i++) {
                    if (name.compare(personagens[i]->getName()) == 0) {
                        characterControl(personagens[i], personagens, bolinhas, cenarioJogo[0], j["vertical"].get<int>(), j["horizontal"].get<int>(), timer);
                        break;
                    }
                }
            }
            else if (s1.compare(s3) == 0) {
                std::string name = j["name"].get<std::string>();
                for (int i = 0; i < personagens.size(); i++) {
                    if (name.compare(personagens[i]->getName()) == 0) {
                        personagens[i]->setLife(-1);
                        personagens[i]->setScore(0);
                        if (personagens[i]->getPower()) personagens[i]->setPower();
                        personagens[i]->setFree(false);
                    }
                }
            }
        }
    };

    auto enviarDados = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {
        char v[100000];
        while(1) {
            json j2;
            j2["request"] = "render";

            std::vector<json> characters;
            //save characters
            for (int i = 0; i < personagens.size(); i++) {
                if (personagens[i]->getFree() == false) continue;
                json en;
                en["x"] = personagens[i]->getTextura()->getTarget().x;
                en["y"] = personagens[i]->getTextura()->getTarget().y;
                en["life"] = personagens[i]->getLife();
                characters.push_back(en);
            }

            std::vector<json> points;
            //save points
            for (int i = 0; i < bolinhas.size(); i++) {
                json pts;
                pts["x"] = bolinhas[i]->getTextura()->getTarget().x;
                pts["y"] = bolinhas[i]->getTextura()->getTarget().y;
                pts["display"] = bolinhas[i]->getDisplay();
                pts["score"] = bolinhas[i]->getScore();
                pts["power"] = bolinhas[i]->getPower();
                points.push_back(pts);
            }

            j2["characters"] = characters;
            j2["bolinhas"] = points;
            
            j2["active"] = true;
            j2["dead"] = false;

            for (int p = 0; p < personagens.size(); p++) {
                if (personagens[p]->getFree() == false) continue;

                bool ativo = true;
                bool dead = false;
                if (personagens[p]->getLife() < 0) {
                    j2["active"] = false;
                    j2["dead"] = true;
                }
                std::string s = j2.dump();
                meu_socket_receive.send_to(boost::asio::buffer(s), personagens[p]->getIp());
            }
        }

    };

    auto processarJogo = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {
        
        while(1) {
            allCharactersControl(personagens, bolinhas, cenarioJogo[0], timer);
        }
    };

    std::vector<std::shared_ptr<Personagem>> personagens;
    std::vector<std::shared_ptr<Bolinha>> bolinhas;
    std::vector<std::shared_ptr<CenarioJogo>> cenarioJogo;
    std::shared_ptr<Timer> timer (new Timer());

    criarBolinhas(bolinhas, view);
    criarCenario(cenarioJogo, view);
    setBallsPositions(cenarioJogo[0], bolinhas);

    int randomBall = rand() % (bolinhas.size()-1);
    if (randomBall < 0) randomBall = 0;
    else if (randomBall >= bolinhas.size()) randomBall = bolinhas.size() - 1;
    darPoderParaBolinha(bolinhas[randomBall], cenarioJogo[0], view, 0);

    std::thread t1(inserirJogadores, std::ref(personagens), std::ref(view), std::ref(cenarioJogo[0]));
    std::thread t2(controlarPersonagem, std::ref(personagens), std::ref(view), std::ref(bolinhas), std::ref(cenarioJogo), std::ref(timer));
    std::thread t3(enviarDados, std::ref(personagens), std::ref(view), std::ref(bolinhas), std::ref(cenarioJogo), std::ref(timer));
    std::thread t4(processarJogo, std::ref(personagens), std::ref(view), std::ref(bolinhas), std::ref(cenarioJogo), std::ref(timer));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::cout << "Fechando servidor" << std::endl;
}