#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"
#include "Carrera.h"

using namespace std;

class Estudiante
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idEstudiante, idCarrera, telefono, estado;
    string nombreEstudiante, email;
    Carrera carrera;
    int state = 0;

    Estudiante() {}

    Estudiante(int x, int y, int z, string m, string n)
        : idCarrera(x), telefono(y), estado(z), nombreEstudiante(m), email(n) {}

    // METODO PARA AGREGAR ESTUDIANTE
    void agregarEstudiante()
    {
        conn = ConexionDB();
        conn.open_connection();
        carrera = Carrera();

        if (carrera.verificarCarrera(idCarrera))
        {
            if (conn.getConnector())
            {
                string ic = to_string(idCarrera);
                string t = to_string(telefono);
                string e = to_string(estado);
                string sql = "insert into estudiantes (Nombre_Estudiante, ID_Carrera, Email_Estudiante, Tel_Estudiante, Estado_Estudiante) values ('" + nombreEstudiante + "','" + ic + "','" + email + "','" + t + "','" + e + "');";
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
            cout << "\nEl ID Carrera ingresado no existe" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR ESTUDIANTE
    void mostrarEstudiantes()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Estudiante-------------------------" << endl;

            string sql = string("select e.ID_Estudiante, e.Nombre_Estudiante, c.Nombre_Carrera,") 
                             + ("e.Email_Estudiante, e.Tel_Estudiante, e.Estado_Estudiante from estudiantes as e ") 
                             + ("inner join carreras as c on e.ID_Carrera = c.ID_Carrera;");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);

            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                while (row = mysql_fetch_row(res))
                {
                    cout << row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << endl;
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

    // METODO PARA MOSTRAR ESTUDIANTE POR ID
    void mostrarEstudiantePorId(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = string("select e.ID_Estudiante, e.Nombre_Estudiante, c.Nombre_Carrera, e.Email_Estudiante, ") 
                             + ("e.Tel_Estudiante, e.Estado_Estudiante from estudiantes as e ") 
                             + ("inner join carreras as c on e.ID_Carrera = c.ID_Carrera where e.ID_Estudiante = " + to_string(id) + ";");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << endl;
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

    // METODO PARA MOSTRAR ESTUDIANTE POR NOMBRE
    bool mostrarEstudiantePorNombre(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select e.ID_Estudiante, e.Nombre_Estudiante, c.Nombre_Carrera, e.Email_Estudiante, ") 
                             + ("e.Tel_Estudiante, e.Estado_Estudiante from estudiantes as e ") 
                             + ("inner join carreras as c on e.ID_Carrera = c.ID_Carrera where e.Nombre_Estudiante like '%" + nombre + "%';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());

                if (res)
                {
                    while ((row = mysql_fetch_row(res)) != nullptr)
                    {
                        cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5];
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

    // METODO PARA MOSTRAR ESTUDIANTE POR EMAIL
    bool mostrarEstudiantePorEmail(string e)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select e.ID_Estudiante, e.Nombre_Estudiante, c.Nombre_Carrera, e.Email_Estudiante, ") 
                             + ("e.Tel_Estudiante, e.Estado_Estudiante from estudiantes as e ") 
                             + ("inner join carreras as c on e.ID_Carrera = c.ID_Carrera where e.Email_Estudiante = '" + e + "';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << endl;
                    found = true;
                }
                else
                {
                    cout << "\nNo se encontro ningun registro con Email = " << e << endl;
                    found = false;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA MOSTRAR ESTUDIANTE POR TELEFONO
    bool mostrarEstudiantePorTelefono(int tel)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select e.ID_Estudiante, e.Nombre_Estudiante, c.Nombre_Carrera, e.Email_Estudiante, ") 
                             + ("e.Tel_Estudiante, e.Estado_Estudiante from estudiantes as e ") 
                             + ("inner join carreras as c on e.ID_Carrera = c.ID_Carrera where e.Tel_Estudiante = '" + to_string(tel) + "';");

            const char *c = sql.c_str();
            state = mysql_query(conn.getConnector(), c);
            if (!state)
            {
                res = mysql_store_result(conn.getConnector());
                if ((row = mysql_fetch_row(res)) != nullptr)
                {
                    // Mostrar el registro encontrado
                    cout << "\n" <<row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5] << endl;
                    found = true;
                }
                else
                {
                    cout << "\nNo se encontro ningun registro con Email = " << tel << endl;
                    found = false;
                }
                // Liberar el resultado después de usarlo
                mysql_free_result(res);
            }
        }
        conn.close_connection();
        return found;
    }

    // METODO PARA VERIFICAR SI EXISTE ESTUDIANTE POR ID
    bool verificarEstudiante(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from estudiantes where ID_Estudiante = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR ESTUDIANTE
    void actualizarEstudiante(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarEstudiante(id))
        {
            if (carrera.verificarCarrera(idCarrera))
            {
                if (conn.getConnector())
                {
                    string ic = to_string(idCarrera);
                    string t = to_string(telefono);
                    string e = to_string(estado);
                    string sql = "update estudiantes set Nombre_Estudiante ='" + nombreEstudiante + "', ID_Carrera ='" + ic + "', Email_Estudiante ='" + email + "', Tel_Estudiante ='" + t + "', Estado_Estudiante ='" + e + "' where ID_Estudiante =" + to_string(id) + ";";
                    const char *c = sql.c_str();
                    state = mysql_query(conn.getConnector(), c);

                    if (!state)
                    {
                        system("color a");
                        cout << "\nEstudiante actualizado exitosamente!" << endl;
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
                cout << "\nEl ID Carrera ingresado no existe" << endl;
            }
        }
        else
        {
            cout << "\nNo se encontro estudiante con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR ESTUDIANTE
    void eliminarEstudiante(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarEstudiante(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from estudiantes where ID_Estudiante =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nEstudiante eliminado exitosamente!" << endl;
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
            cout << "\nNo se encontro estudiante con dicho ID" << endl;
        }
        conn.close_connection();
    }

    void menuEstudiante()
    {
        int subOpcion, subO, idEstudiante, idCarrera, telefono, estado;
        string nombreEstudiante, email;
        Estudiante estudiante;

        do
        {
            cout << "\nSubmenu Estudiante:\n";
            cout << "1. Agregar Estudiante\n";
            cout << "2. Consultar Estudiante\n";
            cout << "3. Mostrar Todos los Estudiantes\n";
            cout << "4. Eliminar Estudiante\n";
            cout << "5. Actualizar Estudiante\n";
            cout << "6. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nNombre Estudiante: ";
                getline(cin, nombreEstudiante);
                getline(cin, nombreEstudiante);
                cout << "ID Carrera a Elegir: ";
                cin >> idCarrera;

                cout << "Telefono(Sin guion): ";
                cin >> telefono;
                cin.ignore();

                cout << "Email: ";
                getline(cin, email);

                cout << "Estado Estudiante: ";
                cout << "\n1 = Activo, 0 = Inactivo\n";
                cin >> estado;

                estudiante = Estudiante(idCarrera, telefono, estado, nombreEstudiante, email);
                estudiante.agregarEstudiante();
            }
            else if (subOpcion == 2)
            {
                cout << "\n1.Consultar por ID\n";
                cout << "2.Consultar por Nombre\n";
                cout << "3.Consultar por Email\n";
                cout << "4.Consultar por Telefono\n";
                cout << "5.Volver\n";
                cout << "Selecciona una opcion: ";
                cin >> subO;

                do
                {
                    if (subO == 1)
                    {
                        cout << "\nID Estudiante a Consultar: ";
                        cin >> idEstudiante;
                        estudiante.mostrarEstudiantePorId(idEstudiante);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Estudiante a Consultar: ";
                        getline(cin, nombreEstudiante);
                        getline(cin, nombreEstudiante);
                        estudiante.mostrarEstudiantePorNombre(nombreEstudiante);
                        break;
                    }
                    else if (subO == 3)
                    {
                        cout << "\nEmail Estudiante a Consultar: ";
                        getline(cin, email);
                        getline(cin, email);
                        estudiante.mostrarEstudiantePorEmail(email);
                        break;
                    }
                    else if (subO == 4)
                    {
                        cout << "\nTelefono Estudiante a Consultar(Sin guion): ";
                        cin >> telefono;
                        estudiante.mostrarEstudiantePorTelefono(telefono);
                        break;
                    }
                    else
                    {
                        cout << "\nOpcion no valida. Intentalo de nuevo.\n";
                        break;
                    }

                } while (subO != 5);
            }
            else if (subOpcion == 3)
            {
                cout << endl;
                estudiante.mostrarEstudiantes();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Estudiante a eliminar: ";
                cin >> idEstudiante;
                cin.ignore();
                estudiante.eliminarEstudiante(idEstudiante);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Estudiante a modificar: ";
                cin >> idEstudiante;
                cin.ignore();

                cout << "Nuevo Nombre Estudiante: ";
                getline(cin, nombreEstudiante);
                cout << "Nuevo ID Carrera a Elegir: ";
                cin >> idCarrera;

                cout << "Nuevo Telefono(Sin guion): ";
                cin >> telefono;
                cin.ignore();

                cout << "Nuevo Email: ";
                getline(cin, email);

                cout << "Nuevo Estado Estudiante: ";
                cout << "\n1 = Activo, 0 = Inactivo\n";
                cin >> estado;

                estudiante = Estudiante(idCarrera, telefono, estado, nombreEstudiante, email);
                estudiante.actualizarEstudiante(idEstudiante);
            }
            else if (subOpcion != 6)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 6);
    }
};