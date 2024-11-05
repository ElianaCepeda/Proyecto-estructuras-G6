#ifndef ARISTA_H
#define ARISTA_H

#include "Vertice.h"

class Arista {
private:  
    Vertice v1;
    Vertice v2;

public:
    // Constructor que toma referencias constantes para evitar copias innecesarias
    Arista(const Vertice& n_v1, const Vertice& n_v2): v1(n_v1), v2(n_v2){};

    // Getters
    Vertice getV1() const;
    Vertice getV2() const;

    // Setters
    void setV1(const Vertice& nuevoV1);
    void setV2(const Vertice& nuevoV2);
};


#endif // ARISTA_H
