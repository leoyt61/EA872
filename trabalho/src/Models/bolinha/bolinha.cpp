#include "../../../Include/Models/bolinha/bolinha.hpp"

Bolinha::Bolinha(int** ball, bool power1, int size1, char const* path)
{
    power = power1;
    size = size1;
    score = 10;
    display = true;
    oldDisplay = true;
    if (power1 == true) score = 50;


    // int mapa[1][1] = {{6}};
    int **mapa = ball;
    imagem img;
    int factor = 30;
    int width = factor * 1;
    int height = factor * 1;
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

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 1; j++)
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

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int idx = i + (j * img.width);
            if (power1 == false && i > 11 && i < 18 && j > 11 && j < 18) {
                img.r[idx] = 255;
                img.g[idx] = 255;
                img.b[idx] = 0;
            }
            else if (power1 == true && i > 5 && i < 24 && j > 5 && j < 24) {
                if (i > 7 && i < 22 && j > 7 && j < 22) {
                    img.r[idx] = 255;
                    img.g[idx] = 255;
                    img.b[idx] = 0;
                }
                else {
                    img.r[idx] = 255;
                    img.g[idx] = 255;
                    img.b[idx] = 255;
                }
            }
            else {
                img.r[idx] = 0;
                img.g[idx] = 0;
                img.b[idx] = 0;
            }
        }
    }

    salvar_imagem(path, &img);
    liberar_imagem(&img);
};

Bolinha::~Bolinha(){};

void Bolinha::setTextura(std::shared_ptr<Textura> textura1)
{
    textura = textura1;
};
std::shared_ptr<Textura> Bolinha::getTextura()
{
    return textura;
};
void Bolinha::setPower(bool power1)
{
    power = power1;
};
bool Bolinha::getPower()
{
    return power;
};
void Bolinha::setDisplay(bool display1)
{
    display = display1;
};
bool Bolinha::getDisplay()
{
    return display;
};
void Bolinha::setOldDisplay(bool oldDisplay1){
    oldDisplay = oldDisplay1;
};
bool Bolinha::getOldDisplay(){
    return oldDisplay;
};
void Bolinha::setSize(int size1)
{
    size = size1;
};
int Bolinha::getSize()
{
    return size;
};
unsigned long int Bolinha::getScore(){
    return score;
};

void Bolinha::setScore(unsigned long int score1) {
    score = score1;
}