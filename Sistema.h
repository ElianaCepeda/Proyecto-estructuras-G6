#ifndef SISTEMA_H
#define SISTEMA_H

#include "Malla.h"
#include <string>
#include <vector>

class Sistema {
private:
  std::vector<Malla> mallas;

public:
  // Constructor que recibe un vector de mallas
  Sistema(const std::vector<Malla> &mallas);

  // Getters
  std::vector<Malla> getMallas() const;

  // Setters
  void setMallas(const std::vector<Malla> &mallas);

  // Métodos
  Malla buscarMalla(const std::string &nombre) const;
  void cargarMalla(const std::string &ruta);
  void listar() const;
  std::vector<Vertice> envolventeMalla(const std::string &nombre) const;
  std::vector<Vertice> envolvente() const;
  void eliminar(const std::string &nombre);
  bool guardarMalla(const std::string &nombre, const std::string &ruta) const;
  float encontrarVerCercano(Malla malla, float px, float py, float pz, Vertice &ver);
  void buscarRecursivamente (NodoKvertice* nodo, Vertice punto, Vertice &ver, float &menor);
  std::vector<Vertice> esquinas(const std::string& nombre) const;

  void ayuda();
  void ayudaComando(std::string comando);
};

#endif // SISTEMA_H
