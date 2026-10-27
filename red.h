#ifndef RED_H
#define RED_H

#include "enrutador.h"
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
    void mostrarEnrutadores() const;
    void generarRedAleatoria(int cantidad);
    // Dijkstra
    map<string, InfoRuta> calcularRutasDesde(const string& origen) const;
    void mostrarRuta(const string& origen, const string& destino) const;
    void mostrarTablaDe(const string& nombre) const;
    void desconectarEnrutadores(const string& origen, const string& destino);
    void mostrarVecinosDe(const string& nombre) const;

    // Actualización de tablas
    void actualizarTablasEnrutamiento();

    // Mostrar información
    void mostrarRed() const;

};

#endif // RED_H
