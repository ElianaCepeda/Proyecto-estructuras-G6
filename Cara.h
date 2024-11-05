#ifndef CARA_H
#define CARA_H

#include "Arista.h"
#include <vector>

class Cara {
private:
    std::vector<Arista> aristas;

public:
    // Constructor que recibe una referencia constante al vector de aristas
    Cara(const std::vector<Arista>& aristas);

    // Getters
    std::vector<Arista> getAristas() const;

    // Setters
    void setAristas(const std::vector<Arista>& aristas);

    // Métodos
    int cantidadAristas() const;
    std::vector<Vertice> listarVertices() const;
};



#endif // CARA_H
