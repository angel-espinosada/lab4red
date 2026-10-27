#include "red.h"
#include "enrutador.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>  // Para rand y srand
#include <ctime>
#include <climits> // Para INT_MAX// Para time (semilla aleatoria)
#include <algorithm>

using namespace std;

Red::Red() {}


void Red::agregarEnrutador(const string& nombre){
    if (existeEnrutador(nombre))
        return;                              // ya existe: conserva sus vecinos
    enrutadores[nombre] = Enrutador(nombre);
    actualizarTablasEnrutamiento();
}
// Eliminar un enrutador de la red
void Red::eliminarEnrutador(const string& nombre) {
    auto it = enrutadores.find(nombre);
    if (it == enrutadores.end()) {
        cout << "Error: El enrutador '" << nombre << "' no existe en la red." << endl;
        return;
    }

    enrutadores.erase(it);

    // quitarlo de la libreta de todos los demas
    for (auto& par : enrutadores)
        par.second.eliminarVecino(nombre);

    cout << "Enrutador '" << nombre << "' eliminado correctamente de la red." << endl;
    actualizarTablasEnrutamiento();
}

// Verificar si un enrutador existe
bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

// Mostrar información básica de la red
void Red::mostrarRed() const {
    cout << " RED DE ENRUTADORES" << endl;
    if (enrutadores.empty()) {
        cout << "La red está vacía." << endl;
        return;
    }

    cout << "Enrutadores en la red: ";
    for (const auto& par : enrutadores) {
        cout << par.first << " ";
    }
    cout << endl;

    cout << "Total de enrutadores: " << enrutadores.size() << endl;
}


// Dijkstra desde un origen. Devuelve, para cada destino alcanzable,
// su costo minimo, el vecino por donde hay que salir y la ruta completa.
map<string, InfoRuta> Red::calcularRutasDesde(const string& origen) const {
    map<string, int> distancias;
    map<string, string> anterior;
    set<string> visitados;

    for (const auto& par : enrutadores)
        distancias[par.first] = INT_MAX;     // INT_MAX = "todavia no se como llegar"
    distancias[origen] = 0;

    while (visitados.size() < enrutadores.size()) {
        // 1. elegir el no visitado mas cercano
        string actual = "";
        int menor = INT_MAX;
        for (const auto& par : distancias) {
            if (visitados.find(par.first) == visitados.end() && par.second < menor) {
                menor = par.second;
                actual = par.first;
            }
        }
        if (actual == "") break;             // los que quedan no son alcanzables

        // 2. confirmarlo
        visitados.insert(actual);

        // 3. ver si mejora el costo de sus vecinos
        for (const auto& vecino : enrutadores.at(actual).obtenerVecinos()) {
            int nuevoCosto = distancias[actual] + vecino.second;
            if (nuevoCosto < distancias[vecino.first]) {
                distancias[vecino.first] = nuevoCosto;
                anterior[vecino.first] = actual;  // llegue a el desde 'actual'
            }
        }
    }

    // 4. armar la tabla: solo los destinos alcanzables
    map<string, InfoRuta> tabla;
    for (const auto& par : distancias) {
        if (par.second == INT_MAX) continue;     // no hay camino: no va en la tabla

        InfoRuta info;
        info.costo = par.second;

        // reconstruir la ruta leyendo 'anterior' al reves
        string nodo = par.first;
        while (nodo != origen) {
            info.rutaCompleta.push_back(nodo);
            nodo = anterior[nodo];
        }
        info.rutaCompleta.push_back(origen);
        reverse(info.rutaCompleta.begin(), info.rutaCompleta.end());

        // el siguiente salto es el segundo de la ruta (o el mismo si es el origen)
        if (info.rutaCompleta.size() > 1)
            info.siguienteSalto = info.rutaCompleta[1];
        else
            info.siguienteSalto = origen;

        tabla[par.first] = info;
    }
    return tabla;
}





// Conecta dos enrutadores (origen y destino) con un costo

