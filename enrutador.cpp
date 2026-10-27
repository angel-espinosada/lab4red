#include "enrutador.h"
#include<iostream>
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

// Setter para cambiar el nombre
void Enrutador::establecerNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

// Getter para obtener el nombre
string Enrutador::obtenerNombre() const {
    return nombre;
}

// Agregar o actualizar un vecino con su costo
void Enrutador::agregarVecino(string vecino, int costo) {
    vecinos[vecino] = costo;  // si ya existe, lo actualiza
}

// Eliminar un vecino
void Enrutador::eliminarVecino(string vecino) {
    vecinos.erase(vecino);
}

// Mostrar vecinos por pantalla
void Enrutador::mostrarVecinos() const {
    cout << "Vecinos de " << nombre << ":" << endl;
    for (const auto& par : vecinos) {
        cout << " -> " << par.first << " con costo: " << par.second << endl;
    }
}

// Obtener mapa completo de vecinos
map<string, int> Enrutador::obtenerVecinos() const {
    return vecinos;
}
