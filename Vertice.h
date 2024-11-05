#ifndef VERTICE_H
#define VERTICE_H

class Vertice {
private:
  float posx;
  float posy;
  float posz;

public:
  Vertice(float x, float y, float z);
  Vertice();

  // Getters
  float getPosx() const;
  float getPosy() const;
  float getPosz() const;

  // Setters
  void setPosx(float nuevaPosx);
  void setPosy(float nuevaPosy);
  void setPosz(float nuevaPosz);
  // Sobrecarga del operador ==
  bool operator==(const Vertice &otro) const;
  // para la distancia euclidiana
  float distanciaEuclidiana(const Vertice& verti) const; 

};



#endif // VERTICE_H
