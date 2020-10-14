#include "../../Include/Models/mola/mola.hpp"
#include <iostream>


Mola::Mola(float coef1) {
    coef = coef1;
};

Mola::~Mola(){};

void Mola::setCoef(float coef1){
    coef = coef1;
};

float Mola::getCoef(){
    return coef;
};


