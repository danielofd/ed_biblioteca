#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <mysql.h>
#include "ConexionDB.h"
#include "Libro.h"
#include "Estudiante.h"

using namespace std;

class Reserva
{
private:
    ConexionDB conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

public:
    int idReserva, idLibro, idEstudiante, estado;
    string reserva, devolucion;
    Libro libro;
    Estudiante estudiante;
    int state = 0;

    Reserva() {}

    Reserva(string de, int es)
        : devolucion(de), estado(es) {}

    Reserva(int il, int ie, string re, string de)
        : idLibro(il), idEstudiante(ie), reserva(re), devolucion(de) {}

    // METODO PARA REALIZAR RESERVA
    void realizarReserva()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (libro.verificarLibro(idLibro) && estudiante.verificarEstudiante(idEstudiante))
        {
            if (conn.getConnector())
            {
                string rL = to_string(idLibro);
                string rE = to_string(idEstudiante);
                string rEst = to_string(estado);
                string sql = "insert into reservas (ID_Libro, ID_Estudiante, Fecha_Reserva, Expiracion_Reserva) values ('" + rL + "','" + rE + "','" + reserva + "', '" + rEst + "');";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nReserva realizada exitosamente!" << endl;
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
            cout << "\nFavor verificar que los IDs de Libro y Estudiante ingresados sean validos" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA MOSTRAR RESERVA
    void mostrarReservas()
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            system("color a");
            cout << "-------------------------Listado de Reservas-------------------------" << endl;

            string sql = string("select re.ID_Reserva, li.Titulo, es.Nombre_Estudiante, re.Fecha_Reserva, ") + ("re.Expiracion_Reserva, re.Estado_Reserva from reservas as re ") + ("inner join libros as li on re.ID_Libro = li.ID_Libro ") + ("inner join estudiantes as es on re.ID_Estudiante = es.ID_Estudiante;");

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

    // METODO PARA MOSTRAR RESERVA POR TITULO
    bool mostrarReservaPorTitulo(string titulo)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select re.ID_Reserva, li.Titulo, es.Nombre_Estudiante, re.Fecha_Reserva, ") + ("re.Expiracion_Reserva, re.Estado_Reserva from reservas as re ") + ("inner join libros as li on re.ID_Libro = li.ID_Libro ") + ("inner join estudiantes as es on re.ID_Estudiante = es.ID_Estudiante where li.Titulo like '%" + titulo + "%';");

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
                             << row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5];
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

    // METODO PARA MOSTRAR RESERVA POR ESTUDIANTE
    bool mostrarReservaPorEstudiante(string nombre)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select re.ID_Reserva, li.Titulo, es.Nombre_Estudiante, re.Fecha_Reserva, ") + ("re.Expiracion_Reserva, re.Estado_Reserva from reservas as re ") + ("inner join libros as li on re.ID_Libro = li.ID_Libro ") + ("inner join estudiantes as es on re.ID_Estudiante = es.ID_Estudiante where es.Nombre_Estudiante like '%" + nombre + "%';");

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
                             << row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5];
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

