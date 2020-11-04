#include "../../../Include/Models/amortecedor/amortecedor.hpp"
#include <iostream>


Amortecedor::Amortecedor(float coef1) {
    coef = coef1;
};

Amortecedor::~Amortecedor(){};

void Amortecedor::setCoef(float coef1){
    coef = coef1;
};

float Amortecedor::getCoef(){
    return coef;
};


