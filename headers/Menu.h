#include <iostream>
#include <cstdlib>
#include "Carrera.h"
#include "Editorial.h"
#include "Categoria.h"
#include "Autor.h"
#include "Estudiante.h"
#include "Libro.h"

using namespace std;

class Menu
{
public:
    Estudiante estudiante;
    Carrera carrera;
    Editorial editorial;
    Categoria categoria;
    Autor autor;
    Libro libro;

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
            cout << "7. Reservas\n";
            cout << "8. Volver al login\n"; 
            cout << "9. Finalizar\n";       
            cout << "Selecciona una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                estudiante = Estudiante();
                estudiante.menuEstudiante();
                break;
            }
            case 2:
            {
                carrera = Carrera();
                carrera.menuCarrera();
                break;
            }
            case 3:
            {
                editorial = Editorial();
                editorial.menuEditorial();
                break;
            }
            case 4:
            {
                categoria = Categoria();
                categoria.menuCategoria();
                break;
            }
            case 5:
            {
                autor = Autor();
                autor.menuAutor();
                break;
            }
            case 6:
            {
                libro = Libro();
                libro.menuLibro();
                break;
            }
            case 7:
            {
                break;
            }
            case 8:
                cout << "\nVolviendo" << endl;
                system("cls");
                return;

            case 9:
                cout << "\nTerminando" << endl;
                exit(0);

            default:
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                break;
            }

        } while (true);
    }
};
