#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Estudiante {
public:
    int id;
    std::string nombre;
    int idCarrera;
    std::string correo;
    std::string telefono;
    int estado; // 1 activo, 0 inactivo

    Estudiante(int idE, std::string n, int idC, std::string c, std::string t, int e)
        : id(idE), nombre(n), idCarrera(idC), correo(c), telefono(t), estado(e) {}
};

class Carrera {
public:
    int idCarrera;
    std::string nombreCarrera;

    Carrera(int idC, std::string n)
        : idCarrera(idC), nombreCarrera(n) {}
};

class Editorial {
public:
    int idEditorial;
    std::string nombreEditorial;

    Editorial(int idE, std::string n)
        : idEditorial(idE), nombreEditorial(n) {}
};

class Categoria {
public:
    int idCategoria;
    std::string nombreCategoria;

    Categoria(int idC, std::string n)
        : idCategoria(idC), nombreCategoria(n) {}
};

class Autor {
public:
    int idAutor;
    std::string nombreAutor;
    std::string nacionalidad;

    Autor(int idA, std::string n, std::string nat)
        : idAutor(idA), nombreAutor(n), nacionalidad(nat) {}
};

class Libro {
public:
    int idLibro;
    int idAutor;
    int idEditorial;
    int idCategoria;
    std::string idioma;
    std::string fechaPublicacion;

    Libro(int idL, int idA, int idE, int idC, std::string i, std::string f)
        : idLibro(idL), idAutor(idA), idEditorial(idE), idCategoria(idC), idioma(i), fechaPublicacion(f) {}
};

class Reserva {
public:
    int idReserva;
    int idLibro;
    int idEstudiante;
    std::string fechaReserva;
    std::string fechaExpiracion;
    int estado; // 1 para activo, 0 para inactivo

    // Constructor
    Reserva(int id, int libro, int estudiante, const std::string& fechaRes, const std::string& fechaExp, int est)
        : idReserva(id), idLibro(libro), idEstudiante(estudiante), fechaReserva(fechaRes), fechaExpiracion(fechaExp), estado(est) {}
};

class BaseDeDatos {
private:
    std::vector<Estudiante> estudiantes;
    std::vector<Carrera> carreras;
    std::vector<Editorial> editoriales;
    std::vector<Categoria> categorias;
    std::vector<Autor> autores;
    std::vector<Libro> libros;
     std::vector<Reserva> reservas; // Nuevo vector para las reservas

    int nextEstudianteId = 1;
    int nextCarreraId = 1;
    int nextEditorialId = 1;
    int nextCategoriaId = 1;
    int nextAutorId = 1;
    int nextLibroId = 1;
	int nextReservaId = 1; // Contador para el próximo ID de reserva

public:
    BaseDeDatos() {
        // Datos predeterminados
        agregarCarrera("Ingeniería de Sistemas");
        agregarCarrera("Administración de Empresas");
        agregarCarrera("Psicología");

        agregarEditorial("Editorial Planeta");
        agregarEditorial("Editorial Santillana");

        agregarCategoria("Ficción");
        agregarCategoria("No Ficción");
        agregarCategoria("Ciencia");

        agregarAutor("Gabriel García Márquez", "Colombiano");
        agregarAutor("Isabel Allende", "Chilena");
        agregarAutor("Stephen King", "Estadounidense");
    }
    
     // Métodos para manejar reservas
    void agregarReserva(int idLibro, int idEstudiante, const std::string& fechaRes, const std::string& fechaExp, int estado) {
         // Crear una nueva reserva
    Reserva nuevaReserva(nextReservaId++, idLibro, idEstudiante, fechaRes, fechaExp, estado);
    
    // Agregar la nueva reserva al vector
    reservas.push_back(nuevaReserva);
    }

    void mostrarReservas() {
        for (size_t i = 0; i < reservas.size(); ++i) {
            const Reserva& r = reservas[i];
            std::cout << "ID Reserva: " << r.idReserva
                      << ", ID Libro: " << r.idLibro
                      << ", ID Estudiante: " << r.idEstudiante
                      << ", Fecha Reserva: " << r.fechaReserva
                      << ", Fecha Expiración: " << r.fechaExpiracion
                      << ", Estado: " << (r.estado == 1 ? "Activo" : "Inactivo") << "\n";
        }
    }
    
	const std::vector<Carrera>& obtenerCarreras() const {
        return carreras;
    }

