#include "NodoKvertice.h"
//constructor vacio
NodoKvertice::NodoKvertice(){
    Vertice ver;
    ver.setPosx(0);
    ver.setPosy(0);
    ver.setPosz(0);

    this->dato = ver;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}
//constructor con un vertice, de modo que se toma toda la info del vertice dado para crear el nodo
NodoKvertice::NodoKvertice(Vertice ver) {
    this->dato = ver;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

//vaciar
NodoKvertice::~NodoKvertice(){
    if (this->hijoIzq != nullptr) {
        delete this->hijoIzq;
    }
    if (this->hijoDer != nullptr) {
        delete this->hijoDer;
    }
}

//setters y getters
Vertice NodoKvertice::obtenerDato(){
    return dato;
}
void NodoKvertice::fijarDato(Vertice ver){
    dato = ver;
}
NodoKvertice *NodoKvertice::obtenerHijoIzq(){
    return hijoIzq;
}
void NodoKvertice::fijarHijoIzq(NodoKvertice *izq){
    this->hijoIzq = izq;
}


NodoKvertice *NodoKvertice::obtenerHijoDer(){
    return hijoDer;
}
void NodoKvertice::fijarHijoDer(NodoKvertice *der){
    this->hijoDer = der;
}
//metodos
//pues ajá, si es hoja true, si no false
bool NodoKvertice::esHoja() {
    return (this->hijoDer == nullptr) && (this->hijoIzq == nullptr);
}