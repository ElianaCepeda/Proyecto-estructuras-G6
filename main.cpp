#include "Sistema.h"
#include "ArbolKvertices.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cfloat>

using namespace std;

// Mapa que contiene las descripciones de los comandos
unordered_map<string, string> ayuda_comandos = {
    {"ayuda",
      "Comandos Disponibles: cargar, listado, envolvente, descargar, guardar, v_cercano, salir, v_cercanos_caja."},
    {"listado",
      "Descripción: Lista todas las mallas cargadas actualmente en el sistema.\nParámetros: No requiere."},
    {"cargar",
     "Descripción: Carga un archivo de malla en el sistema.\nParámetros: \n - nombre_archivo: El nombre del archivo a cargar."},
    {"listado",
      "Descripción: Lista todas las mallas cargadas actualmente en el sistema.\nParámetros: No requiere."},
    {"envolvente",
     "Descripción: Calcula la caja envolvente de un objeto 3D cargado en memoria.\nParámetros: \n - nombre_objeto (opcional): El nombre del objeto cuya envolvente deseas calcular."},
    {"descargar",
     "Descripción: Elimina un objeto cargado de la memoria.\nParámetros: \n - nombre_objeto: El nombre del objeto a eliminar."},
    {"guardar",
     "Descripción: Guarda un objeto cargado en un archivo.\nParámetros: \n - nombre_objeto: El nombre del objeto a guardar.\n - nombre_archivo: El nombre del archivo donde se guardará el objeto."},
    {"v_cercano",
      "Descripción: Encuentra el vértice más cercano a un punto dado.\nParámetros: \n - px, py, pz: Coordenadas del punto.\n - nombre_objeto (opcional): El nombre del objeto sobre el cual se buscará el vértice más cercano."},
    {"v_cercanos_caja",
      "Descripción: identifica los vertices del objeto nombre_objeto más cercanos a las esquinas de su caja envolvente.\nParámetros: \n - nombre_objeto: Objeto del que se quieran encontrar los vertices más cercanos"},
    {"ruta_corta",
     "Descripción: Identifica los índices de los vértices que conforman la ruta más corta entre dos vértices dados de un objeto.\nParámetros: \n - i1, i2: Índices de los vértices de origen y destino.\n - nombre_objeto: El nombre del objeto sobre el cual se calculará la ruta más corta."},
    {"salir",
      "Descripción: Termina la ejecución de la aplicación.\nParámetros: No requiere."}};

// Funciones auxiliares
bool archivoExiste(const std::string &nombre_archivo) {
  std::ifstream archivo(nombre_archivo);
  return archivo.good();
}

bool objetoCargado(std::string &nombre_objeto, std::vector<Malla> mallasActuales) {
  for (size_t i = 0; i < mallasActuales.size(); i++) {
    if (mallasActuales[i].getNombre() == nombre_objeto) {
      return true; // El objeto ya está cargado
    }
  }
  return false; // El objeto no está cargado
}

string nombreEnvolvente(const string &nombre_objeto) {
  return "env_" + nombre_objeto;
}