    // Métodos para Estudiantes
    void agregarEstudiante(const std::string& nombre, int idCarrera, const std::string& correo, const std::string& telefono, int estado) {
        estudiantes.push_back(Estudiante(nextEstudianteId++, nombre, idCarrera, correo, telefono, estado));
    }

    void mostrarEstudiantes() {
    	/*
        for (size_t i = 0; i < estudiantes.size(); ++i) {
            const Estudiante& e = estudiantes[i];
            std::cout << "ID: " << e.id << ", Nombre: " << e.nombre
                      << ", ID Carrera: " << e.idCarrera
                      << ", Correo: " << e.correo
                      << ", Teléfono: " << e.telefono
                      << ", Estado: " << (e.estado == 1 ? "Activo" : "Inactivo") << "\n";
        }
        */
        for (size_t i = 0; i < estudiantes.size(); ++i) {
        const Estudiante& e = estudiantes[i];
        std::string nombreCarrera;

        // Buscar el nombre de la carrera
        for (size_t j = 0; j < carreras.size(); ++j) {
            if (carreras[j].idCarrera == e.idCarrera) {
                nombreCarrera = carreras[j].nombreCarrera;
                break;
            }
        }

        std::cout << "ID: " << e.id << ", Nombre: " << e.nombre
                  << ", Carrera: " << nombreCarrera
                  << ", Correo: " << e.correo
                  << ", Teléfono: " << e.telefono
                  << ", Estado: " << (e.estado == 1 ? "Activo" : "Inactivo") << "\n";
    }
    }

    void eliminarEstudiante(int id) {
        for (size_t i = 0; i < estudiantes.size(); ++i) {
            if (estudiantes[i].id == id) {
                estudiantes.erase(estudiantes.begin() + i);
                std::cout << "Estudiante eliminado.\n";
                return;
            }
        }
        std::cout << "ID de estudiante no válido.\n";
    }

    void actualizarEstudiante(int id) {
        for (size_t i = 0; i < estudiantes.size(); ++i) {
            if (estudiantes[i].id == id) {
                Estudiante& e = estudiantes[i];
                std::cout << "Actualizar Estudiante (ID: " << id << ")\n";
                std::cout << "Nombre actual: " << e.nombre << "\nNuevo nombre: ";
                std::cin >> e.nombre;
                std::cout << "Nuevo Correo: ";
                std::cin >> e.correo;
                std::cout << "Nuevo Teléfono: ";
                std::cin >> e.telefono;
                std::cout << "Nuevo Estado (1: Activo, 0: Inactivo): ";
                std::cin >> e.estado;
                std::cout << "Estudiante actualizado.\n";
                return;
            }
        }
        std::cout << "ID de estudiante no válido.\n";
    }

    // Métodos para Carreras
    void agregarCarrera(const std::string& nombreCarrera) {
        carreras.push_back(Carrera(nextCarreraId++, nombreCarrera));
    }

    void mostrarCarreras() {
        for (size_t i = 0; i < carreras.size(); ++i) {
            const Carrera& c = carreras[i];
            std::cout << "ID: " << c.idCarrera << ", Nombre Carrera: " << c.nombreCarrera << "\n";
        }
    }

    void eliminarCarrera(int id) {
        for (size_t i = 0; i < carreras.size(); ++i) {
            if (carreras[i].idCarrera == id) {
                carreras.erase(carreras.begin() + i);
                std::cout << "Carrera eliminada.\n";
                return;
            }
        }
        std::cout << "ID de carrera no válido.\n";
    }

    void actualizarCarrera(int id) {
        for (size_t i = 0; i < carreras.size(); ++i) {
            if (carreras[i].idCarrera == id) {
                Carrera& c = carreras[i];
                std::cout << "Actualizar Carrera (ID: " << id << ")\n";
                std::cout << "Nombre actual: " << c.nombreCarrera << "\nNuevo nombre: ";
                std::cin >> c.nombreCarrera;
                std::cout << "Carrera actualizada.\n";
                return;
            }
        }
        std::cout << "ID de carrera no válido.\n";
    }

    // Métodos para Editoriales
    void agregarEditorial(const std::string& nombreEditorial) {
        editoriales.push_back(Editorial(nextEditorialId++, nombreEditorial));
    }

    void mostrarEditoriales() {
        for (size_t i = 0; i < editoriales.size(); ++i) {
            const Editorial& e = editoriales[i];
            std::cout << "ID: " << e.idEditorial << ", Nombre Editorial: " << e.nombreEditorial << "\n";
        }
    }

