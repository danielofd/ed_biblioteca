#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Autor
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idAutor;
    string nombreAutor, nacionalidad;
    int state = 0;

    Autor() {}

    Autor(string n, string m)
        : nombreAutor(n), nacionalidad(m) {}

    // METODO PARA AGREGAR AUTOR
    void agregarAutor()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "insert into autores (Nombre_Autor, Nacionalidad_A) values ('" + nombreAutor + "','" + nacionalidad + "');";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                system("color a");
                cout << "\nAutor registrado exitosamente!" << endl;
            }
            else
            {
                system("color c");
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR AUTORES
    void mostrarAutores()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Autores-------------------------" << endl;

            string sql = "select * from autores;";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                while (row = mysql_fetch_row(res))
                {
                    cout << row[0] << ", " << row[1] << ", " << row[2] << endl;
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

    // METODO PARA MOSTRAR AUTOR POR ID
    void mostrarAutorPorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from autores where ID_Autor = " + to_string(id) + ";";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\nID_Autor: " << row[0] << ", Nombre_Autor: " << row[1] << ", Nacionalidad: " << row[2] << endl;
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

    // METODO PARA MOSTRAR AUTOR POR NOMBRE
    bool mostrarAutorPorNombre(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = "select * from autores where Nombre_Autor like '%" + nombre + "%';";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n"
                             << row[0] << ", " << row[1] << ", " << row[2];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Nombre = " << nombre << endl;
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

    // METODO PARA MOSTRAR AUTOR POR NACIONALIDAD
    bool mostrarAutorPorNacionalidad(string nacionalidad)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = "select * from autores where Nacionalidad_A like '%" + nacionalidad + "%';";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n"
                             << row[0] << ", " << row[1] << ", " << row[2];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Nacionalidad = " << nacionalidad << endl;
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

    // METODO PARA VERIFICAR SI EXISTE AUTOR POR ID
    bool verificarAutor(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from autores where ID_Autor = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR AUTOR
    void actualizarAutor(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarAutor(id))
        {
            if (conn.getConnector())
            {
                string sql = "update autores set Nombre_Autor ='" + nombreAutor + "', Nacionalidad_A ='" + nacionalidad + "' where ID_Autor =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nAutor actualizado exitosamente!" << endl;
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
            cout << "\nNo se encontro autor con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR AUTOR
    void eliminarAutor(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarAutor(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from autores where ID_Autor =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nAutor eliminado exitosamente!" << endl;
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
            cout << "\nNo se encontro autor con dicho ID" << endl;
        }
        conn.close_connection();
    }

    void menuAutor()
    {
        int subOpcion, subO;
        int idAutor;
        string nombreAutor, nacionalidad;
        Autor autor;

        do
        {
            cout << "\nSubmenu Autor:\n";
            cout << "1. Agregar Autor\n";
            cout << "2. Consultar Autor\n";
            cout << "3. Mostrar Todos los Autores\n";
            cout << "4. Eliminar Autor\n";
            cout << "5. Actualizar Autor\n";
            cout << "6. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nNombre Autor: ";
                getline(cin, nombreAutor);
                getline(cin, nombreAutor);
                cout << "Nacionalidad: ";
                getline(cin, nacionalidad); // Esto es para evitar el bucle infinito...
                autor = Autor(nombreAutor, nacionalidad);
                autor.agregarAutor();
            }
            else if (subOpcion == 2)
            {
                cout << "\n1.Consultar por ID\n";
                cout << "2.Consultar por Nombre\n";
                cout << "3.Consultar por Nacionalidad\n";
                cout << "4.Volver\n";
                cout << "Selecciona una opcion: ";
                cin >> subO;

                do
                {
                    if (subO == 1)
                    {
                        cout << "\nID Autor a Consultar: ";
                        cin >> idAutor;
                        autor.mostrarAutorPorId(idAutor);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Autor a Consultar: ";
                        getline(cin, nombreAutor);
                        getline(cin, nombreAutor);
                        autor.mostrarAutorPorNombre(nombreAutor);
                        break;
                    }
                    else if (subO == 3)
                    {
                        cout << "\nNacionalidad Autor a Consultar: ";
                        getline(cin, nacionalidad);
                        getline(cin, nacionalidad);
                        autor.mostrarAutorPorNacionalidad(nacionalidad);
                        break;
                    }
                    else
                    {
                        cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                        break;
                    }

                } while (subO != 4);
            }
            else if (subOpcion == 3)
            {
                cout << endl;
                autor.mostrarAutores();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Autor a eliminar: ";
                cin >> idAutor;
                cin.ignore();
                autor.eliminarAutor(idAutor);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Autor a modificar: ";
                cin >> idAutor;
                cin.ignore();
                cout << "Nombre Nuevo de Autor: ";
                getline(cin, nombreAutor);
                cout << "Nacionalidad Nueva de Autor: ";
                getline(cin, nacionalidad);
                autor = Autor(nombreAutor, nacionalidad);
                autor.actualizarAutor(idAutor);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }
};
