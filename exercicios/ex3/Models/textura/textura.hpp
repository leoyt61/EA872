#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Textura {
    private:
        SDL_Texture *texture;
        SDL_Rect target;
    public:
        Textura(SDL_Renderer* renderer, char const *img, int x, int y);
        ~Textura();
        void setTextura(SDL_Renderer* renderer, char * img);
        SDL_Texture* getTextura();
        void setTarget(int x, int y);
        SDL_Rect getTarget();
        SDL_Rect * getTargetAdress();
};