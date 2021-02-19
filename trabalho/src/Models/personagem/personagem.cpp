#include "../../../Include/Models/personagem/personagem.hpp"

Personagem::Personagem(int** pac, bool power1, bool ghost1, int width1, int height1, char const* path, std::string name1)
{
    power = power1;
    ghost = ghost1;
    height = height1;
    width = width1;
    life = 2;
    score = 0;
    name = name1;
    x = 0;
    y = 0;
    playing = false;
    if (ghost1 == true) life = 0;
    std::shared_ptr<Timer> powerTimer1 (new Timer());
    powerTimer = powerTimer1;
    free = false;

    // int mapa[1][1] = {{6}};
    int **mapa = pac;
    imagem img;
    int factor = 3;
    int width = factor * 10;
    int height = factor * 10;
    img.width = width;
    img.height = height;
    img.r = (float*)malloc(sizeof(float) * img.width * img.height);
    img.g = (float*)malloc(sizeof(float) * img.width * img.height);
    img.b = (float*)malloc(sizeof(float) * img.width * img.height);
    int **mapa2 = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++)
    {
        mapa2[i] = (int *)malloc(width * sizeof(int));
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < factor; k++)
            {
                for (int l = 0; l < factor; l++)
                {
                    mapa2[factor * i + k][factor * j + l] = mapa[i][j];
                }
            }
        }
    }

    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int idx = i + (j * img.width);
            if (mapa2[i][j] == 0) {
                img.r[idx] = NULL;
                img.g[idx] = NULL;
                img.b[idx] = NULL;
            }
            else {
                img.r[idx] = r;
                img.g[idx] = g;
                img.b[idx] = b;
            }
        }
    }

    salvar_imagem(path, &img);
    liberar_imagem(&img);
};

Personagem::~Personagem(){};

void Personagem::setTextura(std::shared_ptr<Textura> textura1)
{
    textura = textura1;
};
std::shared_ptr<Textura> Personagem::getTextura()
{
    return textura;
};
void Personagem::setPower()
{
    power = !power;
};
bool Personagem::getPower()
{
    return power;
};
bool Personagem::getGhost()
{
    return ghost;
};
void Personagem::setHeight(int height1)
{
    height = height1;
};
int Personagem::getHeight()
{
    return height;
};
void Personagem::setWidth(int width1)
{
    width = width1;
};
int Personagem::getWidth()
{
    return width;
};
void Personagem::setLife(int life1){
    life = life1;
};
int Personagem::getLife(){
    return life;
};
void Personagem::setScore(unsigned long int score1){
    score = score1;
};
unsigned long int Personagem::getScore(){
    return score;
};
void Personagem::setName(std::string name1) {
    name = name1;
};
std::string Personagem::getName() {
    return name;
};
std::shared_ptr<Timer> Personagem::getPowerTimer() {
    return powerTimer;
};
void Personagem::setX(int x1) {
    x = x1;
}
int Personagem::getX() {
    return x;
}
void Personagem::setY(int y1) {
    y = y1;
}
int Personagem::getY() {
    return y;
}
void Personagem::setPlaying(bool playing1) {
    playing = playing1;
}
bool Personagem::getPlaying() {
    return playing;
}
void Personagem::setIp(udp::endpoint remote_endpoint1) {
    remote_endpoint = remote_endpoint1;
}
udp::endpoint Personagem::getIp() {
    return remote_endpoint;
}
void Personagem::setFree(bool free1) {
    free = free1;
}
bool Personagem::getFree() {
    return free;
}