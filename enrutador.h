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
    map<string, int> vecinos;        // vecinos directos y sus costos
    map<string, InfoRuta> tabla;     // tabla de costos: destino -> mejor ruta

public:
    Enrutador();
    Enrutador(string nombre);
    //  Destructor
    ~Enrutador();
    //  Setters
    void establecerNombre(string nuevoNombre);

    //  Getters
    string obtenerNombre() const;

    // Agregar
    void agregarVecino(string vecino, int costo);


    void eliminarVecino(string vecino);


    void mostrarVecinos() const;


    map<string, int> obtenerVecinos() const;

    // Tabla de costos (la llena la Red)
    void actualizarTabla(const map<string, InfoRuta>& nuevaTabla);
    map<string, InfoRuta> obtenerTabla() const;
    void mostrarTabla() const;


};

#endif // ENRUTADOR_H
