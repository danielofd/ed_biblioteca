#include <iostream>
#include <cstdlib>
#include "Carrera.h"

using namespace std;

class Menu
{
public:
    void menuPrincipal()
    {
        int opcion;
        cout << "\n-------------------Bienvenido-------------------\n";
        do
        {
            cout << "\nMenu Principal:\n";
            cout << "1. Estudiantes\n";
            cout << "2. Carreras\n";
            cout << "3. Editoriales\n";
            cout << "4. Categorias\n";
            cout << "5. Autores\n";
            cout << "6. Libros\n";
            cout << "7. Reservas\n"; // Nueva opción para reservas
            cout << "8. Salir\n";
            cout << "Selecciona una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                int subOpcion;
                do
                {
                    cout << "\nSubmenú Estudiantes:\n";
                    cout << "1. Agregar Estudiante\n";
                    cout << "2. Mostrar Estudiantes\n";
                    cout << "3. Eliminar Estudiante\n";
                    cout << "4. Actualizar Estudiante\n";
                    cout << "5. Volver\n";
                    cout << "Selecciona una opción: ";
                    cin >> subOpcion;

                } while (subOpcion != 5);
                break;
            }

            case 2:
            {
                int subOpcion;
                int idCarrera;
                string nombreCarrera;
                Carrera carrera; // Objeto Carrera
                do
                {
                    cout << "\nSubmenu Carreras:\n";
                    cout << "1. Agregar Carrera\n";
                    cout << "2. Consultar Carrera\n";
                    cout << "3. Mostrar Todas las Carreras\n";
                    cout << "4. Eliminar Carrera\n";
                    cout << "5. Actualizar Carrera\n";
                    cout << "6. Volver\n";
                    cout << "Selecciona una opcion: ";
                    cin >> subOpcion;

                    if (subOpcion == 1)
                    {
                        /*AGREGAR NUEVA CARRERA*/
                        cout << "Nombre Carrera: ";
                        getline(cin, nombreCarrera);
                        getline(cin, nombreCarrera); // Esto es para evitar el bucle infinito...
                        carrera = Carrera(nombreCarrera);
                        carrera.agregarCarrera();
                    }
                    else if (subOpcion == 2)
                    {
                        cout << "ID Carrera a Consultar: ";
                        cin >> idCarrera;
                        carrera.mostrarCarreraPorId(idCarrera);
                    }
                    else if (subOpcion == 3)
                    {
                        carrera.mostrarCarrera();
                    }
                    else if (subOpcion == 4)
                    {
                        cout << "ID Carrera: ";
                        cin >> idCarrera;
                        cin.ignore();
                        if (carrera.verificarCarrera(idCarrera) == 1)
                        {
                            carrera.eliminarCarrera(idCarrera);
                        }
                        else
                        {
                            cout << "\nError, No se pudo encontrar carrera con dicho ID" << endl;
                        }
                    }
                    else if (subOpcion == 5)
                    {
                        cout << "ID Carrera: ";
                        cin >> idCarrera;
                        cin.ignore();
                        cout << "Nombre Nuevo de Carrera: ";
                        getline(cin, nombreCarrera);
                        carrera = Carrera(nombreCarrera);

                        if (carrera.verificarCarrera(idCarrera) == 1)
                        {
                            carrera.actualizarCarrera(idCarrera);
                        }
                        else
                        {
                            cout << "\nError, No se pudo encontrar carrera con dicho ID" << endl;
                        }
                    }

                } while (subOpcion != 6);
                break;
            }

            case 3:
            {
                break;
            }

            case 8:
                cout << "Saliendo...\n";
                system("cls");
                break;

            default:
                cout << "Opción no valida. Inténtalo de nuevo.\n";
                break;
            }

        } while (opcion != 8);
    }
};