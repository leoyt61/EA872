#include "massa.h"
#include <iostream>


Massa::Massa(float m1) {
    m = m1;
};

Massa::~Massa(){};

void Massa::setM(float m1){
    m = m1;
};

float Massa::getM(){
    return m;
};

