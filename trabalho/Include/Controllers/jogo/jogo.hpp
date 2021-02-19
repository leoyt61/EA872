#include "../../Models/teclado/teclado.hpp"
#include "../../Models/cenarioJogo/cenarioJogo.hpp"
#include "../../Models/personagem/personagem.hpp"
#include "../../Models/bolinha/bolinha.hpp"
#include "../../Views/view.hpp"
#include "../timer/timer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "./json.hpp"
#include <memory>
#include <cstdlib>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <math.h>
#include <thread>
using nlohmann::json;
using boost::asio::ip::udp;

class Jogo{

    public:
        Jogo();
        ~Jogo();

        int setSDLInit();
        void setBallsPositions(std::shared_ptr<CenarioJogo> cenarioJogo, std::vector<std::shared_ptr<Bolinha>> &bolinhas);
        void setInitialPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo);
        int setCharacterPosition(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo, int x, int y, int oldX, int oldY);
        void characterControl(std::shared_ptr<Personagem> personagem, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, int vertical, int horizontal, std::shared_ptr<Timer> timer);
        void allCharactersControl(std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Timer> timer);
        int localCharacterControl(std::shared_ptr<Personagem> personagem, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Teclado> teclado, std::shared_ptr<int> x, std::shared_ptr<int> y, std::shared_ptr<int> cont, std::shared_ptr<View> view, std::shared_ptr<Timer> timer, std::shared_ptr<Timer> powerTimer);
        void localNpcControl(std::shared_ptr<Personagem> personagem, std::shared_ptr<CenarioJogo> cenarioJogo, int *x, int *y, int i);
        void carregarJogo(std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<Personagem>> &inimigos, std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<int> cont);
        void criarCenario(std::vector<std::shared_ptr<CenarioJogo>> &cenarioJogo, std::shared_ptr<View> view);
        void criarBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::shared_ptr<View> view);
        void criarInimigos(std::vector<std::shared_ptr<Personagem>> &inimigos, int quantidade, std::shared_ptr<View> view);
        std::shared_ptr<Personagem> criarPersonagem(std::vector<std::shared_ptr<Personagem>> &personagens, std::shared_ptr<View> view, std::string name);
        void iniciarJogo(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado);
        void jogarSingle(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado, std::vector<std::shared_ptr<Bolinha>> &bolinhas, std::vector<std::shared_ptr<Personagem>> &inimigos, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<Personagem> personagem, std::shared_ptr<int> x, std::shared_ptr<int> y, std::shared_ptr<int> cont, int * ix, int * iy);
        void darPoderParaBolinha(std::shared_ptr<Bolinha> bolinha, std::shared_ptr<CenarioJogo> cenarioJogo, std::shared_ptr<View> view, std::shared_ptr<int> cont);
        bool aindaTemBolinhas(std::vector<std::shared_ptr<Bolinha>> &bolinhas);
        void conectarServidor(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado);
        bool jogarMulti(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado, std::string name);
        void fimDeJogo(std::shared_ptr<View> view, std::shared_ptr<Textura> tela);
        void iniciarServidor(std::shared_ptr<View> view, std::shared_ptr<Teclado> teclado);
};