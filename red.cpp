#include "red.h"
#include "Enrutador.h"
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
    enrutadores[nombre] = Enrutador(nombre);
}
// Eliminar un enrutador de la red
void Red::eliminarEnrutador(const string& nombre) {
    auto it = enrutadores.find(nombre);
    if (it == enrutadores.end()) {
        cout << "Error: El enrutador '" << nombre << "' no existe en la red." << endl;
        return;
    }

    enrutadores.erase(it);
    cout << "Enrutador '" << nombre << "' eliminado correctamente de la red." << endl;

    // TODO: Actualizar tablas de enrutamiento después de eliminar
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


map<string, int> Red::calcularRutasDesde(const string& origen) {

    return map<string, int>();
}

vector<string> Red::obtenerRutaMasCorta(const string& origen, const string& destino) {

    return vector<string>();
}


int Red::obtenerCostoMinimo(const string& origen, const string& destino) {
    //Implementar después de Dijkstra
    return -1;
}
// Conecta dos enrutadores (origen y destino) con un costo

void Red::conectarEnrutadores(const string& origen, const string& destino, int costo) {
    enrutadores[origen].agregarVecino(destino, costo);
}
void Red::actualizarTablasEnrutamiento() {

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
        enrutadores[origen].agregarVecino(destino, costo);
        enrutadores[destino].agregarVecino(origen, costo);
    }

    archivo.close();
    cout << "Red cargada desde " << nombreArchivo << " exitosamente.\n";
}
void Red::encontrarRutaMinima(const string& origen, const string& destino) const {
    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }

    // Inicializar estructuras
    map<string, int> distancias;
    map<string, string> anteriores;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (const auto& par : enrutadores) {
        distancias[par.first] = INT_MAX;
    }
    distancias[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        string actual = pq.top().second;
        int distActual = pq.top().first;
        pq.pop();

        const auto& vecinos = enrutadores.at(actual).obtenerVecinos();
        for (const auto& vecino : vecinos) {
            int nuevaDist = distActual + vecino.second;
            if (nuevaDist < distancias[vecino.first]) {
                distancias[vecino.first] = nuevaDist;
                anteriores[vecino.first] = actual;
                pq.push({nuevaDist, vecino.first});
            }
        }
    }

    // Mostrar resultado
    if (distancias[destino] == INT_MAX) {
        cout << "No hay camino entre " << origen << " y " << destino << endl;
        return;
    }

    // Mostrar costo total
    cout << "Costo mínimo de " << origen << " a " << destino << ": " << distancias[destino] << endl;

    // Reconstruir ruta
    vector<string> camino;
    string actual = destino;
    while (actual != origen) {
        camino.push_back(actual);
        actual = anteriores[actual];
    }
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());

    // Mostrar ruta
    cout << "Ruta: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i];
        if (i < camino.size() - 1) cout << " -> ";
    }
    cout << endl;
}
void Red::mostrarEnrutadores() const {
    cout << "\nEnrutadores en la red:\n";
    for (const auto& par : enrutadores) {
        cout << " - " << par.first << endl;
    }
}

void Red::rutaMinimaConEstadisticas(const string& origen, const string& destino) {
    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    // Estructuras para Dijkstra
    map<string, int> distancias;
    map<string, string> anterior;
    set<string> visitados;
    int iteraciones = 0;

    for (const auto& par : enrutadores) {
        distancias[par.first] = INT_MAX;
    }
    distancias[origen] = 0;

    while (visitados.size() < enrutadores.size()) {
        // Elegir nodo no visitado con menor distancia
        string actual = "";
        int menor = INT_MAX;
        for (const auto& par : distancias) {
            if (visitados.find(par.first) == visitados.end() && par.second < menor) {
                menor = par.second;
                actual = par.first;
            }
        }

        if (actual == "") break;  // No hay más alcanzables

        visitados.insert(actual);
        iteraciones++;

        for (const auto& vecino : enrutadores[actual].obtenerVecinos()) {
            int nuevoCosto = distancias[actual] + vecino.second;
            if (nuevoCosto < distancias[vecino.first]) {
                distancias[vecino.first] = nuevoCosto;
                anterior[vecino.first] = actual;
            }
        }
    }

    if (distancias[destino] == INT_MAX) {
        cout << "No hay ruta entre " << origen << " y " << destino << ".\n";
        return;
    }

    // Mostrar resultados
    cout << "Costo mínimo de " << origen << " a " << destino << ": " << distancias[destino] << endl;

    // Reconstruir camino
    vector<string> camino;
    string nodo = destino;
    while (nodo != origen) {
        camino.push_back(nodo);
        nodo = anterior[nodo];
    }
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());

    cout << "Ruta: ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i];
        if (i != camino.size() - 1) cout << " -> ";
    }
    cout << endl;

    // Mostrar iteraciones
    cout << "Iteraciones realizadas: " << iteraciones << endl;

    // Estimar memoria (aproximada)
    int memoria = enrutadores.size() * sizeof(Enrutador);
    cout << "Memoria estimada usada por la red: " << memoria << " bytes\n";
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
                conectarEnrutadores(destino, origen, costo); // bidireccional
            }
        }
    }

    cout << "\n Red aleatoria generada:\n";
    mostrarRed();
}