void Red::conectarEnrutadores(const string& origen, const string& destino, int costo) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Error: uno o ambos enrutadores no existen" << endl;
        return;
    }
    if (origen == destino) {
        cout << "Error: un enrutador no se puede conectar consigo mismo" << endl;
        return;
    }
    if (costo <= 0) {
        cout << "Error: el costo debe ser mayor que 0" << endl;
        return;
    }
    enrutadores[origen].agregarVecino(destino, costo);   // A anota a B
    enrutadores[destino].agregarVecino(origen, costo);   // B anota a A
    actualizarTablasEnrutamiento();
}
// Cada vez que la red cambia, se recalcula la tabla de TODOS los enrutadores
void Red::actualizarTablasEnrutamiento() {
    for (auto& par : enrutadores)
        par.second.actualizarTabla(calcularRutasDesde(par.first));
}

void Red::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << " No se pudo abrir el archivo para guardar.\n";
        return;
    }

    for (const auto& par : enrutadores) {
        const string& origen = par.first;
        const auto& vecinos = par.second.obtenerVecinos();

        for (const auto& v : vecinos) {
            archivo << origen << " " << v.first << " " << v.second << "\n";
        }
    }

    archivo.close();
    cout << "Red guardada exitosamente en " << nombreArchivo << endl;
}
void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para leer.\n";
        return;
    }

    string origen, destino;
    int costo;

    while (archivo >> origen >> destino >> costo) {
        agregarEnrutador(origen);
        agregarEnrutador(destino);
        conectarEnrutadores(origen, destino, costo);
    }

    archivo.close();
    cout << "Red cargada desde " << nombreArchivo << " exitosamente.\n";
}
void Red::mostrarRuta(const string& origen, const string& destino) const {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    map<string, InfoRuta> tabla = enrutadores.at(origen).obtenerTabla();
    if (tabla.find(destino) == tabla.end()) {
        cout << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }
    const InfoRuta& info = tabla.at(destino);
    cout << "Costo minimo de " << origen << " a " << destino << ": " << info.costo << endl;
    cout << "Ruta: ";
    for (size_t i = 0; i < info.rutaCompleta.size(); i++) {
        cout << info.rutaCompleta[i];
        if (i < info.rutaCompleta.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void Red::mostrarTablaDe(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        cout << "Error: el enrutador " << nombre << " no existe" << endl;
        return;
    }
    enrutadores.at(nombre).mostrarTabla();
}

void Red::desconectarEnrutadores(const string& origen, const string& destino) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Error: uno o ambos enrutadores no existen" << endl;
        return;
    }
    if (enrutadores.at(origen).obtenerVecinos().count(destino) == 0) {
        cout << "Error: " << origen << " y " << destino << " no estan conectados" << endl;
        return;
    }
    enrutadores[origen].eliminarVecino(destino);
    enrutadores[destino].eliminarVecino(origen);
    cout << "Enlace " << origen << " - " << destino << " eliminado" << endl;
    actualizarTablasEnrutamiento();
}

void Red::mostrarVecinosDe(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        cout << "Error: el enrutador " << nombre << " no existe" << endl;
        return;
    }
    enrutadores.at(nombre).mostrarVecinos();
}
void Red::mostrarEnrutadores() const {
    cout << "\nEnrutadores en la red:\n";
    for (const auto& par : enrutadores) {
        cout << " - " << par.first << endl;
    }
}



void Red::generarRedAleatoria(int cantidad) {
    if (cantidad < 2) {
        cout << "Necesitas al menos 2 enrutadores.\n";
        return;
    }

    // Letras: A, B, C, ...
    for (int i = 0; i < cantidad; ++i) {
        char nombre = 'A' + i;
        agregarEnrutador(string(1, nombre));
    }

    // Semilla aleatoria
    srand(time(0));

    // Conectar enrutadores de forma aleatoria
    for (int i = 0; i < cantidad; ++i) {
        for (int j = i + 1; j < cantidad; ++j) {
            if (rand() % 2 == 0) {  // 50% de probabilidad de conectar
                int costo = 1 + rand() % 10;  // Costo entre 1 y 10
                string origen(1, 'A' + i);
                string destino(1, 'A' + j);

                conectarEnrutadores(origen, destino, costo);
            }
        }
    }

    cout << "\n Red aleatoria generada:\n";
    mostrarRed();
}
