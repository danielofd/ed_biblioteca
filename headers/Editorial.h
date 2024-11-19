#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Editorial
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idEditorial;
    string nombreEditorial;
    int state = 0;

    Editorial() {}

    Editorial(string n)
        : nombreEditorial(n) {}

    // METODO PARA AGREGAR EDITORIAL
    void agregarEditorial()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "insert into editoriales (Nombre_Editorial) values ('" + nombreEditorial + "');";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                system("color a");
                cout << "\nEditorial registrada exitosamente!" << endl;
            }
            else
            {
                system("color c");
                cout << "Error, vuelvalo a intentar..." << endl;
            }
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR EDITORIALES
    void mostrarEditoriales()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Editoriales-------------------------" << endl;

            string sql = "select * from editoriales;";
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

    // METODO PARA MOSTRAR EDITORIAL POR ID
    int mostrarEditorialPorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from editoriales where ID_Editorial = " + to_string(id) + ";";
            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\nID_Editorial: " << row[0] << ", Nombre_Editorial: " << row[1] << endl;
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

    // METODO PARA MOSTRAR EDITORIAL POR NOMBRE
    int mostrarEditorialPorNombre(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from editoriales where Nombre_Editorial like '%" + nombre + "%';";
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
                        cout << "\nNo se encontro ningun registro con Nombre = " << nombre << endl;
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

    // METODO PARA VERIFICAR SI EXISTE EDITORIAL POR ID
    bool verificarEditorial(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from editoriales where ID_Editorial = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR EDITORIAL
    void actualizarEditorial(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarEditorial(id))
        {
            if (conn.getConnector())
            {
                string sql = "update editoriales set Nombre_Editorial ='" + nombreEditorial + "' where ID_Editorial =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nEditorial actualizada exitosamente!" << endl;
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
            cout << "\nNo se encontro editorial con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR EDITORIAL
    void eliminarEditorial(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarEditorial(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from editoriales where ID_Editorial =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nEditorial eliminada exitosamente!" << endl;
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
            cout << "\nNo se encontro editorial con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // ESTE ES EL MENU DE EDITORIAL
    void menuEditorial()
    {
        int subOpcion, subO;
        int idEditorial;
        string nombreEditorial;
        Editorial editorial;

        do
        {
            cout << "\nSubmenu Editorial:\n";
            cout << "1. Agregar Editorial\n";
            cout << "2. Consultar Editorial\n";
            cout << "3. Mostrar Todas las Editoriales\n";
            cout << "4. Eliminar Editorial\n";
            cout << "5. Actualizar Editorial\n";
            cout << "6. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nNombre Editorial: ";
                getline(cin, nombreEditorial);
                getline(cin, nombreEditorial); // Esto es para evitar el bucle infinito...
                editorial = Editorial(nombreEditorial);
                editorial.agregarEditorial();
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
                        cout << "\nID Editorial a Consultar: ";
                        cin >> idEditorial;
                        editorial.mostrarEditorialPorId(idEditorial);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Editorial a Consultar: ";
                        getline(cin, nombreEditorial);
                        getline(cin, nombreEditorial);
                        editorial.mostrarEditorialPorNombre(nombreEditorial);
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
                editorial.mostrarEditoriales();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Editorial a eliminar: ";
                cin >> idEditorial;
                cin.ignore();
                editorial.eliminarEditorial(idEditorial);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Editorial a modificar: ";
                cin >> idEditorial;
                cin.ignore();
                cout << "Nombre Nuevo de Editorial: ";
                getline(cin, nombreEditorial);
                editorial = Editorial(nombreEditorial);
                editorial.actualizarEditorial(idEditorial);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }
};