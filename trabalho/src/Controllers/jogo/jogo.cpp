#include "../../../Include/Controllers/jogo/jogo.hpp"
#include <iostream>
#include <memory>
#include <cmath>

Jogo::Jogo() {};

Jogo::~Jogo(){};

int Jogo::setSDLInit() {
    if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
        std::cout << SDL_GetError();
    return 1;
  }
  return 0;
}

void Jogo::setBallsPositions(std::shared_ptr<CenarioJogo> cenarioJogo, std::vector<std::shared_ptr<Bolinha>> &bolinhas) {
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

void Jogo::setInitialPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo) {
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

int Jogo::setCharacterPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo, int x, int y, int oldX, int oldY){
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

void Jogo::characterControl(std::shared_ptr<Personagem> personagem, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, int vertical, int horizontal, std::shared_ptr<Timer> timer) { 
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

void Jogo::allCharactersControl(std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Timer> timer) {
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


int Jogo::localCharacterControl(std::shared_ptr<Personagem> personagem, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Teclado> teclado, std::shared_ptr<int> x, std::shared_ptr<int> y, std::shared_ptr<int> cont, std::shared_ptr<View> view, std::shared_ptr<Timer> timer, std::shared_ptr<Timer> powerTimer) { 
    int newX = 0;
    int newY = 0;

    if (powerTimer->elapsedSeconds() > 10) {
        if (personagem->getPower() == true) personagem->setPower();
        powerTimer->stop();
    }
    
    teclado->updateState();
    if ((teclado->getState())[SDL_SCANCODE_UP]) {
        newX = 0; 
        newY = -2;
    }
    else if ((teclado->getState())[SDL_SCANCODE_DOWN]) {
        newX = 0; 
        newY = 2;
    }
    else if ((teclado->getState())[SDL_SCANCODE_RIGHT]) {
        newX = 2; 
        newY = 0;
    }
    else if ((teclado->getState())[SDL_SCANCODE_LEFT]) {
        newX = -2; 
        newY = 0;
    }
    int i = setCharacterPosition(personagem, cenarioJogo, newX, newY, (*x), (*y));
    if (i == 0) {
        (*x) = newX;
        (*y) = newY;
    }
    int xpse = personagem->getTextura()->getTarget().x;
    int ypse = personagem->getTextura()->getTarget().y;
    int xpid = personagem->getTextura()->getTarget().x+29;
    int ypid = personagem->getTextura()->getTarget().y+29;
    for (int i = 0; i < bolinhas.size(); i++) {
        int xbse = bolinhas[i]->getTextura()->getTarget().x;
        int ybse = bolinhas[i]->getTextura()->getTarget().y;
        int xbid = bolinhas[i]->getTextura()->getTarget().x+29;
        int ybid = bolinhas[i]->getTextura()->getTarget().y+29;
        if ((xbse == xpse && ((ypse <= ybid-10 && ypse >= ybse+10) || (ypid <= ybid-10 && ypid >= ybse+10))) || (ybse == ypse && ((xpse <= xbid-10 && xpse >= xbse+10) || (xpid <= xbid-10 && xpid >= xbse+10)))) {
            if (bolinhas[i]->getDisplay() == true) {
                bolinhas[i]->setDisplay(false);
                personagem->setScore(personagem->getScore()+bolinhas[i]->getScore());
                bolinhas[i]->setOldDisplay(false);
                if (bolinhas[i]->getPower() == true && personagem->getPower() == false) {
                    personagem->setPower();
                    timer->start();
                    powerTimer->start();
                }
                if (bolinhas[i]->getPower() == false) {
                    (*cont)++;
                }
            }
        }
    }

    for (int i = 0; i < inimigos.size(); i++) {
        int xise = inimigos[i]->getTextura()->getTarget().x;
        int yise = inimigos[i]->getTextura()->getTarget().y;
        int xiid = inimigos[i]->getTextura()->getTarget().x+29;
        int yiid = inimigos[i]->getTextura()->getTarget().y+29;


        if (((xpse <= xise && xpid >= xise) || (xpse <= xiid && xpid >= xiid)) && ((ypse <= yise && ypid >= yise) || (ypse <= yiid && ypid >= yiid))) {
            if (inimigos[i]->getLife() >= 0) {
                if (personagem->getPower() == true && personagem->getGhost() == false && inimigos[i]->getGhost() == true) {
                    inimigos[i]->setLife(inimigos[i]->getLife()-1);
                    personagem->setScore(personagem->getScore()+(100*(i+1)));
                    return 0;
                }
                return 1;
            }
        }
    }
    std::cout << "Score: "<< personagem->getScore() <<" ----------------- Extra Life: "<< personagem->getLife() <<"/2 ----------------- Power: " << personagem->getPower();
    if (personagem->getPower()) std::cout << " ----------------- Power Time Left: " << 10-powerTimer->elapsedSeconds();
    std::cout << std::endl;
    if ((*cont) == bolinhas.size()) return 2;
    return 0;
}

void Jogo::localNpcControl(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo, int *x, int *y, int i) { 
    int random0 = rand() % 100;
    int random1 = rand() % 2;
    int random2 = rand() % 2;
    int newX = 0;
    int newY = 0;
    std::shared_ptr<Textura> textura = personagem->getTextura();
    int tx = textura->getTarget().x;
    int ty = textura->getTarget().y;
    if (random0 == 0 || (x[i] == 0 && y[i] == 0)) {
        if (random1 == 0 && random2 == 0) {
            newX = -2;
            newY = 0;
        }
        else if (random1 == 0 && random2 == 1) {
            newX = 2;
            newY = 0;
        }
        else if (random1 == 1 && random2 == 0 && ((cenarioJogo->getMap()[ty-1][tx] == 2 && cenarioJogo->getMap()[ty][tx] == 5) || cenarioJogo->getMap()[ty][tx] != 5)) {
            newX = 0;
            newY = -2;
        }
        else if (random1 == 1 && random2 == 1 && cenarioJogo->getMap()[ty][tx] != 2 && cenarioJogo->getMap()[ty+29][tx] != 2 && cenarioJogo->getMap()[ty+30][tx] != 2 && cenarioJogo->getMap()[ty][tx] != 5) {
            newX = 0;
            newY = 2;
        }
    }
    int j = setCharacterPosition(personagem, cenarioJogo, newX, newY, x[i], y[i]);
    if (j == 0) {
        x[i] = newX;
        y[i] = newY;
    }
}

void Jogo::carregarJogo(std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<int> cont) {
    std::ifstream arquivo;
    std::stringstream s;
    arquivo.open("save.txt");
    if (arquivo.is_open() ) {
        s << arquivo.rdbuf();
        auto j3 = json::parse(s.str());
        
        personagens[0]->setLife(j3["personagem"]["life"].get<int>());
        personagens[0]->setScore(j3["personagem"]["score"].get<int>());
        personagens[0]->getTextura()->setTarget(j3["personagem"]["x"].get<int>(), j3["personagem"]["y"].get<int>());

        std::vector<json> in = j3["inimigos"].get<std::vector<json>>();
        for (int i = 0; i < inimigos.size(); i++) {
            inimigos[i]->setLife(in[i]["life"].get<int>());
            inimigos[i]->getTextura()->setTarget(in[i]["x"].get<int>(), in[i]["y"].get<int>());
        }

        std::vector<json> pt = j3["bolinhas"].get<std::vector<json>>();
        for (int i = 0; i < bolinhas.size(); i++) {
            bolinhas[i]->setDisplay(pt[i]["display"].get<bool>());
            bolinhas[i]->setScore(pt[i]["score"].get<unsigned long int>());
            bolinhas[i]->getTextura()->setTarget(pt[i]["x"].get<int>(), pt[i]["y"].get<int>());
        }
        arquivo.close();
    }
}

void Jogo::criarCenario(std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<View> view) {

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


void Jogo::criarBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<View> view) {

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

void Jogo::criarInimigos(std::vector<std::shared_ptr<Personagem>> &inimigos, int quantidade, std::shared_ptr<View> view) {

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

std::shared_ptr<Personagem> Jogo::criarPersonagem(std::vector<std::shared_ptr<Personagem>> &personagens,std::shared_ptr<View> view, std::string name) {
    
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


void Jogo::iniciarJogo(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado) {
    SDL_Event event;
    std::vector<std::shared_ptr<Personagem>> inimigos;
    std::vector<std::shared_ptr<Personagem>> personagens;
    std::vector<std::shared_ptr<Bolinha>> bolinhas;
    std::vector<std::shared_ptr<CenarioJogo>> cenarioJogo;


    criarBolinhas(bolinhas, view);
    criarInimigos(inimigos, 5, view);
    criarCenario(cenarioJogo, view);

    char const *img3 = "./assets/pacwpp.jpg";

    std::shared_ptr<Textura> menuInicial (new Textura(view->getRenderer(), img3, 0, 0)); // textura 2 (fundo)

    std::shared_ptr<int> cont (new int);
    (*cont) = 0;

    std::shared_ptr<int> x (new int);
    std::shared_ptr<int> y (new int);
    (*x) = 0;
    (*y) = 0;
    std::shared_ptr<int> x1 (new int);
    std::shared_ptr<int> y1 (new int);
    int *ix = (int*)malloc(inimigos.size()*sizeof(int));
    int *iy = (int*)malloc(inimigos.size()*sizeof(int));
    for (int i = 0; i < inimigos.size(); i++) {
        ix[i] = 0;
        iy[i] = 0;
        setInitialPosition(inimigos[i], cenarioJogo[0]);
    }

    setBallsPositions(cenarioJogo[0], bolinhas);

    bool single = true;

    bool rodando = true;

    bool carregar = false;

    bool jogar = false;

    while (rodando) {

        teclado->updateState();
        if ((teclado->getState())[SDL_SCANCODE_RETURN]) {
            rodando = false;
            jogar = true;
        }
        else if ((teclado->getState())[SDL_SCANCODE_SPACE]) {
            carregar = true;
            rodando = false;
            jogar = true;
        }
        else if ((teclado->getState())[SDL_SCANCODE_TAB]) {
            conectarServidor(view, teclado);
            rodando = false;
            break;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                rodando = false;
            }
        }
        view->renderClear();
        view->renderMain(menuInicial);
        view->renderPresent();
        SDL_Delay(10);
    }

    if (single && jogar) {
        std::string name;
        criarPersonagem(personagens, view, name);
        setInitialPosition(personagens[0], cenarioJogo[0]);
        if (carregar) carregarJogo(bolinhas, inimigos, personagens, cont);
        int randomBall = rand() % (bolinhas.size()-1);
        if (randomBall < 0) randomBall = 0;
        else if (randomBall >= bolinhas.size()) randomBall = bolinhas.size() - 1;
        darPoderParaBolinha(bolinhas[randomBall], cenarioJogo[0], view, cont);
        jogarSingle(view, teclado, bolinhas, inimigos, cenarioJogo[0], personagens[0], x, y, cont, ix, iy);
    }

}


void Jogo::jogarSingle(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<Personagem>> &inimigos, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Personagem> personagem, std::shared_ptr<int> x, std::shared_ptr<int> y, std::shared_ptr<int> cont, int * ix, int * iy) {
    SDL_Event event;
    std::shared_ptr<Timer> timer (new Timer());
    std::shared_ptr<Timer> powerTimer (new Timer());
    char const *img4 = "./assets/pacwpp2.jpg";

    std::shared_ptr<Textura> derrota (new Textura(view->getRenderer(), img4, 0, 0)); // textura 2 (fundo)

    char const *img5 = "./assets/pacwpp3.jpg";

    std::shared_ptr<Textura> vitoria (new Textura(view->getRenderer(), img5, 0, 0)); // textura 2 (fundo)

    int state = 2;

    bool rodando = true;
    while (rodando) {
        // std::cout << "tempo: " << timer->elapsedSeconds() << std::endl;
        if (timer->elapsedSeconds() > 10) {
            int randomBall = rand() % (bolinhas.size()-1);
            if (randomBall < 0) randomBall = 0;
            else if (randomBall >= bolinhas.size()) randomBall = bolinhas.size() - 1;
            darPoderParaBolinha(bolinhas[randomBall], cenarioJogo, view, cont);
            timer->stop();
        }
        int res = localCharacterControl(personagem, inimigos, bolinhas, cenarioJogo, teclado, x, y, cont, view, timer, powerTimer);
        if (res == 2 || aindaTemBolinhas(bolinhas) == false) {
            fimDeJogo(view, vitoria);
            break; 
        }
        if(personagem->getLife() >= 0 && res == 1) {
            personagem->setLife(personagem->getLife()-1);
            if(personagem->getLife() >= 0) setInitialPosition(personagem, cenarioJogo);
            else {
                fimDeJogo(view, derrota);
                break;
            }
        }
        for (int i = 0; i < inimigos.size(); i++) {
            localNpcControl(inimigos[i], cenarioJogo, ix, iy, i);
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                json j;
                json ps;   

                //save main character
                ps["x"] = personagem->getTextura()->getTarget().x;
                ps["y"] = personagem->getTextura()->getTarget().y;
                ps["score"] = personagem->getScore();
                ps["life"] = personagem->getLife();
                ps["power"] = personagem->getPower();


                std::vector<json> enemies;
                //save enemies
                for (int i = 0; i < inimigos.size(); i++) {
                    json en;
                    en["x"] = inimigos[i]->getTextura()->getTarget().x;
                    en["y"] = inimigos[i]->getTextura()->getTarget().y;
                    en["life"] = inimigos[i]->getLife();
                    enemies.push_back(en);
                }

                std::vector<json> points;
                //save points
                for (int i = 0; i < bolinhas.size(); i++) {
                    json pts;
                    pts["x"] = bolinhas[i]->getTextura()->getTarget().x;
                    pts["y"] = bolinhas[i]->getTextura()->getTarget().y;
                    if (bolinhas[i]->getOldDisplay()) pts["display"] = bolinhas[i]->getDisplay();
                    else pts["display"] = false;
                    pts["score"] = bolinhas[i]->getScore();
                    points.push_back(pts);
                }

                std::ofstream arquivo1;
                arquivo1.open("save.txt");

                j["personagem"] = ps;
                j["inimigos"] = enemies;
                j["bolinhas"] = points;
                arquivo1 << j << std::endl;
                arquivo1.close();
                rodando = false;
            }
        }
        view->renderClear();
        view->renderBackground(cenarioJogo->getTextura());
        for (int i = 0; i < bolinhas.size(); i++) {
            if (bolinhas[i]->getDisplay() == true) view->renderCharacter(bolinhas[i]->getTextura());
        }
        for (int i = 0; i < inimigos.size(); i++) {
            if (inimigos[i]->getLife() >= 0) view->renderCharacter(inimigos[i]->getTextura());
        }
        if (personagem->getLife() >= 0) view->renderCharacter(personagem->getTextura());
        view->renderPresent();


        //save
        SDL_Delay(10);
    }
};

void Jogo::darPoderParaBolinha(std::shared_ptr<Bolinha> bolinha, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<View> view, std::shared_ptr<int> cont) {
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

bool Jogo::aindaTemBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas) {
    bool temBolinhas = false;
    for (int i = 0; i < bolinhas.size(); i++) {
        if (bolinhas[i]->getPower() == false && bolinhas[i]->getDisplay()) {
            temBolinhas = true;
            break;
        }
    }
    return temBolinhas;
}


void Jogo::conectarServidor(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado) {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    json j;

    std::stringstream ss;
    ss << username << "@" << hostname;
    std::string name = ss.str();

    j["name"] = name;
    j["request"] = "connect";

    boost::asio::io_service io_service;

    udp::endpoint local_endpoint(udp::v4(), 0);
    udp::socket meu_socket(io_service, local_endpoint);

    json config;
    std::ifstream file("config.txt");
    std::string str;
    size_t pos = 0;
    std::string delimiter = "=";
    while (std::getline(file, str)) {
        pos = str.find(delimiter);
        std::cout << pos << std::endl;
        std::string token = str.substr(0, pos);
        std::cout << token << std::endl;
        str.erase(0, pos + delimiter.length());
        std::string token2 = str;
        std::cout << token2 << std::endl;
        config[token] = token2;
    }

    // Encontrando IP remoto
    boost::asio::ip::address ip_remoto =
        boost::asio::ip::address::from_string(config["SERVER_IP"]);

    udp::endpoint remote_endpoint(ip_remoto, 9001);

    std::string s = j.dump();
    meu_socket.send_to(boost::asio::buffer(s), remote_endpoint);

    char v[1000];
    meu_socket.receive_from(boost::asio::buffer(v, 1000), // Local do buffer
                    remote_endpoint);
    json j2 = json::parse(v);
    std::string s1 = j2["response"];
    std::string s2 = "success";
    std::string s3 = "ip_already_connected";
    bool rodando = false;
    if (s1.compare(s2) == 0) {
        std::cout << "Connected Successfully" << std::endl;
        bool gameover = jogarMulti(view, teclado, name);
        if (gameover) {
            rodando = true;
        }
    }
    else if (s1.compare(s3) == 0) {
        std::cout << "IP already connected!" << std::endl;
        return;
    }
    while(rodando) {
        char const *img4 = "./assets/pacwpp2.jpg";
        std::shared_ptr<Textura> derrota (new Textura(view->getRenderer(), img4, 0, 0)); // textura 2 (fundo)
        fimDeJogo(view, derrota);
        rodando = false;
    }
}

bool Jogo::jogarMulti(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado, std::string name) {

    std::shared_ptr<json> config (new json);
    std::ifstream file("config.txt");
    std::string str;
    size_t pos = 0;
    std::string delimiter = "=";
    std::cout << "configuring" << std::endl;
    while (std::getline(file, str)) {
        pos = str.find(delimiter);
        std::string token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        std::string token2 = str;
        (*config)[token] = token2;
    }
    std::cout << "configured" << std::endl;
    
    std::vector<std::shared_ptr<Personagem>> personagens;
    std::vector<std::shared_ptr<Bolinha>> bolinhas;
    std::vector<std::shared_ptr<CenarioJogo>> cenarioJogo;

    auto render = [this](std::shared_ptr<View> view, std::vector<std::shared_ptr<Personagem>> personagens, std::vector<std::shared_ptr<Bolinha>> bolinhas, std::vector<std::shared_ptr<CenarioJogo>> cenarioJogo, std::shared_ptr<bool> gameover, std::shared_ptr<json> config, std::string name, std::shared_ptr<bool> rodando) {
        std::shared_ptr<Timer> timeout (new Timer());
        boost::asio::io_service io_service;

        udp::endpoint local_endpoint(udp::v4(), 0);
        udp::socket meu_socket(io_service, local_endpoint);
        meu_socket.non_blocking(true);

        // Encontrando IP remoto
        boost::asio::ip::address ip_remoto =
            boost::asio::ip::address::from_string((*config)["SERVER_IP"]);

        udp::endpoint remote_endpoint1(ip_remoto, 9003);

        char const* bolao = "./assets/bolao.jpg";

        char v[1000000];
        json j;
        while ((*rodando)) {
            boost::system::error_code error = boost::asio::error::would_block;
            j["request"] = "data";
            j["name"] = name;
            std::string s2 = j.dump();
            meu_socket.send_to(boost::asio::buffer(s2), remote_endpoint1);
            std::cout << "Sending request!!!" << std::endl;

            timeout->start();
            bool received = false;
            while (timeout->elapsedSeconds() < 0.1) {
                memset(v, 0, 1000000);
                size_t len = 0;
                len = meu_socket.receive_from(boost::asio::buffer(v, 1000000), // Local do buffer
                            remote_endpoint1, 0, error);
                if (len > 0) {
                    received = true;
                    break;
                }
            }
            timeout->stop();
            if (received == false) continue;
            json j3 = json::parse(v);
            std::cout << j3 << std::endl;
            if (j3["active"].get<bool>() == false) {
                (*rodando) = false;
                (*gameover) = j3["dead"].get<bool>();
                break;
            }

            std::vector<json> ch = j3["characters"].get<std::vector<json>>();
            while (personagens.size() != ch.size()) {
                criarPersonagem(personagens, view, name);
            }
            for (int i = 0; i < ch.size(); i++) {
                personagens[i]->setLife(ch[i]["life"].get<int>());
                personagens[i]->getTextura()->setTarget(ch[i]["x"].get<int>(), ch[i]["y"].get<int>());
            }

            std::vector<json> pt = j3["bolinhas"].get<std::vector<json>>();
            for (int i = 0; i < bolinhas.size(); i++) {
                bolinhas[i]->setDisplay(pt[i]["display"].get<bool>());
                bolinhas[i]->setPower(pt[i]["power"].get<bool>());
                bolinhas[i]->setScore(pt[i]["score"].get<unsigned long int>());
                if (bolinhas[i]->getPower()) {
                    std::shared_ptr<Textura> bolaPoder (new Textura(view->getRenderer(), bolao, pt[i]["x"].get<int>(), pt[i]["y"].get<int>()));
                    bolinhas[i]->setTextura(bolaPoder);
                }
                else bolinhas[i]->getTextura()->setTarget(pt[i]["x"].get<int>(), pt[i]["y"].get<int>());
            }

            view->renderClear();
            view->renderBackground(cenarioJogo[0]->getTextura());
            for (int i = 0; i < bolinhas.size(); i++) {
                if (bolinhas[i]->getDisplay() == true) view->renderCharacter(bolinhas[i]->getTextura());
            }
            for (int i = 0; i < personagens.size(); i++) {
                if (personagens[i]->getLife() >= 0) view->renderCharacter(personagens[i]->getTextura());
            }
            view->renderPresent();
        }

    };

    auto control = [this](std::shared_ptr<Teclado> teclado, std::vector<std::shared_ptr<Personagem>> personagens, std::vector<std::shared_ptr<Bolinha>> bolinhas, std::vector<std::shared_ptr<CenarioJogo>> cenarioJogo, std::shared_ptr<bool> gameover, std::shared_ptr<json> config, std::string name, std::shared_ptr<bool> rodando) {
        std::shared_ptr<Timer> controlTimer (new Timer());
        SDL_Event event;
        boost::asio::io_service io_service;

        udp::endpoint local_endpoint(udp::v4(), 0);
        udp::socket meu_socket(io_service, local_endpoint);

        // Encontrando IP remoto
        boost::asio::ip::address ip_remoto =
            boost::asio::ip::address::from_string((*config)["SERVER_IP"]);

        udp::endpoint remote_endpoint1(ip_remoto, 9002);

        int newX = 0;
        int newY = 0;
        json j;
        controlTimer->start();
        while((*rodando)) {
            if (controlTimer->elapsedSeconds() > 0.01) {
                j["request"] = "play";

                teclado->updateState();
                if ((teclado->getState())[SDL_SCANCODE_UP]) {
                    newX = 0; 
                    newY = -2;
                }
                else if ((teclado->getState())[SDL_SCANCODE_DOWN]) {
                    newX = 0; 
                    newY = 2;
                }
                else if ((teclado->getState())[SDL_SCANCODE_RIGHT]) {
                    newX = 2; 
                    newY = 0;
                }
                else if ((teclado->getState())[SDL_SCANCODE_LEFT]) {
                    newX = -2; 
                    newY = 0;
                }

                j["vertical"] = newY;
                j["horizontal"] = newX;
                j["name"] = name;

                std::string s = j.dump();
                meu_socket.send_to(boost::asio::buffer(s), remote_endpoint1);
                controlTimer->stop();
                controlTimer->start();
            }
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    (*rodando) = false;
                    j["request"] = "remove";
                    std::string s = j.dump();
                    meu_socket.send_to(boost::asio::buffer(s), remote_endpoint1);
                }
            }
        }

    };

    criarBolinhas(bolinhas, view);
    criarCenario(cenarioJogo, view);
    std::shared_ptr<bool> gameover (new bool);
    (*gameover) = false;
        std::shared_ptr<bool> rodando (new bool);
    (*rodando) = true;

    std::cout << (*config)["SERVER_IP"] << std::endl;

    std::thread t1(render, view, std::ref(personagens), std::ref(bolinhas), std::ref(cenarioJogo), gameover, config, name, rodando);
    std::thread t2(control, teclado, std::ref(personagens), std::ref(bolinhas), std::ref(cenarioJogo), gameover, config, name, rodando);
    t1.join();
    t2.join();

    return (*gameover);
}

void Jogo::fimDeJogo(std::shared_ptr<View> view, std::shared_ptr<Textura> tela) {
    SDL_Event event;
    bool rodando = true;
    while (rodando) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                rodando = false;
            }
        }
        view->renderClear();
        view->renderMain(tela);
        view->renderPresent();
        SDL_Delay(10);
    }
}

