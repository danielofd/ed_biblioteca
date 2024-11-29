#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"
#include "Autor.h"
#include "Editorial.h"
#include "Categoria.h"

using namespace std;

class Libro
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idLibro, idAutor, idEditorial, idCategoria, fecha;
    string titulo, idioma;
    Autor autor;
    Editorial editorial;
    Categoria categoria;
    int state = 0;

    Libro() {}

    Libro(int ia, int ie, int ic, int f, string t, string id)
        : idAutor(ia), idEditorial(ie), idCategoria(ic), fecha(f), titulo(t), idioma(id) {}

    // METODO PARA AGREGAR LIBRO
    void agregarLibro()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (autor.verificarAutor(idAutor) && editorial.verificarEditorial(idEditorial) && categoria.verificarCategoria(idCategoria))
        {
            if (conn.getConnector())
            {
                string lA = to_string(idAutor);
                string lE = to_string(idEditorial);
                string lC = to_string(idCategoria);
                string lF = to_string(fecha);
                string sql = "insert into libros (Titulo, ID_Autor, ID_Editorial, ID_Categoria, Idioma, Fecha_Publicacion) values ('" + titulo + "','" + lA + "','" + lE + "','" + lC + "','" + idioma + "','" + lF + "');";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nEstudiante registrado exitosamente!" << endl;
                }
                else
                {
                    system("color c");
                    cout << "Error, vuelvalo a intentar..." << endl;
                }
            }
        }
        else
        {
            cout << "\nFavor verificar que los IDs de Autor, Editorial, Categoria ingresados sean validos" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR LIBRO
    void mostrarLibros()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Libros-------------------------" << endl;

            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria;");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                while (row = mysql_fetch_row(res))
                {
                    cout << row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6] << endl;
                }
            }
            else
            {
                system("color c");
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR LIBRO POR ID
    void mostrarLibroPorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where l.ID_Libro = " + to_string(id) + ";");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6] << endl;
                }
                else
                {
                    cout << "\nNo se encontro ningun registro con ID = " << id << endl;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR LIBRO POR TITULO
    bool mostrarLibroPorTitulo(string titulo)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where l.Titulo like '%" + titulo + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Titulo = " << titulo << endl;
                    }
                    // Liberar el resultado después de usarlo
                    mysql_free_result(res);
                }
                else
                {
                    cout << "\nError al obtener el resultado de la consulta." << endl;
                }
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA MOSTRAR LIBRO POR AUTOR
    bool mostrarLibroPorAutor(string autor)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where a.Nombre_Autor like '%" + autor + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Autor = " << autor << endl;
                    }
                    // Liberar el resultado después de usarlo
                    mysql_free_result(res);
                }
                else
                {
                    cout << "\nError al obtener el resultado de la consulta." << endl;
                }
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA MOSTRAR LIBRO POR EDITORIAL
    bool mostrarLibroPorEditorial(string editorial)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where e.Nombre_Editorial like '%" + editorial + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Editorial = " << editorial << endl;
                    }
                    // Liberar el resultado después de usarlo
                    mysql_free_result(res);
                }
                else
                {
                    cout << "\nError al obtener el resultado de la consulta." << endl;
                }
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA MOSTRAR LIBRO POR CATEGORIA
    bool mostrarLibroPorCategoria(string categoria)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where c.Nombre_Categoria like '%" + categoria + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Categoria = " << categoria << endl;
                    }
                    // Liberar el resultado después de usarlo
                    mysql_free_result(res);
                }
                else
                {
                    cout << "\nError al obtener el resultado de la consulta." << endl;
                }
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA MOSTRAR LIBRO POR FECHA DE PUBLICACION
    bool mostrarLibroPorFecha(int fecha)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select l.ID_Libro, l.Titulo, a.Nombre_Autor, e.Nombre_Editorial, ") 
                             + ("c.Nombre_Categoria, l.Idioma, l.Fecha_Publicacion from libros as l ") 
                             + ("inner join autores as a on l.ID_Autor = a.ID_Autor ") 
                             + ("inner join editoriales as e on l.ID_Editorial = e.ID_Editorial ") 
                             + ("inner join categorias as c on l.ID_Categoria = c.ID_Categoria where l.Fecha_Publicacion like '%" + to_string(fecha) + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << " || " << row[6];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Fecha de Publicacion = " << fecha << endl;
                    }
                    // Liberar el resultado después de usarlo
                    mysql_free_result(res);
                }
                else
                {
                    cout << "\nError al obtener el resultado de la consulta." << endl;
                }
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA VERIFICAR SI EXISTE LIBRO POR ID
    bool verificarLibro(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from libros where ID_Libro = " + to_string(id) + ";";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    return true;
                }
                else
                {
                    return false;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return false;
    }

    // METODO PARA ACTUALIZAR LIBRO
    void actualizarLibro(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarLibro(id))
        {
            if (autor.verificarAutor(idAutor) && editorial.verificarEditorial(idEditorial) && categoria.verificarCategoria(idCategoria))
            {
                if (conn.getConnector())
                {
                    string lA = to_string(idAutor);
                    string lE = to_string(idEditorial);
                    string lC = to_string(idCategoria);
                    string lF = to_string(fecha);
                    string sql = "update libros set Titulo ='" + titulo + "', ID_Autor ='" + lA + "', ID_Editorial ='" + lE + "', ID_Categoria ='" + lC + "', Idioma ='" + idioma + "', Fecha_Publicacion ='" + lF + "' where ID_Libro =" + to_string(id) + ";";
                    const char *c = sql.c_str();
                    state = mysql_query(conn.getConnector(), c);

                    if (!state)
                    {
                        system("color a");
                        cout << "\nLibro actualizado exitosamente!" << endl;
                    }
                    else
                    {
                        system("color c");
                        cout << "\nError, vuelvalo a intentar..." << endl;
                    }
                }
            }
            else
            {
                cout << "\nFavor verificar que los IDs de Autor, Editorial, Categoria ingresados sean validos" << endl;
            }
        }
        else
        {
            cout << "\nNo se encontro libro con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR LIBRO
    void eliminarLibro(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarLibro(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from libros where ID_Libro =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nLibro eliminado exitosamente!" << endl;
                }
                else
                {
                    system("color c");
                    cout << "Error, vuelvalo a intentar..." << endl;
                }
            }
        }
        else
        {
            cout << "\nNo se encontro libro con dicho ID" << endl;
        }
        conn.close_connection();
    }

    void menuLibro()
    {
        int subOpcion, subO, idLibro, idAutor, idEditorial, idCategoria, fecha;
        string titulo, idioma, autor, editorial, categoria;
        Libro libro;

        do
        {
            cout << "\nSubmenu Libro:\n";
            cout << "1. Agregar Libro\n";
            cout << "2. Consultar Libro\n";
            cout << "3. Mostrar Todos los Libro\n";
            cout << "4. Eliminar Libro\n";
            cout << "5. Actualizar Libro\n";
            cout << "6. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nTitulo Libro: ";
                getline(cin, titulo);
                getline(cin, titulo);

                cout << "\nNo Recuerdas el ID del Autor? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarAutor();

                cout << "\nID Autor: ";
                cin >> idAutor;

                cout << "\nNo Recuerdas el ID de la Editorial? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarEditorial();

                cout << "\nID Editorial: ";
                cin >> idEditorial;

                cout << "\nNo Recuerdas el ID de la Categoria? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarCategoria();

                cout << "\nID Categoria: ";
                cin >> idCategoria;
                cout << "Idioma Libro: ";
                getline(cin, idioma);
                getline(cin, idioma);
                cout << "Fecha Publicacion: ";
                cin >> fecha;

                libro = Libro(idAutor, idEditorial, idCategoria, fecha, titulo, idioma);
                libro.agregarLibro();
            }
            else if (subOpcion == 2)
            {
                cout << "\n1.Consultar por ID\n";
                cout << "2.Consultar por Titulo\n";
                cout << "3.Consultar por Autor\n";
                cout << "4.Consultar por Editorial\n";
                cout << "5.Consultar por Categoria\n";
                cout << "6.Consultar por Fecha Publicacion\n";
                cout << "7.Volver\n";
                cout << "Selecciona una opcion: ";
                cin >> subO;

                do 
                {
                    if (subO == 1)
                    {
                        cout << "\nID Libro a Consultar: ";
                        cin >> idLibro;
                        libro.mostrarLibroPorId(idLibro);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nTitulo Libro a Consultar: ";
                        getline(cin, titulo);
                        getline(cin, titulo);
                        libro.mostrarLibroPorTitulo(titulo);
                        break;
                    }
                    else if (subO == 3)
                    {
                        cout << "\nAutor Libro a Consultar: ";
                        getline(cin, autor);
                        getline(cin, autor);
                        libro.mostrarLibroPorAutor(autor);
                        break;
                    }
                    else if (subO == 4)
                    {
                        cout << "\nEditorial Libro a Consultar: ";
                        getline(cin, editorial);
                        getline(cin, editorial);
                        libro.mostrarLibroPorEditorial(editorial);
                        break;
                    }
                    else if (subO == 5)
                    {
                        cout << "\nCategoria Libro a Consultar: ";
                        getline(cin, categoria);
                        getline(cin, categoria);
                        libro.mostrarLibroPorCategoria(categoria);
                        break;
                    }
                    else if (subO == 6)
                    {
                        cout << "\nFecha Publicacion Libro a Consultar: ";
                        cin >> fecha;
                        libro.mostrarLibroPorFecha(fecha);
                        break;
                    }
                    else 
                    {
                        cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                        break;
                    }

                } while (subO != 7);
            }
            else if (subOpcion == 3)
            {
                cout << endl;
                libro.mostrarLibros();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Libro a eliminar: ";
                cin >> idLibro;
                cin.ignore();
                libro.eliminarLibro(idLibro);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Libro a modificar: ";
                cin >> idLibro;
                cin.ignore();

                cout << "\nNuevo Titulo Libro: ";
                getline(cin, titulo);

                cout << "\nNo Recuerdas el ID del Autor? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarAutor();

                cout << "\nNuevo ID Autor: ";
                cin >> idAutor;

                cout << "\nNo Recuerdas el ID de la Editorial? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarEditorial();

                cout << "\nNuevo ID Editorial: ";
                cin >> idEditorial;

                cout << "\nNo Recuerdas el ID de la Categoria? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                libro.verificarCategoria();

                cout << "\nNuevo ID Categoria: ";
                cin >> idCategoria;
                cout << "Nuevo Idioma Libro: ";
                getline(cin, idioma);
                getline(cin, idioma);
                cout << "Nueva Fecha Publicacion: ";
                cin >> fecha;

                libro = Libro(idAutor, idEditorial, idCategoria, fecha, titulo, idioma);
                libro.actualizarLibro(idLibro);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }

    // METODO PARA BUSCAR AUTOR
    void verificarAutor()
    {
        int op;
        bool bandera = false;
        string nombre, nacionalidad;
        autor = Autor();

        while (!bandera)
        {
            cout << "\n1.Consultar por Nombre\n";
            cout << "2.Consultar por Nacionalidad\n";
            cout << "Selecciona una opcion: ";
            cin >> op;

            if (op == 1)
            {
                cout << "\nNombre Autor a Consultar: ";
                getline(cin, nombre);
                getline(cin, nombre);
                if (!autor.mostrarAutorPorNombre(nombre))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else if (op == 2)
            {
                cout << "\nNacionalidad Autor a Consultar: ";
                getline(cin, nacionalidad);
                getline(cin, nacionalidad);
                if (!autor.mostrarAutorPorNacionalidad(nacionalidad))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                bandera = false;
            }
        }
    }

    // METODO PARA BUSCAR EDITORIAL
    void verificarEditorial()
    {
        bool bandera = false;
        string nombre;
        editorial = Editorial();

        while (!bandera)
        {
            cout << "\nConsultar Nombre Editorial: ";
            getline(cin, nombre);
            getline(cin, nombre);

            if (!editorial.mostrarEditorialPorNombre(nombre))
            {
                bandera = false;
            }
            else
            {
                bandera = true;
            }
        }
    }

    // METODO PARA BUSCAR CATEGORIA
    void verificarCategoria()
    {
        bool bandera = false;
        string nombre;
        categoria = Categoria();

        while (!bandera)
        {
            cout << "\nConsultar Nombre Categoria: ";
            getline(cin, nombre);
            getline(cin, nombre);

            if (!categoria.mostrarCategoriaPorNombre(nombre))
            {
                bandera = false;
            }
            else
            {
                bandera = true;
            }
        }
    }
};