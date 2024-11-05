#include "Vertice.h"
#include <cmath> 

// Constructor con lista de inicialización
Vertice::Vertice(float x, float y, float z) : posx(x), posy(y), posz(z) {}

// Constructor por defecto
Vertice::Vertice() : posx(0), posy(0), posz(0) {}

// Getters
float Vertice::getPosx() const {
    return posx;
}

float Vertice::getPosy() const {
    return posy;
}

float Vertice::getPosz() const {
    return posz;
}

// Setters
void Vertice::setPosx(float nuevaPosx) {
    posx = nuevaPosx;
}

void Vertice::setPosy(float nuevaPosy) {
    posy = nuevaPosy;
}

void Vertice::setPosz(float nuevaPosz) {
    posz = nuevaPosz;
}

// Sobrecarga del operador ==
bool Vertice::operator==(const Vertice& other) const {
    return (this->posx == other.posx && this->posy == other.posy && this->posz == other.posz);
}

// Función para calcular la distancia euclidiana entre dos vértices
float Vertice::distanciaEuclidiana(const Vertice& verti) const {
    return sqrt(pow(posx - verti.getPosx(), 2) + pow(posy - verti.getPosy(), 2) + pow(posz - verti.getPosz(), 2));
}
