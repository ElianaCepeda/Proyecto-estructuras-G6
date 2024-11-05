#include "Malla.h"
#include "algorithm"

// Constructor con lista de inicialización
Malla:: Malla (const std::vector<Cara>& caras, const std::string& nombre)
    : caras(caras), nombre(nombre) {construirArbolVertices();}

// Getters
std::vector<Cara> Malla::getCaras() const {
    return caras;
}

std::string Malla::getNombre() const {
    return nombre;
}

ArbolKvertices* Malla::getArbolVertices() const {
    return const_cast<ArbolKvertices*>(&arbolVertices); 
}

// Setters
void Malla::setCaras(const std::vector<Cara>& nuevasCaras) {
    caras = nuevasCaras;
}

void Malla::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

// Devuelve la cantidad de caras
int Malla::cantidadCaras() const {
    return caras.size();
}

// Devuelve la cantidad de aristas
int Malla::cantidadAristas() const {
    int cantidad = 0;
    for (std::size_t i = 0; i < caras.size(); ++i) {
        cantidad += caras[i].cantidadAristas();
    }
    return cantidad;
}

// Listar todas las aristas únicas de la malla
std::vector<Arista> Malla::listarAristas() const {
    std::vector<Arista> aristasUnicas;

    for (std::size_t i = 0; i < caras.size(); ++i) {
        std::vector<Arista> aristasCara = caras[i].getAristas();
        for (std::size_t j = 0; j < aristasCara.size(); ++j) {
            bool aristaEncontrada = false;
            for (std::size_t k = 0; k < aristasUnicas.size(); ++k) {
                if ((aristasUnicas[k].getV1().getPosx() == aristasCara[j].getV1().getPosx() &&
                     aristasUnicas[k].getV1().getPosy() == aristasCara[j].getV1().getPosy() &&
                     aristasUnicas[k].getV1().getPosz() == aristasCara[j].getV1().getPosz() &&
                     aristasUnicas[k].getV2().getPosx() == aristasCara[j].getV2().getPosx() &&
                     aristasUnicas[k].getV2().getPosy() == aristasCara[j].getV2().getPosy() &&
                     aristasUnicas[k].getV2().getPosz() == aristasCara[j].getV2().getPosz()) ||
                    (aristasUnicas[k].getV1().getPosx() == aristasCara[j].getV2().getPosx() &&
                     aristasUnicas[k].getV1().getPosy() == aristasCara[j].getV2().getPosy() &&
                     aristasUnicas[k].getV1().getPosz() == aristasCara[j].getV2().getPosz() &&
                     aristasUnicas[k].getV2().getPosx() == aristasCara[j].getV1().getPosx() &&
                     aristasUnicas[k].getV2().getPosy() == aristasCara[j].getV1().getPosy() &&
                     aristasUnicas[k].getV2().getPosz() == aristasCara[j].getV1().getPosz())) {
                    aristaEncontrada = true;
                    break;
                }
            }
            if (!aristaEncontrada) {
                aristasUnicas.push_back(aristasCara[j]);
            }
        }
    }

    return aristasUnicas;
}

// Listar todos los vértices únicos de la malla
std::vector<Vertice> Malla::listarVertices() const {
    std::vector<Vertice> verticesUnicos;

    for (std::size_t i = 0; i < caras.size(); ++i) {
        std::vector<Vertice> verticesCara = caras[i].listarVertices();
        verticesUnicos.insert(verticesUnicos.end(), verticesCara.begin(), verticesCara.end());
    }

    // Eliminar duplicados en el vector de vértices
    std::sort(verticesUnicos.begin(), verticesUnicos.end(), [](const Vertice& a, const Vertice& b) {
        return a.getPosx() < b.getPosx() ||
               (a.getPosx() == b.getPosx() && a.getPosy() < b.getPosy()) ||
               (a.getPosx() == b.getPosx() && a.getPosy() == b.getPosy() && a.getPosz() < b.getPosz());
    });

    verticesUnicos.erase(std::unique(verticesUnicos.begin(), verticesUnicos.end()), verticesUnicos.end());

    return verticesUnicos;
}