// Función principal
int main() {
  std::vector<Malla> mallasIniciales;
  Sistema sistema(mallasIniciales);

  cout << "Bienvenido al programa de representacion en 3D de mallas poligonales"
       << endl;
  string comando = "nada";

  while (comando != "salir") {
    cout << "\n$";
    string linea;
    getline(cin, linea);

    stringstream ss(linea);
    ss >> comando;

    if (comando == "ayuda") {
      string subcomando;
      ss >> subcomando;
      if(subcomando.empty()) {
        sistema.ayuda();

      }
      else {
        sistema.ayudaComando(subcomando);
      }
    } else if (comando == "cargar") {
      string nombre_archivo;
      ss >> nombre_archivo;

      if (nombre_archivo.empty()) {
        cout << "Error: Falta el parámetro nombre_archivo." << endl;
      } else if (!archivoExiste(nombre_archivo)) {
        cout << "El archivo " << nombre_archivo << " no existe o es ilegible."
             << endl;
      } else if (objetoCargado(nombre_archivo, mallasIniciales)) {
        cout << "El objeto ya está cargado, búscalo por su nombre" << endl;
      } else {
        sistema.cargarMalla(nombre_archivo);
        cout << "El archivo fue cargado correctamente" << endl;

        // Actualizar mallasIniciales con las mallas cargadas en el sistema
        mallasIniciales = sistema.getMallas();

        // Verificar el contenido del vector mallasIniciales
        cout << "Actualmente hay " << mallasIniciales.size()
             << " mallas cargadas." << endl;
        for (const auto &malla : mallasIniciales) {
          cout << "Malla cargada: " << malla.getNombre() << endl;
        }
      }
    } else if (comando == "listado") {
      if (mallasIniciales.empty()) {
        cout << "No hay mallas cargadas en el sistema" << endl;
      } else {
        sistema.listar();
      }
    } else if (comando == "envolvente") {
      std::string nombre_objeto;
      ss >> nombre_objeto;

      if (nombre_objeto.empty()) {
        std::vector<Vertice> envolventeGlobal = sistema.envolvente();
        if (envolventeGlobal.empty()) {
          std::cout << "No hay mallas cargadas en el sistema." << std::endl;
        } else {
          std::cout << "La caja envolvente global es: " << std::endl;
          std::cout << "Vertice minimo: (" << envolventeGlobal[0].getPosx()
                    << ", " << envolventeGlobal[0].getPosy() << ", "
                    << envolventeGlobal[0].getPosz() << ")" << std::endl;
          std::cout << "Vertice maximo: (" << envolventeGlobal[1].getPosx()
                    << ", " << envolventeGlobal[1].getPosy() << ", "
                    << envolventeGlobal[1].getPosz() << ")" << std::endl;
        }
      } else {
        std::vector<Vertice> envolventeMalla =
            sistema.envolventeMalla(nombre_objeto);
        if (envolventeMalla.empty()) {
          std::cout << "El objeto " << nombre_objeto
                    << " no ha sido cargado en memoria." << std::endl;
        } else {
          std::cout << "La caja envolvente de la malla " << nombre_objeto
                    << " es: " << std::endl;
          std::cout << "Vertice minimo: (" << envolventeMalla[0].getPosx()
                    << ", " << envolventeMalla[0].getPosy() << ", "
                    << envolventeMalla[0].getPosz() << ")" << std::endl;
          std::cout << "Vertice maximo: (" << envolventeMalla[1].getPosx()
                    << ", " << envolventeMalla[1].getPosy() << ", "
                    << envolventeMalla[1].getPosz() << ")" << std::endl;
        }
      }
    } else if (comando == "descargar") {
      string nombre_objeto;
      ss >> nombre_objeto;
      if (nombre_objeto.empty()) {
        cout << "Error: Falta el parámetro nombre_objeto." << endl;
      } else if (!objetoCargado(nombre_objeto, mallasIniciales)) {
        cout << "El objeto " << nombre_objeto
             << " no ha sido cargado en memoria." << endl;
      } else {
        sistema.eliminar(nombre_objeto);
      }
    } else if (comando == "guardar") {
      string nombre_objeto, nombre_archivo;
      ss >> nombre_objeto >> nombre_archivo;

      if (nombre_objeto.empty() || nombre_archivo.empty()) {
        cout << "Error: Faltan parámetros nombre_objeto o nombre_archivo."
             << endl;
      } else if (!objetoCargado(nombre_objeto, mallasIniciales)) {
        cout << "El objeto " << nombre_objeto
             << " no ha sido cargado en memoria." << endl;
      } else {
        Malla meshObjetivo = sistema.buscarMalla(nombre_objeto);
        bool creado = sistema.guardarMalla(nombre_objeto, nombre_archivo);
        if (creado) {
          cout << "La información del objeto " << nombre_objeto
               << " ha sido guardada exitosamente en el archivo "
               << nombre_archivo << "." << endl;
        } else {
          cout << "Error al guardar el objeto " << nombre_objeto
               << " en el archivo " << nombre_archivo << "." << endl;
        }
      }
    } else if (comando == "ruta_corta") {
      float i1, i2;
      string nombre_objeto;
      ss >> i1 >> i2 >> nombre_objeto;
      if (ss.fail()) {
        std:: cout << "Error: Faltan o son inválidos los parámetros i1, i2 o "
                "nombre_objeto";
      } else if (i1 == i2) {
        std:: cout << "Error: Los indices son iguales";
      } 
    } else if (comando == "v_cercano") {
      float px, py, pz;
      string nombre_objeto;
      ss >> px >> py >> pz;

      if (ss.fail()) {
          cout << "Error: Faltan o son inválidos los parámetros px, py, pz." << endl;
      }else{
        ss>>nombre_objeto;
        if (nombre_objeto.empty()) {
          // Caso donde no se proporciona nombre de objeto, buscamos en todas las mallas
          if (mallasIniciales.empty()) {
              cout << "Error: Ningún objeto ha sido cargado en memoria." << endl;
          } else {
              Vertice verticeCercano;
              Malla* mallaCercana = nullptr;
              float menorDistancia = FLT_MAX;
              bool encontrado = false;

              // Iterar sobre todas las mallas cargadas
              for (Malla& malla : mallasIniciales) {
                  Vertice verticeActual;
                  float distanciaActual = sistema.encontrarVerCercano(malla, px, py, pz, verticeActual);

                  if (distanciaActual < menorDistancia) {
                      menorDistancia = distanciaActual;
                      verticeCercano = verticeActual;
                      mallaCercana = &malla;  // Apuntar a la malla encontrada
                      encontrado = true;
                  }
              }

              if (encontrado && mallaCercana != nullptr) {
                  cout << "El vértice más cercano en el objeto " << mallaCercana->getNombre() << " es: ("
                       << verticeCercano.getPosx() << ", " << verticeCercano.getPosy() << ", "
                       << verticeCercano.getPosz() << ") a una distancia de " << menorDistancia << "." << endl;
              }
            
          }
      } else {
          // Caso donde se proporciona el nombre del objeto
          if (!objetoCargado(nombre_objeto, mallasIniciales)) {
              cout << "Error: El objeto " << nombre_objeto << " no ha sido cargado en memoria." << endl;
          } else {
              // Buscar en el objeto específico
              Malla mallaActual = sistema.buscarMalla(nombre_objeto);
              Vertice verticeCercano;
              float distancia = sistema.encontrarVerCercano(mallaActual, px, py, pz, verticeCercano);

              cout << "El vértice más cercano en el objeto " << nombre_objeto << " es: (" 
                   << verticeCercano.getPosx() << ", " << verticeCercano.getPosy() << ", "
                   << verticeCercano.getPosz() << ") a una distancia de " << distancia << "." << endl;
          }
        }
      }
  }else if (comando == "v_cercanos_caja") {
      string nombre_objeto;
      ss >> nombre_objeto;

      if (nombre_objeto.empty()) {
          cout << "Error: Falta el parámetro nombre_objeto." << endl;
      } else if (!objetoCargado(nombre_objeto, mallasIniciales)) {
          cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << endl;
      } else {
          // Obtener las esquinas de la caja envolvente del objeto
          std::vector<Vertice> esquinasCaja = sistema.esquinas(nombre_objeto);
          if (esquinasCaja.size() != 8) {
              cout << "Error: No se pudo calcular la caja envolvente correctamente." << endl;
          } else {
              cout << "Los vértices del objeto " << nombre_objeto << " más cercanos a las esquinas de su caja envolvente son:" << endl;
              cout << "Esquina\t\t\tVertice\t\t\tDistancia" << endl;

              // Iterar sobre las 8 esquinas de la caja envolvente
              for (int i = 0; i < 8; ++i) {
                  const Vertice& esquina = esquinasCaja[i];
                  Vertice verticeCercano;
                  float distancia = sistema.encontrarVerCercano(sistema.buscarMalla(nombre_objeto),esquina.getPosx(), esquina.getPosy(), esquina.getPosz(), verticeCercano);
                  // Imprimir los resultados para cada esquina
                  cout << i + 1 << " (" << esquina.getPosx() << ", " << esquina.getPosy() << ", " << esquina.getPosz() << ")"
                       << "\t" << verticeCercano.getPosx() << ", " << verticeCercano.getPosy() << ", " << verticeCercano.getPosz()
                       << "\t" << distancia << endl;
              }
          }
      }
    }else if (comando == "salir") {
      return 0;
    } else {
      cout << "Comando no reconocido" << endl;
    }
  }

  return 0;
}