    void eliminarEditorial(int id) {
        for (size_t i = 0; i < editoriales.size(); ++i) {
            if (editoriales[i].idEditorial == id) {
                editoriales.erase(editoriales.begin() + i);
                std::cout << "Editorial eliminada.\n";
                return;
            }
        }
        std::cout << "ID de editorial no válido.\n";
    }

    void actualizarEditorial(int id) {
        for (size_t i = 0; i < editoriales.size(); ++i) {
            if (editoriales[i].idEditorial == id) {
                Editorial& e = editoriales[i];
                std::cout << "Actualizar Editorial (ID: " << id << ")\n";
                std::cout << "Nombre actual: " << e.nombreEditorial << "\nNuevo nombre: ";
                std::cin >> e.nombreEditorial;
                std::cout << "Editorial actualizada.\n";
                return;
            }
        }
        std::cout << "ID de editorial no válido.\n";
    }

    // Métodos para Categorías
    void agregarCategoria(const std::string& nombreCategoria) {
        categorias.push_back(Categoria(nextCategoriaId++, nombreCategoria));
    }

    void mostrarCategorias() {
        for (size_t i = 0; i < categorias.size(); ++i) {
            const Categoria& c = categorias[i];
            std::cout << "ID: " << c.idCategoria << ", Nombre Categoría: " << c.nombreCategoria << "\n";
        }
    }

    void eliminarCategoria(int id) {
        for (size_t i = 0; i < categorias.size(); ++i) {
            if (categorias[i].idCategoria == id) {
                categorias.erase(categorias.begin() + i);
                std::cout << "Categoría eliminada.\n";
                return;
            }
        }
        std::cout << "ID de categoría no válido.\n";
    }

    void actualizarCategoria(int id) {
        for (size_t i = 0; i < categorias.size(); ++i) {
            if (categorias[i].idCategoria == id) {
                Categoria& c = categorias[i];
                std::cout << "Actualizar Categoría (ID: " << id << ")\n";
                std::cout << "Nombre actual: " << c.nombreCategoria << "\nNuevo nombre: ";
                std::cin >> c.nombreCategoria;
                std::cout << "Categoría actualizada.\n";
                return;
            }
        }
        std::cout << "ID de categoría no válido.\n";
    }

    // Métodos para Autores
    void agregarAutor(const std::string& nombreAutor, const std::string& nacionalidad) {
        autores.push_back(Autor(nextAutorId++, nombreAutor, nacionalidad));
    }

    void mostrarAutores() {
        for (size_t i = 0; i < autores.size(); ++i) {
            const Autor& a = autores[i];
            std::cout << "ID: " << a.idAutor << ", Nombre Autor: " << a.nombreAutor << ", Nacionalidad: " << a.nacionalidad << "\n";
        }
    }

    void eliminarAutor(int id) {
        for (size_t i = 0; i < autores.size(); ++i) {
            if (autores[i].idAutor == id) {
                autores.erase(autores.begin() + i);
                std::cout << "Autor eliminado.\n";
                return;
            }
        }
        std::cout << "ID de autor no válido.\n";
    }

    void actualizarAutor(int id) {
        for (size_t i = 0; i < autores.size(); ++i) {
            if (autores[i].idAutor == id) {
                Autor& a = autores[i];
                std::cout << "Actualizar Autor (ID: " << id << ")\n";
                std::cout << "Nombre actual: " << a.nombreAutor << "\nNuevo nombre: ";
                std::cin >> a.nombreAutor;
                std::cout << "Nueva nacionalidad: ";
                std::cin >> a.nacionalidad;
                std::cout << "Autor actualizado.\n";
                return;
            }
        }
        std::cout << "ID de autor no válido.\n";
    }

    // Métodos para Libros
    void agregarLibro(int idAutor, int idEditorial, int idCategoria, const std::string& idioma, const std::string& fechaPublicacion) {
        libros.push_back(Libro(nextLibroId++, idAutor, idEditorial, idCategoria, idioma, fechaPublicacion));
    }

