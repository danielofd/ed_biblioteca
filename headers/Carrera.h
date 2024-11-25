#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Carrera
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idCarrera;
    string nombreCarrera;
    int state = 0;

    Carrera() {}

    Carrera(string n)
        : nombreCarrera(n) {}

    // METODO PARA AGREGAR CARRERA
    void agregarCarrera()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "insert into carreras (Nombre_Carrera) values ('" + nombreCarrera + "');";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                system("color a");
                cout << "\nCarrera registrada exitosamente!" << endl;
            }
            else
            {
                system("color c");
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR CARRERA
    void mostrarCarreras()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Carreras-------------------------" << endl;

            string sql = "select * from carreras;";
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

    // METODO PARA MOSTRAR CARRERA POR ID
    int mostrarCarreraPorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from carreras where ID_Carrera = " + to_string(id) + ";";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\nID_Carrera: " << row[0] << ", Nombre_Carrera: " << row[1] << endl;
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

    // METODO PARA MOSTRAR CARRERA POR NOMBRE DE CARRERA
    int mostrarCarreraPorNombre(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from carreras where Nombre_Carrera like '%" + nombre + "%';";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    bool found = false;
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
        return 0;
    }

    // METODO PARA VERIFICAR SI EXISTE CARRERA POR ID
    bool verificarCarrera(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from carreras where ID_Carrera = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR CARRERA
    void actualizarCarrera(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarCarrera(id))
        {
            if (conn.getConnector())
            {
                string sql = "update carreras set Nombre_Carrera ='" + nombreCarrera + "' where ID_Carrera =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nCarrera actualizada exitosamente!" << endl;
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
            cout << "\nNo se encontro carrera con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR CARRERA
    void eliminarCarrera(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarCarrera(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from carreras where ID_Carrera =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nCarrera eliminada exitosamente!" << endl;
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
            cout << "\nNo se encontro carrera con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // ESTE ES EL MENU DE CARRERAS
    void menuCarrera()
    {
        int subOpcion, subO;
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
                cout << "\nNombre Carrera: ";
                getline(cin, nombreCarrera);
                getline(cin, nombreCarrera); // Esto es para evitar el bucle infinito...
                carrera = Carrera(nombreCarrera);
                carrera.agregarCarrera();
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
                        cout << "\nID Carrera a Consultar: ";
                        cin >> idCarrera;
                        carrera.mostrarCarreraPorId(idCarrera);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Carrera a Consultar: ";
                        getline(cin, nombreCarrera);
                        getline(cin, nombreCarrera);
                        carrera.mostrarCarreraPorNombre(nombreCarrera);
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
                carrera.mostrarCarreras();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Carrera a eliminar: ";
                cin >> idCarrera;
                cin.ignore();
                carrera.eliminarCarrera(idCarrera);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Carrera a modificar: ";
                cin >> idCarrera;
                cin.ignore();
                cout << "Nombre Nuevo de Carrera: ";
                getline(cin, nombreCarrera);
                carrera = Carrera(nombreCarrera);
                carrera.actualizarCarrera(idCarrera);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }
};