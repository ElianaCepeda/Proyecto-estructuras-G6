    #include "Sistema.h"
    #include <fstream>
    #include <iostream>
    #include <map>
    #include <vector>
    #include <sstream>
    #include <limits>
    #include <string.h>

    // Constructor con lista de inicialización
    Sistema::Sistema(const std::vector<Malla>& mallas) : mallas(mallas) {}

    // Getters
    std::vector<Malla> Sistema::getMallas() const {
        return mallas;
    }

    // Setters
    void Sistema::setMallas(const std::vector<Malla>& nuevasMallas) {
        mallas = nuevasMallas;
    }

    // Buscar una malla por nombre
    Malla Sistema::buscarMalla(const std::string& nombre) const {
        for (std::size_t i = 0; i < mallas.size(); ++i) {
            if (mallas[i].getNombre() == nombre) {
                return mallas[i];
            }
        }
        std::cerr << "Error: Malla con nombre " << nombre << " no encontrada." << std::endl;
        return Malla(std::vector<Cara>(), ""); // Devuelve una malla vacía si no se encuentra
    }

    // Cargar una malla desde un archivo
    void Sistema::cargarMalla(const std::string& ruta) {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            std::cerr << "Error: El archivo " << ruta << " no existe o es ilegible." << std::endl;
            return;
        }

        std::string nombreMalla;
        int cantidadVertices;
        std::vector<Vertice> vertices;
        std::vector<Cara> caras;

        archivo >> nombreMalla >> cantidadVertices;

        for (int i = 0; i < cantidadVertices; ++i) {
            float posx, posy, posz;
            archivo >> posx >> posy >> posz;
            Vertice vertice(posx, posy, posz);
            vertices.push_back(vertice);
        }

        int cantidadCaras;
        while (archivo >> cantidadCaras && cantidadCaras != -1) {
            std::vector<Vertice> caraVertices;
            std::vector<Arista> aristas;
            for (int i = 0; i < cantidadCaras; ++i) {
                int indiceVertice;
                archivo >> indiceVertice;
                caraVertices.push_back(vertices[indiceVertice]);
            }
            for (int i = 0; i < cantidadCaras; ++i) {
                Arista arista(caraVertices[i], caraVertices[(i + 1) % cantidadCaras]);
                aristas.push_back(arista);
            }
            Cara cara(aristas);
            caras.push_back(cara);
        }

        Malla nuevaMalla(caras, nombreMalla);
        mallas.push_back(nuevaMalla);
        std::cout << "Malla " << nombreMalla << " cargada correctamente desde " << ruta << std::endl;
    }

    // Listar todas las mallas cargadas
    void Sistema::listar() const {
        if (mallas.empty()) {
            std::cout << "No hay mallas cargadas en el sistema." << std::endl;
            return;
        }

        for (std::size_t i = 0; i < mallas.size(); ++i) {
            const Malla& malla = mallas[i];
            std::cout << "Malla: " << malla.getNombre() << "\n";
            std::cout << "Vertices: " << malla.listarVertices().size() << "\n";
            std::cout << "Aristas: " << malla.cantidadAristas() << "\n";
            std::cout << "Caras: " << malla.cantidadCaras() << "\n";
            std::cout << "--------------------------" << std::endl;
        }
    }

    // Calcular la envolvente global de todas las mallas
    std::vector<Vertice> Sistema::envolvente() const {
        // Si no hay mallas cargadas, devuelve un vector vacío
        if (mallas.empty()) return std::vector<Vertice>();
        //Establece como caso de comparación el primer elemento del vector de mallas
        Vertice Verticeminimo = mallas[0].envolvente()[0];
        Vertice Verticemaximo = mallas[0].envolvente()[1];
        //Recorre el vector de mallas, compara los vértices de cada malla con los vértices minimo y maximo
        for (std::size_t i = 1; i < mallas.size(); ++i) {
            std::vector<Vertice> minMax = mallas[i].envolvente();
            const Vertice& minimo = minMax[0];
            const Vertice& maximo = minMax[1];

            if (minimo.getPosx() <  Verticeminimo.getPosx()) Verticeminimo.setPosx(minimo.getPosx());
            if (minimo.getPosy() < Verticeminimo.getPosy()) Verticeminimo.setPosy(minimo.getPosy());
            if (minimo.getPosz() < Verticeminimo.getPosz()) Verticeminimo.setPosz(minimo.getPosz());

            if (maximo.getPosx() > Verticemaximo.getPosx()) Verticemaximo.setPosx(maximo.getPosx());
            if (maximo.getPosy() > Verticemaximo.getPosy()) Verticemaximo.setPosy(maximo.getPosy());
            if (maximo.getPosz() > Verticemaximo.getPosz()) Verticemaximo.setPosz(maximo.getPosz());
        }

        std::vector<Vertice> resultado;
        resultado.push_back(Verticemaximo);
        resultado.push_back(Verticeminimo);
        return resultado;
    }

    // Calcular la envolvente de una malla específica
    std::vector<Vertice> Sistema::envolventeMalla(const std::string& nombre) const {
        //Busca la malla por nombre
        for (std::size_t i = 0; i < mallas.size(); ++i) {
            if (mallas[i].getNombre() == nombre) {
                return mallas[i].envolventeMalla();
            }
        }
        //Si no se encuentra la malla devuelve un vector vacío
        std::cerr << "Error: Malla con nombre " << nombre << " no encontrada." << std::endl;
        return std::vector<Vertice>();
    }

    // Eliminar una malla por nombre
    void Sistema::eliminar(const std::string& nombre) {
        for (std::size_t i = 0; i < mallas.size(); ++i) {
            if (mallas[i].getNombre() == nombre) {
                mallas.erase(mallas.begin() + i);
                std::cout << "Malla " << nombre << " eliminada correctamente." << std::endl;
                return;
            }
        }
        std::cerr << "Error: Malla con nombre " << nombre << " no encontrada." << std::endl;
    }

    // Guardar una malla en un archivo
    bool Sistema::guardarMalla(const std::string& nombreMalla, const std::string& ruta) const {
        std::ofstream MeshArch(ruta);

        if (MeshArch.is_open()) {
            // Guardar nombre de la malla
            const Malla& meshOb = buscarMalla(nombreMalla);
            MeshArch << meshOb.getNombre() << "\n";

            // Guardar cantidad de vertices totales en el mesh
            std::vector<Vertice> ListVert = meshOb.listarVertices();
            int vertcant = ListVert.size();
            MeshArch << vertcant << "\n";

            // Guardar cada vertice
            std::map<int, Vertice> vertMap; // Mapa en donde se define el orden de los vertices para listarlos por cara
            for (int i = 0; i < vertcant; i++) {
                vertMap[i] = ListVert[i];
                MeshArch << ListVert[i].getPosx() << " " << ListVert[i].getPosy() << " " << ListVert[i].getPosz() << "\n";
            }

            // Guardar caras
            std::vector<Cara> ListCaras = meshOb.getCaras();

            for (std::size_t i = 0; i < ListCaras.size(); i++) { // i recorre la lista de caras
                // Guardar cuantos vertices tiene la cara
                std::vector<Vertice> ListVert = ListCaras[i].listarVertices();
                int vertcant = ListVert.size();
                MeshArch << vertcant;

                // Guardar cada indice de los vertices de la cara
                std::map<int, Vertice>::iterator it = vertMap.begin(); // Iterador para recorrer el mapa
                while (it != vertMap.end()) {
                    for (std::size_t j = 0; j < ListVert.size(); j++) { // j recorre la lista de vertices de la cara
                        if (ListVert[j].getPosx() == it->second.getPosx() &&
                            ListVert[j].getPosy() == it->second.getPosy() &&
                            ListVert[j].getPosz() == it->second.getPosz()) {
                            // Si el vertice de la cara es igual al vertice del mapa, se guarda su indice
                            MeshArch << " " << it->first;
                            break;
                        }
                    }
                    ++it;
                }
            }
            MeshArch << -1 << std::endl; // menos uno porque ya acabo
            MeshArch.close();
            return true;
        } else {
            return false;
        }
    }
