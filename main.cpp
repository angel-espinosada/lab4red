#include <iostream>
#include <string>
#include "red.h"

using namespace std;

int main()
{
    Red red;
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n===== MENU DE RED DE ENRUTADORES =====\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Conectar enrutadores (vecinos)\n";
        cout << "3. Eliminar enrutador\n";
        cout << "4. Mostrar red\n";
        cout << "5. Calcular ruta mas corta\n";
        cout << "6. Mostrar tabla de costos de un enrutador\n";
        cout << "7. Mostrar enrutadores\n";
        cout << "8. Generar red aleatoria\n";
        cout << "9. Guardar red en archivo\n";
        cout << "10. Cargar red desde archivo\n";
        cout << "11. Eliminar enlace\n";
        cout << "12. Mostrar vecinos\n";
        cout << "0. Salir\n";
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcion no valida: escribe un numero" << endl;
            opcion = -1;
            continue;
        }
        switch (opcion) {
        case 1: {
            string nombre;
            cout << "Nombre del enrutador: ";
            cin >> nombre;
            if (red.existeEnrutador(nombre))
                cout << "El enrutador " << nombre << " ya existe" << endl;
            else
                red.agregarEnrutador(nombre);
            break;
        }
        case 2: {
            string origen, destino;
            int costo;
            cout << "Origen: ";
            cin >> origen;
            cout << "Destino: ";
            cin >> destino;
            if (!red.existeEnrutador(origen) || !red.existeEnrutador(destino)) {
                cout << "Error: uno o ambos enrutadores no existen" << endl;
                break;
            }
            cout << "Costo: ";
            cin >> costo;
            red.conectarEnrutadores(origen, destino, costo);
            break;
        }
        case 3: { string n; cout << "Nombre: ";
            cin >> n;
            red.eliminarEnrutador(n);
            break;
        }
        case 4: red.mostrarRed();
            break;
        case 5: {
            string origen, destino;
            cout << "Origen: ";
            cin >> origen;
            cout << "Destino: ";
            cin >> destino;
            red.mostrarRuta(origen, destino);
            break;
        }
        case 6: {
            string n;
            cout << "Nombre: ";
            cin >> n;
            red.mostrarTablaDe(n);
            break; }
        case 7: red.mostrarEnrutadores();
            break;
        case 8: { int c;
            cout << "Cuantos: ";
            cin >> c;
            red.generarRedAleatoria(c);
            break;
        }
        case 9: {
            string a; cout << "Archivo: ";
            cin >> a;
            red.guardarEnArchivo(a);
            break;
        }
        case 10: {
            string a;
            cout << "Archivo: ";
            cin >> a; red.cargarDesdeArchivo(a);
            break; }
        case 11: {
            string origen, destino;
            cout << "Origen: ";
            cin >> origen;
            cout << "Destino: ";
            cin >> destino;
            red.desconectarEnrutadores(origen, destino);
            break;
        }
        case 12: { string n;
            cout << "Nombre: ";
            cin >> n;
            red.mostrarVecinosDe(n);
            break;
        }
        case 0: cout << "Hasta luego!\n"; break;
        default: cout << "Opcion no valida.\n";
        }
    }
    return 0;
}
