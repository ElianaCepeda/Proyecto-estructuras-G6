#ifndef ARBOLKVERTICES_H
#define ARBOLKVERTICES_H

#include "NodoKvertice.h"
#include "Vertice.h"
#include <string>

class ArbolKvertices {
private:
    NodoKvertice* raiz;

    bool insertarRecursivo(NodoKvertice* nodo, const Vertice& ver, int dim);
    void preOrdenRecursivo(NodoKvertice* nodo);
    void inOrdenRecursivo(NodoKvertice* nodo);
    void posOrdenRecursivo(NodoKvertice* nodo);

public:
    ArbolKvertices();
    ArbolKvertices(const Vertice& ver);

    void fijarRaiz(NodoKvertice* nodo);
    NodoKvertice* obtenerRaiz() const;
    Vertice getDatoEnRaiz() const;
    bool esVacio() const;
    bool insertarVertice(const Vertice& ver);
    void v_cercano(float px, float py, float pz, std::string nombre_objeto);
    void v_cercano(float px, float py, float pz);
    void v_cercanos_caja(std::string nombre_objeto);
    void preOrden();
    void inOrden();
    void posOrden();
};
#endif //ARBOLKVERTICES_H