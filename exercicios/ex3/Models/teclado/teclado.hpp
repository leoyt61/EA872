#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Teclado {
    private:
        const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado;
    public:
        Teclado();
        ~Teclado();
        const Uint8* getState();
        void updateState();
};