void Jogo::iniciarServidor(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado) {

    auto inserirJogadores = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::shared_ptr<CenarioJogo> cenarioJogo) {
        boost::asio::io_service my_io_service; // Conecta com o SO

        udp::endpoint local_endpoint(udp::v4(), 9001); // endpoint: contem
                                                        // conf. da conexao (ip/port)

        udp::socket meu_socket(my_io_service,   // io service
                                local_endpoint); // endpoint

        udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar
        char v[1000];
        while(1) {
            memset(v, 0, 1000);
            meu_socket.receive_from(boost::asio::buffer(v, 1000), // Local do buffer
                            remote_endpoint);            // Confs. do Cliente
            json j = json::parse(v);

            std::string s1 = j["request"].get<std::string>();
            std::string s2 = "connect";
            if (s1.compare(s2) == 0) {
                std::string name = j["name"].get<std::string>();
                std::cout << "IP: " << remote_endpoint << " - connected successfully" << std::endl;
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
                            reconnect = true;
                        }
                    }
                }
                json j2;
                if (notConnected) {
                    if (reconnect == false) {
                        std::shared_ptr<Personagem> personagem = criarPersonagem(personagens, view, name);
                        setInitialPosition(personagem, cenarioJogo);
                        std::cout << "character: " << name << " created successfully!" << std::endl;
                    }
                    j2["response"] = "success";
                    std::string s = j2.dump();
                    meu_socket.send_to(boost::asio::buffer(s), remote_endpoint);
                }
                else {
                    j2["response"] = "ip_already_connected";
                    std::string s = j2.dump();
                    meu_socket.send_to(boost::asio::buffer(s), remote_endpoint);
                }
            }
        }
    };

    auto controlarPersonagem = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {
        boost::asio::io_service my_io_service; // Conecta com o SO

        udp::endpoint local_endpoint(udp::v4(), 9002); // endpoint: contem
                                                        // conf. da conexao (ip/port)

        udp::socket meu_socket(my_io_service,   // io service
                                local_endpoint); // endpoint

        udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar

        char v[100000];

        while(1) {
            memset(v, 0, 100000);
            meu_socket.receive_from(boost::asio::buffer(v, 100000), // Local do buffer
                            remote_endpoint);            // Confs. do Cliente
            json j = json::parse(v);
            std::string s1 = j["request"].get<std::string>();
            std::string s2 = "play";
            std::string name = j["name"].get<std::string>();
            std::string s3 = "remove";
            if (s1.compare(s2) == 0) {
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
                for (int i = 0; i < personagens.size(); i++) {
                    if (name.compare(personagens[i]->getName()) == 0) {
                        personagens[i]->setLife(-1);
                        personagens[i]->setScore(0);
                        if (personagens[i]->getPower()) personagens[i]->setPower();
                    }
                }
            }
        }
    };

    auto enviarDados = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {
        boost::asio::io_service my_io_service; // Conecta com o SO

        udp::endpoint local_endpoint(udp::v4(), 9003); // endpoint: contem
                                                        // conf. da conexao (ip/port)

        udp::socket meu_socket(my_io_service,   // io service
                                local_endpoint); // endpoint

        udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar

        char v[100000];
        while(1) {
            memset(v, 0, 100000);
            meu_socket.receive_from(boost::asio::buffer(v, 100000), // Local do buffer
                            remote_endpoint);            // Confs. do Cliente
            std::cout << "Received request from " << remote_endpoint << std::endl;
            json j = json::parse(v);

            std::string name = j["name"].get<std::string>();
            bool ativo = false;
            bool dead = false;
            for (int i = 0; i < personagens.size(); i++) {
                if (name.compare(personagens[i]->getName()) == 0) {
                    ativo = true;
                    if (personagens[i]->getLife() < 0) {
                        ativo = false;
                        dead = true;
                        break;
                    }
                }
            }
            if (ativo == false) {
                json js;
                js["active"] = false;
                js["dead"] = dead;
                std::string s = js.dump();
                meu_socket.send_to(boost::asio::buffer(s), remote_endpoint);
                std::cout << "Sending request to remove Character of " << remote_endpoint << std::endl;
                continue;
            }

            std::string s1 = j["request"].get<std::string>();
            std::string s2 = "data";
            if (s1.compare(s2) == 0) {
                json j2;

                std::vector<json> characters;
                //save characters
                for (int i = 0; i < personagens.size(); i++) {
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
                
                std::string name = j["name"].get<std::string>();
                j2["active"] = true;
                j2["dead"] = false;
                std::string s = j2.dump();
                meu_socket.send_to(boost::asio::buffer(s), remote_endpoint);
                std::cout << "Sending data to render " << remote_endpoint << std::endl;
            }
        }

    };

    auto processarJogo = [this](std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<Timer> timer) {
        boost::asio::io_service my_io_service; // Conecta com o SO

        udp::endpoint local_endpoint(udp::v4(), 9004); // endpoint: contem
                                                        // conf. da conexao (ip/port)

        udp::socket meu_socket(my_io_service,   // io service
                                local_endpoint); // endpoint

        udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar


        while(1) {
            // std::cout << "personagens: " << personagens.size() << std::endl;
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