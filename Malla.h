#ifndef MALLA_H
#define MALLA_H

#include "Cara.h"
#include "ArbolKvertices.h"
#include <string>
#include <vector>

class Malla {
private:
    std::vector<Cara> caras;
    std::string nombre;
    ArbolKvertices arbolVertices;

public:
    // Constructor
    Malla(const std::vector<Cara>& caras, const std::string& nombre);

    // Getters
    std::vector<Cara> getCaras() const;
    std::string getNombre() const;
    ArbolKvertices* getArbolVertices() const;

    // Setters
    void setCaras(const std::vector<Cara>& caras);
    void setNombre(const std::string& nombre);

    // Métodos
    int cantidadCaras() const;
    int cantidadAristas() const;
    std::vector<Vertice> listarVertices() const;
    std::vector<Arista> listarAristas() const;
    std::vector<Vertice> envolvente() const;
    void construirArbolVertices();
    std::vector<Vertice> encontrarEsquinas() const;
    std::vector<Vertice> envolventeMalla() const;
};

#endif // MALLA_H
