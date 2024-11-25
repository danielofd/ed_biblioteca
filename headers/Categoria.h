#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Categoria
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idCategoria;
    string nombreCategoria;
    int state = 0;

    Categoria() {}

    Categoria(string n)
        : nombreCategoria(n) {}

    // METODO PARA AGREGAR CATEGORIA
    void agregarCategoria()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "insert into categorias (Nombre_Categoria) values ('" + nombreCategoria + "');";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                system("color a");
                cout << "\nCategoria registrada exitosamente!" << endl;
            }
            else
            {
                system("color c");
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR CATEGORIAS
    void mostrarCategorias()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Categorias-------------------------" << endl;

            string sql = "select * from categorias;";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                while (row = mysql_fetch_row(res))
                {
                    cout << row[0] << ", " << row[1] << endl;
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

    // METODO PARA MOSTRAR CATEGORIA POR ID
    int mostrarCategoriaPorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from categorias where ID_Categoria = " + to_string(id) + ";";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\nID_Cateogoria: " << row[0] << ", Nombre_Categoria: " << row[1] << endl;
                    return 1;
                }
                else
                {
                    cout << "\nNo se encontro ningun registro con ID = " << id << endl;
                    return 0;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return 0;
    }

    // METODO PARA MOSTRAR CATEGORIA POR NOMBRE
    bool mostrarCategoriaPorNombre(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = "select * from categorias where Nombre_Categoria like '%" + nombre + "%';";
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
                             << row[0] << ", " << row[1];
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

    // METODO PARA VERIFICAR SI EXISTE CATEGORIA POR ID
    bool verificarCategoria(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from categorias where ID_Categoria = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR CATEGORIA
    void actualizarCategoria(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarCategoria(id))
        {
            if (conn.getConnector())
            {
                string sql = "update categorias set Nombre_Categoria ='" + nombreCategoria + "' where ID_Categoria =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nCategoria actualizada exitosamente!" << endl;
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
            cout << "\nNo se encontro categoria con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR CATEGORIA
    void eliminarCategoria(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarCategoria(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from categorias where ID_Categoria =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nCategoria eliminada exitosamente!" << endl;
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
            cout << "\nNo se encontro categoria con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // ESTE ES EL MENU DE CATEGORIA
    void menuCategoria()
    {
        int subOpcion, subO;
        int idCategoria;
        string nombreCategoria;
        Categoria categoria;

        do
        {
            cout << "\nSubmenu Categoria:\n";
            cout << "1. Agregar Categoria\n";
            cout << "2. Consultar Categoria\n";
            cout << "3. Mostrar Todas las Categorias\n";
            cout << "4. Eliminar Categoria\n";
            cout << "5. Actualizar Categoria\n";
            cout << "6. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nNombre Categoria: ";
                getline(cin, nombreCategoria);
                getline(cin, nombreCategoria); // Esto es para evitar el bucle infinito...
                categoria = Categoria(nombreCategoria);
                categoria.agregarCategoria();
            }
            else if (subOpcion == 2)
            {
                cout << "\n1.Consultar por ID\n";
                cout << "2.Consultar por Nombre\n";
                cout << "3.Volver\n";
                cout << "Selecciona una opcion: ";
                cin >> subO;

                do
                {
                    if (subO == 1)
                    {
                        cout << "\nID Categoria a Consultar: ";
                        cin >> idCategoria;
                        categoria.mostrarCategoriaPorId(idCategoria);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Categoria a Consultar: ";
                        getline(cin, nombreCategoria);
                        getline(cin, nombreCategoria);
                        categoria.mostrarCategoriaPorNombre(nombreCategoria);
                        break;
                    }
                    else
                    {
                        cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                        break;
                    }

                } while (subO != 3);
            }
            else if (subOpcion == 3)
            {
                cout << endl;
                categoria.mostrarCategorias();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Categoria a eliminar: ";
                cin >> idCategoria;
                cin.ignore();
                categoria.eliminarCategoria(idCategoria);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Categoria a modificar: ";
                cin >> idCategoria;
                cin.ignore();
                cout << "Nombre Nuevo de Categoria: ";
                getline(cin, nombreCategoria);
                categoria = Categoria(nombreCategoria);
                categoria.actualizarCategoria(idCategoria);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }
};