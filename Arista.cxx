#include "Arista.h"
#include <iostream>

// Getters
Vertice Arista::getV1() const {
    return v1;
}

Vertice Arista::getV2() const {
    return v2;
}

// Setters
void Arista::setV1(const Vertice& nuevoV1) {
    v1 = nuevoV1;
}

void Arista::setV2(const Vertice& nuevoV2) {
    v2 = nuevoV2;
}
