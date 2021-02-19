#include <iostream>
#include <memory>

class Coord {
    private:
        int x;
        int y;
    public:
        Coord(int x, int y);
        ~Coord();
};

class Cube {
    private:
        int x, y, z;
    public:
        Cube(int x, int y, int z);
        ~Cube();
        void cubePrintVolume();
};

Coord::Coord(int x1, int y1) {
    x = x1;
    y = y1;
}

Coord::~Coord(){}

Cube::Cube(int x1, int y1, int z1) {
    x = x1;
    y = y1;
    z = z1;
}

Cube::~Cube(){}

void Cube::cubePrintVolume() {
    std::cout << x * y * z << std::endl;
}


int main() {
    std::unique_ptr<Coord> c1 (new Coord(50, 10));
    std::unique_ptr<Cube> c2 (new Cube(10, 20, 30));
    c2->cubePrintVolume();
    
    return 0;
}