float Sistema:: encontrarVerCercano(Malla malla, float px, float py, float pz, Vertice &ver){
    ArbolKvertices* arbol = malla.getArbolVertices();
    if(arbol!=nullptr){
        float menor = std::numeric_limits<float>::max();
        Vertice punto(px, py, pz);
        buscarRecursivamente(arbol->obtenerRaiz(), punto, ver, menor);
        return menor;
    }
    return -1;
}
void Sistema::buscarRecursivamente (NodoKvertice* nodo, Vertice punto, Vertice &ver, float &menor){
    if(nodo == nullptr) return;
    Vertice actual = nodo-> obtenerDato();
    float distancia= actual.distanciaEuclidiana(punto);
    if(distancia < menor){
        menor = distancia;
        ver = actual;
    }
    buscarRecursivamente(nodo->obtenerHijoIzq(), punto, ver, menor);
    buscarRecursivamente(nodo->obtenerHijoDer(), punto, ver, menor);
}
std::vector<Vertice> Sistema::esquinas(const std::string& nombre) const {
    //Busca la malla por nombre
    for (std::size_t i = 0; i < mallas.size(); ++i) {
        if (mallas[i].getNombre() == nombre) {
            return mallas[i].encontrarEsquinas();
        }
    }
    //Si no se encuentra la malla devuelve un vector vacío
    std::cerr << "Error: Malla con nombre " << nombre << " no encontrada." << std::endl;
    return std::vector<Vertice>();
}



