#include "ArbolKvertices.h"
#include <stdexcept>


ArbolKvertices::ArbolKvertices() : raiz(nullptr) {}

ArbolKvertices::ArbolKvertices(const Vertice& ver) : raiz(new NodoKvertice(ver)) {}

void ArbolKvertices::fijarRaiz(NodoKvertice* nodo) {
    raiz = nodo;
}

NodoKvertice* ArbolKvertices::obtenerRaiz() const {
    return raiz;
}

Vertice ArbolKvertices::getDatoEnRaiz() const {
    if (raiz) {
        return raiz->obtenerDato();
    }
    throw std::runtime_error("El árbol está vacío");
}

bool ArbolKvertices::esVacio() const {
    return raiz == nullptr;
}

bool ArbolKvertices::insertarVertice(const Vertice& ver) {
    if (esVacio()) {
        raiz = new NodoKvertice(ver);
        return true;
    } else {
        return insertarRecursivo(raiz, ver, 0);
    }
}

void ArbolKvertices::preOrden() {
    preOrdenRecursivo(raiz);
}

void ArbolKvertices::inOrden() {
    inOrdenRecursivo(raiz);
}

void ArbolKvertices::posOrden() {
    posOrdenRecursivo(raiz);
}

bool ArbolKvertices::insertarRecursivo(NodoKvertice* nodo, const Vertice& ver, int dim) {
    if (ver == nodo->obtenerDato()) {
        return false;
    }
    bool vaIzquierda;
    switch (dim % 3) {
        case 0:
            vaIzquierda = (ver.getPosx() < nodo->obtenerDato().getPosx());
            break;
        case 1:
            vaIzquierda = (ver.getPosy() < nodo->obtenerDato().getPosy());
            break;
        case 2:
            vaIzquierda = (ver.getPosz() < nodo->obtenerDato().getPosz());
            break;
    }
    if (vaIzquierda) {
        if (nodo->obtenerHijoIzq() == nullptr) {
            nodo->fijarHijoIzq(new NodoKvertice(ver));
            return true;
        } else {
            return insertarRecursivo(nodo->obtenerHijoIzq(), ver, dim + 1);
        }
    } else {
        if (nodo->obtenerHijoDer() == nullptr) {
            nodo->fijarHijoDer(new NodoKvertice(ver));
            return true;
        } else {
            return insertarRecursivo(nodo->obtenerHijoDer(), ver, dim + 1);
        }
    }
}

void ArbolKvertices::preOrdenRecursivo(NodoKvertice* nodo) {
    if (nodo != nullptr) {
        preOrdenRecursivo(nodo->obtenerHijoIzq());
        preOrdenRecursivo(nodo->obtenerHijoDer());
    }
}

void ArbolKvertices::inOrdenRecursivo(NodoKvertice* nodo) {
    if (nodo != nullptr) {
        inOrdenRecursivo(nodo->obtenerHijoIzq());
    }
}

void ArbolKvertices::posOrdenRecursivo(NodoKvertice* nodo) {
    if (nodo != nullptr) {
        posOrdenRecursivo(nodo->obtenerHijoIzq());
        posOrdenRecursivo(nodo->obtenerHijoDer());
    }
}