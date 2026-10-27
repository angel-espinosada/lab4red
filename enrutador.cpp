#include "enrutador.h"
#include<iostream>
using namespace std;
#include<queue>
#include <map>
#include <vector>
#include <string>

Enrutador::Enrutador() {
    nombre = "";
}

// Constructor
Enrutador::Enrutador(string nombre) {
    this->nombre = nombre;
}

// Destructor
Enrutador::~Enrutador() {
    // No hay memoria dinámica, por ahora no hace nada
}

// Setter
void Enrutador::establecerNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

// Getter
string Enrutador::obtenerNombre() const {
    return nombre;
}


void Enrutador::agregarVecino(string vecino, int costo) {
    vecinos[vecino] = costo;  // si ya existe, lo actualiza
}


void Enrutador::eliminarVecino(string vecino) {
    vecinos.erase(vecino);
}


void Enrutador::mostrarVecinos() const {
    cout << "Vecinos de " << nombre << ":" << endl;
    for (const auto& par : vecinos) {
        cout << " -> " << par.first << " con costo: " << par.second << endl;
    }
}


map<string, int> Enrutador::obtenerVecinos() const {
    return vecinos;
}

// Reemplaza la tabla completa por la que calculo la Red
void Enrutador::actualizarTabla(const map<string, InfoRuta>& nuevaTabla) {
    tabla = nuevaTabla;
}

map<string, InfoRuta> Enrutador::obtenerTabla() const {
    return tabla;
}

void Enrutador::mostrarTabla() const {
    cout << "Tabla de costos de " << nombre << ":" << endl;
    cout << "  Destino  Costo  Salir por  Ruta" << endl;
    for (const auto& par : tabla) {
        const InfoRuta& info = par.second;
        cout << "  " << par.first << "        " << info.costo
             << "      " << info.siguienteSalto << "         ";
        for (size_t i = 0; i < info.rutaCompleta.size(); i++) {
            cout << info.rutaCompleta[i];
            if (i < info.rutaCompleta.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}
