#include "../../../Include/Models/cenarioJogo/cenarioJogo.hpp"

CenarioJogo::CenarioJogo(int **mapa1)
{
    // int mapa[21][25] =
    //     {
    //         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
    //         {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 2
    //         {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 3
    //         {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 4
    //         {1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1}, // 5
    //         {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 6
    //         {1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1}, // 7
    //         {0, 0, 0, 0, 1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 1, 0, 0, 0, 0}, // 8
    //         {1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1}, // 9
    //         {3, 3, 3, 3, 3, 3, 3, 3, 1, 5, 5, 5, 5, 5, 5, 5, 1, 3, 3, 3, 3, 3, 3, 3, 3}, // 10
    //         {1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1}, // 11
    //         {0, 0, 0, 0, 1, 3, 1, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 1, 3, 1, 0, 0, 0, 0}, // 12
    //         {1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1}, // 13
    //         {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 14
    //         {1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1}, // 15
    //         {1, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 1}, // 16
    //         {1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 1}, // 17
    //         {1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1}, // 18
    //         {1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1}, // 19
    //         {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1}, // 20
    //         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // 21
    //     };
    int **mapa = mapa1;
    imagem img;
    int factor = 30;
    int w = factor * 25;
    int h = factor * 21;
    width = w;
    height = h;
    img.width = w;
    img.height = h;
    img.r = (float *)malloc(sizeof(float) * img.width * img.height);
    img.g = (float *)malloc(sizeof(float) * img.width * img.height);
    img.b = (float *)malloc(sizeof(float) * img.width * img.height);
    map = (int **)malloc(h * sizeof(int *));
    for (int i = 0; i < h; i++)
    {
        map[i] = (int *)malloc(w * sizeof(int));
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            for (int k = 0; k < factor; k++)
            {
                for (int l = 0; l < factor; l++)
                {
                    map[factor * i + k][factor * j + l] = mapa[i][j];
                }
            }
        }
    }



    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int idx = i + (j * img.width);
            if (map[j][i] == 0 || (map[j][i] >= 3 && map[j][i] <= 6))
            {
                img.r[idx] = 0;
                img.g[idx] = 0;
                img.b[idx] = 0;
            }
            else if (map[j][i] == 1)
            {
                img.r[idx] = 0;
                img.g[idx] = 0;
                img.b[idx] = 255;
            }
            else if (map[j][i] == 2)
            {
                img.r[idx] = 200;
                img.g[idx] = 200;
                img.b[idx] = 200;
            }
        }
    }

    salvar_imagem("assets/mapinha.jpg", &img);
    liberar_imagem(&img);
};

CenarioJogo::~CenarioJogo(){};

void CenarioJogo::setMap(int **mapa)
{
    map = mapa;
}
int **CenarioJogo::getMap()
{
    return map;
}
void CenarioJogo::setTextura(std::shared_ptr<Textura> textura1)
{
    textura = textura1;
}
std::shared_ptr<Textura> CenarioJogo::getTextura()
{
    return textura;
}

void CenarioJogo::setWidth(int w){
    width = w;
}
int CenarioJogo::getWidth(){
    return width;
}
void CenarioJogo::setHeight(int h){
    height = h;
}
int CenarioJogo::getHeight(){
    return height;
}