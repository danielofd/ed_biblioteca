#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Login
{
public:
    string user, pass;
    char caracter;

    // INICIO DE SESION
    int iniciarSesion(string usuario, string password)
    {
        int state = 0;
        ConexionDB conn = ConexionDB();
        MYSQL_ROW row;
        MYSQL_RES *res;

        conn.open_connection();

        if (conn.getConnector())
        {
            string sql = "select * from usuarios where Nombre_Usuario = '" + usuario + "' and Contra = '" + password + "';";
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
        else
        {
            system("color c");
            cout << "Error..." << endl;
            return 0;
        }
        conn.close_connection();
        return 0;
    }

    bool mostrarLogin()
    {
        cout << "\n------------------Login------------------\n";
        cout << "Ingrese el nombre de usuario: ";
        cin >> user;
        cout << "Ingrese la contrasena: ";

        // Todo lo que esta dentro del bucle while es para ocultar la contraseña con un asterisco *
        caracter = getch();
        pass = "";
        while (caracter != 13) // El numero 13 representa la tecla ENTER
        {
            if (caracter != 8) // El numero 8 representa la tecla BACKSPACE
            {
                pass.push_back(caracter);
                cout << "*";
            }
            else
            {
                if (pass.length() > 0) // Este bloque sirve para borrar caracteres en caso de equivocarse en la contraseña
                {
                    cout << "\b \b";
                    pass.pop_back();
                }
            }
            caracter = getch();
        }

        if (iniciarSesion(user, pass) == 1)
        {
            cout << "\nExito" << endl;
            system("cls");
            return true;
        }
        else 
        {
            cout << "\nVuelva a intentarlo" << endl;
            return false;
        }
    }
};