void Sistema::ayuda(){

  std::cout<<"lista de comandos: "<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"cargar nombre_archivo"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"listado"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"envolvente nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"envolvente"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"descargar nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"guardar nombre_objeto nombre_archivo"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercano px py pz nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercano px py pz"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercanos_caja nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"ruta_corta i1 i2 nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"ruta_corta_centro i1 nombre_objeto"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"salir"<<std::endl<<std::endl;


}

void Sistema::ayudaComando(std::string comando){
  if (strcmp(comando.c_str(), "cargar") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"cargar nombre_archivo"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Carga en memoria la información del objeto nombre_objeto contenida en el archivo identificado por nombre_archivo."<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  } else if (strcmp(comando.c_str(), "listado") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"listado"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras."<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  } else if (strcmp(comando.c_str(), "envolvente") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"envolvente nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<" Calcula la caja envolvente del objeto identificado por nombre_objeto. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"envolvente"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<" La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_global, para distinguirla de los demás objetos en memoria"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;


  } else if (strcmp(comando.c_str(), "descargar") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"descargar nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<" Descarga de la memoria toda la información básica (vértices, aristas, caras) del objeto identificado por nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;


  } else if (strcmp(comando.c_str(), "guardar") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"guardar nombre_objeto nombre_archivo"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Escribe en un archivo de texto, identificado por nombre_archivo, la información básica (vértices y caras) del objeto identificado por nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;


  } else if (strcmp(comando.c_str(), "v_cercano") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercano px py pz nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"  Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl<<std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercano px py pz"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"  Identifica, entre todos los objetos cargados en memoria, el vértice más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el objeto al que pertenece, el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  } else if (strcmp(comando.c_str(), "v_cercanos_caja") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"v_cercanos_caja nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Identifica los vértices del objeto nombre_objeto más cercanos (en términos de la distancia euclidiana) a los puntos (vértices) que definen la respectiva caja envolvente del objeto. Informa en pantalla, en una tabla, las coordenadas de cada una de las esquinas de la caja envolvente, y para cada una de ellas, el índice del vértice más cercano, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra de la respectiva esquina"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  } else if (strcmp(comando.c_str(), "ruta_corta") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"ruta_corta i1 i2 nombre_objeto"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Identifica los índices de los vértices que conforman la ruta más corta entre los vértices dados para el objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;


  } else if (strcmp((comando).c_str(), "ruta_corta_centro") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"ruta_corta_centro i1 nombre_objeto"<<std::endl<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<" Identifica los índices de los vértices que conforman la ruta más corta entre el vértice dado y el centro del objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada."<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  } else if (strcmp((comando).c_str(), "salir") == 0) {
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"salir"<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;
    std::cout<<"Termina la ejecución de la aplicación."<<std::endl;
    std::cout<<"------------------------------------------------"<<std::endl;

  }else {
    std::cout << "Comando no reconocido\n";
  }

}
