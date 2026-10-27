#include <iostream>
#include <map>
#include <string>
#include "Enrutador.h"
#include "red.h"


using namespace std;

int main()
{
    Red red;
    Enrutador enrutador;
    int opcion= -1;

    while (opcion!=0) {
        cout << "\n===== MENU DE RED DE ENRUTADORES =====\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Conectar enrutadores (vecinos)\n";
        cout << "3. Eliminar enrutador\n";
        cout << "4. Mostrar red\n";
        cout << "5. Calcular ruta mas corta (Dijkstra)\n";
        cout << "6. Iteraciones y medicion de memoria (simulacion)\n";
        cout << "7. Mostrar Enrutadores\n";
        cout << "8. Generar red aleatoria\n";
        cout << "9. Guardar red en archivo\n";
        cout << "10. Cargar red desde archivo\n";
        cout<< "12. mostrar vecinos\n";
        cout << "11. Salir\n";
        cin>>opcion;
        switch(opcion){

        case 1: {
            string nombre;
            cout << "Nombre del enrutador: ";
            cin >> nombre;
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
            cout << "Costo: ";
            cin >> costo;
            red.conectarEnrutadores(origen, destino, costo);
            break;
        }
        case 3: {
            string nombre;
            cout << "Nombre del enrutador a eliminar: ";
            cin >> nombre;
            red.eliminarEnrutador(nombre);
            break;
        }
        case 4: {
            red.mostrarRed();
            break;
        }
        case 5: {string origen, destino;
            cout << "Ingrese enrutador de origen: ";
            cin >> origen;
            cout << "Ingrese enrutador de destino: ";
            cin >> destino;
            red.rutaMinimaConEstadisticas(origen, destino);
            break;
        }
        case 6: {
            string origen, destino;
            cout << "Ingrese enrutador de origen: ";
            cin >> origen;
            cout << "Ingrese enrutador de destino: ";
            cin >> destino;
            red.encontrarRutaMinima(origen, destino);
            break;
        }
        case 7:
            red.mostrarEnrutadores();
            break;

        case 8: {
            int cantidad;
            cout << "¿Cuantos enrutadores quieres generar?: ";
            cin >> cantidad;
            red.generarRedAleatoria(cantidad);

            break;
        }


        case 9: {
            string archivo;
            cout << "Nombre del archivo para guardar: ";
            cin >> archivo;
            red.guardarEnArchivo(archivo);
            break;
        }
        case 10: {
            string archivo;
            cout << "Nombre del archivo para cargar: ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
            break;
        }
        case 14:
            cout << "Hasta luego!\n";
            break;

        case 12:{

            enrutador.mostrarVecinos();
            break;
        }
        default:
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 14);
    return 0;
}
