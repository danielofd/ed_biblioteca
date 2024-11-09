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
    void mostrarCarrera()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Carreras Disponibles-------------------------" << endl;

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
                    cout << "\nNo se encontro ninguna carrera con ID = " << id << endl;
                    return 0;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return 0;
    }

    // METODO PARA VERIFICAR SI EXISTE CARRERA POR ID
    int verificarCarrera(int id)
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
                    return 1;
                }
                else
                {
                    return 0;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return 0;
    }

    // METODO PARA ACTUALIZAR CARRERA
    void actualizarCarrera(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

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
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR CARRERA
    void eliminarCarrera(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

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
        conn.close_connection();
    }
};