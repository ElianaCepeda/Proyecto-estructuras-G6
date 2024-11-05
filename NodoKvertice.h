#ifndef NODOKVERTICE_H
#define NODOKVERTICE_H
#include "Vertice.h"

class NodoKvertice {
    private:
        Vertice dato;
        NodoKvertice *hijoIzq;
        NodoKvertice *hijoDer;
    public:
        NodoKvertice();
        NodoKvertice(Vertice ver);
        ~NodoKvertice();
        Vertice obtenerDato();
        void fijarDato(Vertice ver);
        bool esHoja();
        NodoKvertice *obtenerHijoIzq();
        NodoKvertice *obtenerHijoDer();
        void fijarHijoIzq(NodoKvertice *izq);
        void fijarHijoDer(NodoKvertice *der);
 };

#endif //NODOKVERTICE_H