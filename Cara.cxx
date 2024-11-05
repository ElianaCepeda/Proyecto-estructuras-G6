#include "Cara.h"
#include <unordered_set>

// Constructor con lista de inicialización
Cara::Cara(const std::vector<Arista>& aristas) : aristas(aristas) {}

// Getters
std::vector<Arista> Cara::getAristas() const {
    return aristas;
}

// Setters
void Cara::setAristas(const std::vector<Arista>& nuevasAristas) {
    aristas = nuevasAristas;
}

// Devuelve la cantidad de aristas
int Cara::cantidadAristas() const {
    return aristas.size();
}

// Listar todos los vértices únicos de la cara
std::vector<Vertice> Cara::listarVertices() const {
    std::vector<Vertice> vertices;

    for (std::size_t i = 0; i < aristas.size(); ++i) {
        Vertice verticeInicial = aristas[i].getV1();
        Vertice verticeFinal = aristas[i].getV2();

        // Verificar si el vértice inicial ya está en la lista
        bool inicialEncontrado = false;
        for (std::size_t j = 0; j < vertices.size(); ++j) {
            if (vertices[j].getPosx() == verticeInicial.getPosx() &&
                vertices[j].getPosy() == verticeInicial.getPosy() &&
                vertices[j].getPosz() == verticeInicial.getPosz()) {
                inicialEncontrado = true;
                break;
            }
        }
        if (!inicialEncontrado) {
            vertices.push_back(verticeInicial);
        }

        // Verificar si el vértice final ya está en la lista
        bool finalEncontrado = false;
        for (std::size_t j = 0; j < vertices.size(); ++j) {
            if (vertices[j].getPosx() == verticeFinal.getPosx() &&
                vertices[j].getPosy() == verticeFinal.getPosy() &&
                vertices[j].getPosz() == verticeFinal.getPosz()) {
                finalEncontrado = true;
                break;
            }
        }
        if (!finalEncontrado) {
            vertices.push_back(verticeFinal);
        }
    }

    return vertices;
}