    void mostrarLibros() {
    	/*
        for (size_t i = 0; i < libros.size(); ++i) {
            const Libro& l = libros[i];
            std::cout << "ID Libro: " << l.idLibro
                      << ", ID Autor: " << l.idAutor
                      << ", ID Editorial: " << l.idEditorial
                      << ", ID Categoría: " << l.idCategoria
                      << ", Idioma: " << l.idioma
                      << ", Fecha de Publicación: " << l.fechaPublicacion << "\n";
        }
        */
        
         for (size_t i = 0; i < libros.size(); ++i) {
        const Libro& l = libros[i];
        std::string nombreAutor, nombreEditorial, nombreCategoria;

        // Buscar el nombre del autor
        for (size_t j = 0; j < autores.size(); ++j) {
            if (autores[j].idAutor == l.idAutor) {
                nombreAutor = autores[j].nombreAutor;
                break;
            }
        }

        // Buscar el nombre de la editorial
        for (size_t j = 0; j < editoriales.size(); ++j) {
            if (editoriales[j].idEditorial == l.idEditorial) {
                nombreEditorial = editoriales[j].nombreEditorial;
                break;
            }
        }

        // Buscar el nombre de la categoría
        for (size_t j = 0; j < categorias.size(); ++j) {
            if (categorias[j].idCategoria == l.idCategoria) {
                nombreCategoria = categorias[j].nombreCategoria;
                break;
            }
        }

        std::cout << "ID Libro: " << l.idLibro
                  << ", Autor: " << nombreAutor
                  << ", Editorial: " << nombreEditorial
                  << ", Categoría: " << nombreCategoria
                  << ", Idioma: " << l.idioma
                  << ", Fecha de Publicación: " << l.fechaPublicacion << "\n";
    }
    }

    void eliminarLibro(int id) {
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i].idLibro == id) {
                libros.erase(libros.begin() + i);
                std::cout << "Libro eliminado.\n";
                return;
            }
        }
        std::cout << "ID de libro no válido.\n";
    }

    void actualizarLibro(int id) {
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i].idLibro == id) {
                Libro& l = libros[i];
                std::cout << "Actualizar Libro (ID: " << id << ")\n";
                std::cout << "Nuevo ID Autor: ";
                std::cin >> l.idAutor;
                std::cout << "Nuevo ID Editorial: ";
                std::cin >> l.idEditorial;
                std::cout << "Nuevo ID Categoría: ";
                std::cin >> l.idCategoria;
                std::cout << "Nuevo Idioma: ";
                std::cin >> l.idioma;
                std::cout << "Nueva Fecha de Publicación: ";
                std::cin >> l.fechaPublicacion;
                std::cout << "Libro actualizado.\n";
                return;
            }
        }
        std::cout << "ID de libro no válido.\n";
    }

    // Métodos para mostrar opciones de relaciones
    void mostrarOpcionesAutores() {
        std::cout << "Selecciona un autor:\n";
        for (size_t i = 0; i < autores.size(); ++i) {
            std::cout << autores[i].idAutor << ": " << autores[i].nombreAutor << "\n";
        }
    }

    void mostrarOpcionesEditoriales() {
        std::cout << "Selecciona una editorial:\n";
        for (size_t i = 0; i < editoriales.size(); ++i) {
            std::cout << editoriales[i].idEditorial << ": " << editoriales[i].nombreEditorial << "\n";
        }
    }

    void mostrarOpcionesCategorias() {
        std::cout << "Selecciona una categoría:\n";
        for (size_t i = 0; i < categorias.size(); ++i) {
            std::cout << categorias[i].idCategoria << ": " << categorias[i].nombreCategoria << "\n";
        }
    }
};