// Calcular los vértices de la caja envolvente de la malla
std::vector<Vertice> Malla::envolventeMalla() const {
    std::vector<Vertice> vertices = listarVertices();
    if (vertices.empty()) {
        return std::vector<Vertice>();
    }

    float xmin = vertices[0].getPosx();
    float ymin = vertices[0].getPosy();
    float zmin = vertices[0].getPosz();
    float xmax = xmin;
    float ymax = ymin;
    float zmax = zmin;

    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getPosx() < xmin) xmin = vertices[i].getPosx();
        if (vertices[i].getPosy() < ymin) ymin = vertices[i].getPosy();
        if (vertices[i].getPosz() < zmin) zmin = vertices[i].getPosz();
        if (vertices[i].getPosx() > xmax) xmax = vertices[i].getPosx();
        if (vertices[i].getPosy() > ymax) ymax = vertices[i].getPosy();
        if (vertices[i].getPosz() > zmax) zmax = vertices[i].getPosz();
    }

    std::vector<Vertice> resultado;
    Vertice verticeMinimo(xmin, ymin, zmin);
    Vertice verticeMaximo(xmax, ymax, zmax);
    resultado.push_back(verticeMinimo);
    resultado.push_back(verticeMaximo);
    return resultado;
}
std::vector<Vertice> Malla::envolvente() const {
    std::vector<Vertice> vertices = listarVertices();
    if (vertices.empty()) {
        return std::vector<Vertice>();
    }

    float xmin = vertices[0].getPosx();
    float ymin = vertices[0].getPosy();
    float zmin = vertices[0].getPosz();
    float xmax = xmin;
    float ymax = ymin;
    float zmax = zmin;

    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getPosx() < xmin) xmin = vertices[i].getPosx();
        if (vertices[i].getPosy() < ymin) ymin = vertices[i].getPosy();
        if (vertices[i].getPosz() < zmin) zmin = vertices[i].getPosz();
        if (vertices[i].getPosx() > xmax) xmax = vertices[i].getPosx();
        if (vertices[i].getPosy() > ymax) ymax = vertices[i].getPosy();
        if (vertices[i].getPosz() > zmax) zmax = vertices[i].getPosz();
    }

    std::vector<Vertice> resultado;
    Vertice verticeMinimo(xmin, ymin, zmin);
    Vertice verticeMaximo(xmax, ymax, zmax);
    resultado.push_back(verticeMinimo);
    resultado.push_back(verticeMaximo);
    return resultado;
}
void Malla::construirArbolVertices() {
    std::vector<Vertice> vertices = listarVertices();  
    for (const Vertice& v : vertices) {
        arbolVertices.insertarVertice(v);
    }  
}
std::vector <Vertice> Malla::encontrarEsquinas()const{
    std::vector<Vertice> vertices = listarVertices();
    if (vertices.empty()) {
        return std::vector<Vertice>();
    }

    // Inicializamos los valores mínimo y máximo con el primer vértice
    float xmin = vertices[0].getPosx();
    float ymin = vertices[0].getPosy();
    float zmin = vertices[0].getPosz();
    float xmax = xmin;
    float ymax = ymin;
    float zmax = zmin;

    // Iteramos sobre los vértices para encontrar los valores mínimos y máximos
    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getPosx() < xmin) xmin = vertices[i].getPosx();
        if (vertices[i].getPosy() < ymin) ymin = vertices[i].getPosy();
        if (vertices[i].getPosz() < zmin) zmin = vertices[i].getPosz();
        if (vertices[i].getPosx() > xmax) xmax = vertices[i].getPosx();
        if (vertices[i].getPosy() > ymax) ymax = vertices[i].getPosy();
        if (vertices[i].getPosz() > zmax) zmax = vertices[i].getPosz();
    }

    // Creamos las 8 esquinas de la caja envolvente utilizando combinaciones de xmin, xmax, ymin, ymax, zmin, zmax
    std::vector<Vertice> resultado;
    resultado.push_back(Vertice(xmin, ymin, zmin)); // Esquina 1
    resultado.push_back(Vertice(xmax, ymin, zmin)); // Esquina 2
    resultado.push_back(Vertice(xmin, ymax, zmin)); // Esquina 3
    resultado.push_back(Vertice(xmax, ymax, zmin)); // Esquina 4
    resultado.push_back(Vertice(xmin, ymin, zmax)); // Esquina 5
    resultado.push_back(Vertice(xmax, ymin, zmax)); // Esquina 6
    resultado.push_back(Vertice(xmin, ymax, zmax)); // Esquina 7
    resultado.push_back(Vertice(xmax, ymax, zmax)); // Esquina 8

    return resultado;
}