    // METODO PARA MOSTRAR RESERVA POR FECHA
    bool mostrarReservaPorFecha(string fecha)
    {
        conn = ConexionDB();
        conn.open_connection();
        bool found = false;

        if (conn.getConnector())
        {
            string sql = string("select re.ID_Reserva, li.Titulo, es.Nombre_Estudiante, re.Fecha_Reserva, ") + ("re.Expiracion_Reserva, re.Estado_Reserva from reservas as re ") + ("inner join libros as li on re.ID_Libro = li.ID_Libro ") + ("inner join estudiantes as es on re.ID_Estudiante = es.ID_Estudiante where re.Fecha_Reserva like '%" + fecha + "%';");

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
                             << row[0] << " || " << row[1] << " || " << row[2] << " || " << row[3] << " || " << row[4] << " || " << row[5];
                        found = true;
                    }
                    cout << endl;
                    if (!found)
                    {
                        cout << "No se encontro ningun registro con Fecha = " << fecha << endl;
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

    // METODO PARA VERIFICAR SI EXISTE RESERVA POR ID
    bool verificarReserva(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from reservas where ID_Reserva = " + to_string(id) + ";";
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

    // METODO PARA ACTUALIZAR RESERVA
    void actualizarReserva(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarReserva(id))
        {
            if (libro.verificarLibro(idLibro) && estudiante.verificarEstudiante(idEstudiante))
            {
                if (conn.getConnector())
                {
                    string rL = to_string(idLibro);
                    string rE = to_string(idEstudiante);
                    string rEst = to_string(estado);
                    string sql = "update reservas set ID_Libro ='" + rL + "', ID_Estudiante ='" + rE + "', Fecha_Reserva ='" + reserva + "' where ID_Reserva =" + to_string(id) + ";";
                    const char *c = sql.c_str();
                    state = mysql_query(conn.getConnector(), c);

                    if (!state)
                    {
                        system("color a");
                        cout << "\nReserva actualizada exitosamente!" << endl;
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
                cout << "\nFavor verificar que los IDs de Libro, Estudiante ingresados sean validos" << endl;
            }
        }
        else
        {
            cout << "\nNo se encontro reserva con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA DEVOLVER RESERVA
    void devolverReserva(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarReserva(id))
        {
            if (conn.getConnector())
            {
                string rEst = to_string(estado);
                string sql = "update reservas set Expiracion_Reserva ='" + devolucion + "', Estado_Reserva ='" + rEst + "' where ID_Reserva =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nDevolucion exitosa!" << endl;
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
            cout << "\nNo se encontro reserva con dicho ID" << endl;
        }
        conn.close_connection();
    }

    // METODO PARA ELIMININAR RESERVA
    void eliminarReserva(int id)
    {
        conn = ConexionDB();
        conn.open_connection();

        if (verificarReserva(id))
        {
            if (conn.getConnector())
            {
                string sql = "delete from reservas where ID_Reserva =" + to_string(id) + ";";
                const char *c = sql.c_str();
                state = mysql_query(conn.getConnector(), c);

                if (!state)
                {
                    system("color a");
                    cout << "\nReserva eliminada exitosamente!" << endl;
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
            cout << "\nNo se encontro reserva con dicho ID" << endl;
        }
        conn.close_connection();
    }

    void menuReserva()
    {
        int subOpcion, subO, idLibro, idEstudiante, estado;
        string fecha, devolucion, titulo, nombre, f;
        Reserva reserva;

        do
        {
            cout << "\nSubmenu Reserva:\n";
            cout << "1. Realizar Reserva\n";
            cout << "2. Consultar Reserva\n";
            cout << "3. Mostrar Todas las Reservas\n";
            cout << "4. Eliminar Reserva\n";
            cout << "5. Actualizar Reserva\n";
            cout << "6. Devolver Reserva\n";
            cout << "7. Volver\n";
            cout << "Selecciona una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1)
            {
                cout << "\nNo Recuerdas el ID del Libro? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                reserva.verificarLibro();

                cout << "\nID Libro: ";
                cin >> idLibro;

                cout << "\nNo Recuerdas el ID del Estudiante? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                reserva.verificarEstudiante();

                cout << "\nID Estudiante: ";
                cin >> idEstudiante;

                fecha = reserva.obtenerFecha();
                devolucion = "0001-01-01";

                reserva = Reserva(idLibro, idEstudiante, fecha, devolucion);
                reserva.realizarReserva();
            }
            else if (subOpcion == 2)
            {
                cout << "\n1.Consultar por Titulo\n";
                cout << "2.Consultar por Nombre Estudiante\n";
                cout << "3.Consultar por Fecha Reserva\n";
                cout << "4.Volver\n";
                cout << "Selecciona una opcion: ";
                cin >> subO;

                do
                {
                    if (subO == 1)
                    {
                        cout << "\nTitulo Libro Reservado a Consultar: ";
                        getline(cin, titulo);
                        getline(cin, titulo);
                        reserva.mostrarReservaPorTitulo(titulo);
                        break;
                    }
                    else if (subO == 2)
                    {
                        cout << "\nNombre Estudiante Reserva a Consultar: ";
                        getline(cin, nombre);
                        getline(cin, nombre);
                        reserva.mostrarReservaPorEstudiante(nombre);
                        break;
                    }
                    else if (subO == 3)
                    {
                        cout << "\nFecha Reserva a Consultar: ";
                        getline(cin, f);
                        getline(cin, f);
                        reserva.mostrarReservaPorFecha(f);
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
                reserva.mostrarReservas();
            }
            else if (subOpcion == 4)
            {
                cout << "\nID Reserva a eliminar: ";
                cin >> idReserva;
                cin.ignore();
                reserva.eliminarReserva(idReserva);
            }
            else if (subOpcion == 5)
            {
                cout << "\nID Reserva a modificar: ";
                cin >> idReserva;
                cin.ignore();

                cout << "\nNo Recuerdas el ID del Libro? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                reserva.verificarLibro();

                cout << "\nNuevo ID Libro: ";
                cin >> idLibro;

                cout << "\nNo Recuerdas el ID del Estudiante? Estas Opciones Te Pueden Ayudar a Buscarlo.\n";
                reserva.verificarEstudiante();

                cout << "\nNuevo ID Estudiante: ";
                cin >> idEstudiante;

                fecha = reserva.obtenerFecha();
                devolucion = "0001-01-01";

                reserva = Reserva(idLibro, idEstudiante, fecha, devolucion);
                reserva.actualizarReserva(idReserva);
            }
            else if (subOpcion == 6)
            {
                cout << "\nID Reserva a devolver: ";
                cin >> idReserva;
                cin.ignore();

                fecha = reserva.obtenerFecha();
                estado = 0;

                reserva = Reserva(fecha, estado);
                reserva.devolverReserva(idReserva);

            }
            else if (subOpcion != 7)
            {
                cout << "\nOpcion no valida. Intentalo de nuevo.\n";
            }

        } while (subOpcion != 7);
    }

    // METODO PARA OBTENER LA FECHA ACTUAL
    string obtenerFecha()
    {
        time_t now = time(nullptr);
        tm *now_tm = localtime(&now);
        ostringstream oss;
        oss << put_time(now_tm, "%Y-%m-%d");
        string ol = oss.str();
        return ol;
    }

    void verificarLibro()
    {
        int op, fecha;
        bool bandera = false;
        string titulo, autor, editorial, categoria;
        libro = Libro();

        while (!bandera)
        {
            cout << "\n1.Consultar por Titulo\n";
            cout << "2.Consultar por Autor\n";
            cout << "3.Consultar por Editorial\n";
            cout << "4.Consultar por Categoria\n";
            cout << "5.Consultar por Fecha Publicacion\n";
            cout << "Selecciona una opcion: ";
            cin >> op;

            if (op == 1)
            {
                cout << "\nTitulo Libro a Consultar: ";
                getline(cin, titulo);
                getline(cin, titulo);
                if (!libro.mostrarLibroPorTitulo(titulo))
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
                cout << "\nNombre Autor Libro a Consultar: ";
                getline(cin, autor);
                getline(cin, autor);
                if (!libro.mostrarLibroPorAutor(autor))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else if (op == 3)
            {
                cout << "\nNombre Editorial Libro a Consultar: ";
                getline(cin, editorial);
                getline(cin, editorial);
                if (!libro.mostrarLibroPorEditorial(editorial))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else if (op == 4)
            {
                cout << "\nNombre Categoria Libro a Consultar: ";
                getline(cin, categoria);
                getline(cin, categoria);
                if (!libro.mostrarLibroPorCategoria(categoria))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else if (op == 5)
            {
                cout << "\nFecha Libro a Consultar: ";
                cin >> fecha;
                if (!libro.mostrarLibroPorFecha(fecha))
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

    void verificarEstudiante()
    {
        int op, telefono;
        string nombre, email;
        bool bandera = false;
        estudiante = Estudiante();

        while (!bandera)
        {
            cout << "\n1.Consultar Estudiante por Nombre\n";
            cout << "2.Consultar Estudiante por Email\n";
            cout << "3.Consultar Estudiante por Telefono\n";
            cout << "Selecciona una opcion: ";
            cin >> op;

            if (op == 1)
            {
                cout << "\nNombre Estudiante a Consultar: ";
                getline(cin, nombre);
                getline(cin, nombre);
                if (!estudiante.mostrarEstudiantePorNombre(nombre))
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
                cout << "\nEmail Estudiante a Consultar: ";
                getline(cin, email);
                getline(cin, email);
                if (!estudiante.mostrarEstudiantePorEmail(email))
                {
                    bandera = false;
                }
                else
                {
                    bandera = true;
                }
            }
            else if (op == 3)
            {
                cout << "\nTelefono Estudiante a Consultar: ";
                cin >> telefono;
                if (!estudiante.mostrarEstudiantePorTelefono(telefono))
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
};