#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Red
{
private:
    map<string, Enrutador> enrutadores;  // Todos los enrutadores de la red

public:
    Red();

    // Métodos
    //void agregarEnrutador(const string& nombre, const map<string, int>& vecinos);
    void agregarEnrutador(const string& nombre);
    void eliminarEnrutador(const string& nombre);
    bool existeEnrutador(const string& nombre) const;
    void guardarEnArchivo(const string& nombreArchivo) const;
    void cargarDesdeArchivo(const string& nombreArchivo);
    void conectarEnrutadores(const string& origen, const string& destino, int costo);
    void encontrarRutaMinima(const string& origen, const string& destino) const;
    void mostrarEnrutadores() const;
    void generarRedAleatoria(int cantidad);
    void rutaMinimaConEstadisticas(const string& origen, const string& destino);
    // Dijkstra
    map<string, int> calcularRutasDesde(const string& origen);
    vector<string> obtenerRutaMasCorta(const string& origen, const string& destino);
    int obtenerCostoMinimo(const string& origen, const string& destino);

    // Actualización de tablas
    void actualizarTablasEnrutamiento();

    // Mostrar información
    void mostrarRed() const;

};

#endif // RED_H
