#include <iostream>
#include <string>
#include <mysql.h>
#include "ConexionDB.h"

using namespace std;

class Login
{
public:
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
};