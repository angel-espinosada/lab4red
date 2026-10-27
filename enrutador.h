#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <string>
#include<map>
#include<vector>

using namespace std;


struct InfoRuta {
    int costo;
    string siguienteSalto;
    vector<string> rutaCompleta;
};

class Enrutador
{
private:
    string nombre;
    map<string, int> vecinos;  // vecinos directos y sus costos

public:
    Enrutador();
    Enrutador(string nombre);
    //  Destructor
    ~Enrutador();
    //  Setters
    void establecerNombre(string nuevoNombre);

    //  Getters
    string obtenerNombre() const;

    // Agregar o modificar un vecino
    void agregarVecino(string vecino, int costo);

    // Eliminar un vecino
    void eliminarVecino(string vecino);

    //  Mostrar vecinos
    void mostrarVecinos() const;

    // Obtener el mapa de vecinos
    map<string, int> obtenerVecinos() const;


};

#endif // ENRUTADOR_H