void menu(BaseDeDatos& db) {
    int opcion;
    do {
        std::cout << "\nMenú Principal:\n";
std::cout << "1. Estudiantes\n";
std::cout << "2. Carreras\n";
std::cout << "3. Editoriales\n";
std::cout << "4. Categorías\n";
std::cout << "5. Autores\n";
std::cout << "6. Libros\n";
std::cout << "7. Reservas\n";  // Nueva opción para reservas
std::cout << "8. Salir\n";
std::cout << "Selecciona una opción: ";
std::cin >> opcion;

        switch (opcion) {
            case 1: { // Estudiantes
                int subopcion;
                do {
                    std::cout << "\nSubmenú Estudiantes:\n";
                    std::cout << "1. Agregar Estudiante\n";
                    std::cout << "2. Mostrar Estudiantes\n";
                    std::cout << "3. Eliminar Estudiante\n";
                    std::cout << "4. Actualizar Estudiante\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                    	/*
                        std::string nombre, correo, telefono;
                        int idCarrera, estado;
                        std::cout << "Nombre: ";
                        std::cin >> nombre;
                        std::cout << "ID Carrera: ";
                        std::cin >> idCarrera;
                        std::cout << "Correo: ";
                        std::cin >> correo;
                        std::cout << "Teléfono: ";
                        std::cin >> telefono;
                        std::cout << "Estado (1: Activo, 0: Inactivo): ";
                        std::cin >> estado;
                        */
                        
                        std::string nombre, correo, telefono;
    int idCarrera, estado;

    // Mostrar opciones de carreras
    std::cout << "Selecciona una carrera:\n";
    const std::vector<Carrera>& listaCarreras = db.obtenerCarreras();
    for (size_t j = 0; j < listaCarreras.size(); ++j) {
        std::cout << listaCarreras[j].idCarrera << ". " << listaCarreras[j].nombreCarrera << "\n";
    }

    std::cout << "ID Carrera: ";
    std::cin >> idCarrera;

    std::cout << "Nombre: ";
    std::cin >> nombre;
    std::cout << "Correo: ";
    std::cin >> correo;
    std::cout << "Teléfono: ";
    std::cin >> telefono;
    std::cout << "Estado (1: Activo, 0: Inactivo): ";
    std::cin >> estado;

                        
                        
                        db.agregarEstudiante(nombre, idCarrera, correo, telefono, estado);
                    } else if (subopcion == 2) {
                        db.mostrarEstudiantes();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de estudiante a eliminar: ";
                        std::cin >> id;
                        db.eliminarEstudiante(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de estudiante a actualizar: ";
                        std::cin >> id;
                        db.actualizarEstudiante(id);
                    }

                } while (subopcion != 5);
                break;
            }
            case 2: { // Carreras
                int subopcion;
                do {
                    std::cout << "\nSubmenú Carreras:\n";
                    std::cout << "1. Agregar Carrera\n";
                    std::cout << "2. Mostrar Carreras\n";
                    std::cout << "3. Eliminar Carrera\n";
                    std::cout << "4. Actualizar Carrera\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        std::string nombreCarrera;
                        std::cout << "Nombre Carrera: ";
                        std::cin >> nombreCarrera;
                        db.agregarCarrera(nombreCarrera);
                    } else if (subopcion == 2) {
                        db.mostrarCarreras();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de carrera a eliminar: ";
                        std::cin >> id;
                        db.eliminarCarrera(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de carrera a actualizar: ";
                        std::cin >> id;
                        db.actualizarCarrera(id);
                    }

                } while (subopcion != 5);
                break;
            }
            case 3: { // Editoriales
                int subopcion;
                do {
                    std::cout << "\nSubmenú Editoriales:\n";
                    std::cout << "1. Agregar Editorial\n";
                    std::cout << "2. Mostrar Editoriales\n";
                    std::cout << "3. Eliminar Editorial\n";
                    std::cout << "4. Actualizar Editorial\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        std::string nombreEditorial;
                        std::cout << "Nombre Editorial: ";
                        std::cin >> nombreEditorial;
                        db.agregarEditorial(nombreEditorial);
                    } else if (subopcion == 2) {
                        db.mostrarEditoriales();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de editorial a eliminar: ";
                        std::cin >> id;
                        db.eliminarEditorial(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de editorial a actualizar: ";
                        std::cin >> id;
                        db.actualizarEditorial(id);
                    }

                } while (subopcion != 5);
                break;
            }
            case 4: { // Categorías
                int subopcion;
                do {
                    std::cout << "\nSubmenú Categorías:\n";
                    std::cout << "1. Agregar Categoría\n";
                    std::cout << "2. Mostrar Categorías\n";
                    std::cout << "3. Eliminar Categoría\n";
                    std::cout << "4. Actualizar Categoría\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        std::string nombreCategoria;
                        std::cout << "Nombre Categoría: ";
                        std::cin >> nombreCategoria;
                        db.agregarCategoria(nombreCategoria);
                    } else if (subopcion == 2) {
                        db.mostrarCategorias();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de categoría a eliminar: ";
                        std::cin >> id;
                        db.eliminarCategoria(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de categoría a actualizar: ";
                        std::cin >> id;
                        db.actualizarCategoria(id);
                    }

                } while (subopcion != 5);
                break;
            }
            case 5: { // Autores
                int subopcion;
                do {
                    std::cout << "\nSubmenú Autores:\n";
                    std::cout << "1. Agregar Autor\n";
                    std::cout << "2. Mostrar Autores\n";
                    std::cout << "3. Eliminar Autor\n";
                    std::cout << "4. Actualizar Autor\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        std::string nombreAutor, nacionalidad;
                        std::cout << "Nombre Autor: ";
                        std::cin >> nombreAutor;
                        std::cout << "Nacionalidad: ";
                        std::cin >> nacionalidad;
                        db.agregarAutor(nombreAutor, nacionalidad);
                    } else if (subopcion == 2) {
                        db.mostrarAutores();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de autor a eliminar: ";
                        std::cin >> id;
                        db.eliminarAutor(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de autor a actualizar: ";
                        std::cin >> id;
                        db.actualizarAutor(id);
                    }

                } while (subopcion != 5);
                break;
            }
            case 6: { // Libros
                int subopcion;
                do {
                    std::cout << "\nSubmenú Libros:\n";
                    std::cout << "1. Agregar Libro\n";
                    std::cout << "2. Mostrar Libros\n";
                    std::cout << "3. Eliminar Libro\n";
                    std::cout << "4. Actualizar Libro\n";
                    std::cout << "5. Volver\n";
                    std::cout << "Selecciona una opción: ";
                    std::cin >> subopcion;

                    if (subopcion == 1) {
                        db.mostrarOpcionesAutores();
                        int idAutor;
                        std::cout << "Selecciona ID Autor: ";
                        std::cin >> idAutor;

                        db.mostrarOpcionesEditoriales();
                        int idEditorial;
                        std::cout << "Selecciona ID Editorial: ";
                        std::cin >> idEditorial;

                        db.mostrarOpcionesCategorias();
                        int idCategoria;
                        std::cout << "Selecciona ID Categoría: ";
                        std::cin >> idCategoria;

                        std::string idioma, fechaPublicacion;
                        std::cout << "Idioma: ";
                        std::cin >> idioma;
                        std::cout << "Fecha de Publicación: ";
                        std::cin >> fechaPublicacion;

                        db.agregarLibro(idAutor, idEditorial, idCategoria, idioma, fechaPublicacion);
                    } else if (subopcion == 2) {
                        db.mostrarLibros();
                    } else if (subopcion == 3) {
                        int id;
                        std::cout << "ID de libro a eliminar: ";
                        std::cin >> id;
                        db.eliminarLibro(id);
                    } else if (subopcion == 4) {
                        int id;
                        std::cout << "ID de libro a actualizar: ";
                        std::cin >> id;
                        db.actualizarLibro(id);
                    }

                } while (subopcion != 5);
                break;
            }
            
            case 7: {  // Opción de Reservas
        int subopcion;
        do {
            std::cout << "\nSubmenú Reservas:\n";
            std::cout << "1. Agregar Reserva\n";
            std::cout << "2. Mostrar Reservas\n";
            std::cout << "3. Eliminar Reserva\n";
            std::cout << "4. Actualizar Reserva\n";
            std::cout << "5. Volver\n";
            std::cout << "Selecciona una opción: ";
            std::cin >> subopcion;

            switch (subopcion) {
                case 1: {
                
                    int idLibro, idEstudiante, estado;
                    std::string fechaReserva, fechaExpiracion;

                    // Obtener información de la reserva
                    std::cout << "ID Libro: ";
                    std::cin >> idLibro;
                    std::cout << "ID Estudiante: ";
                    std::cin >> idEstudiante;
                    std::cout << "Fecha Reserva (dd/mm/yyyy): ";
                    std::cin >> fechaReserva;
                    std::cout << "Fecha Expiración (dd/mm/yyyy): ";
                    std::cin >> fechaExpiracion;
                    std::cout << "Estado (1: Activo, 0: Inactivo): ";
                    std::cin >> estado;

                    db.agregarReserva(idLibro, idEstudiante, fechaReserva, fechaExpiracion, estado);
                    break;
                  
                    
                }
                case 2:
                    db.mostrarReservas();
                    break;
                case 3:
                    // Implementar la lógica para eliminar una reserva
                    break;
                case 4:
                    // Implementar la lógica para actualizar una reserva
                    break;
                case 5:
                    // Volver al menú principal
                    break;
                default:
                    std::cout << "Opción no válida. Por favor, selecciona de nuevo.\n";
                    break;
            }
        } while (subopcion != 5);
        break;
    }
            
            
            case 8:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtalo de nuevo.\n";
        }
    } while (opcion != 8);
}

int main() {
    BaseDeDatos db;
    menu(db);
    return 0;
}

