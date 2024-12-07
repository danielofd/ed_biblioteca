#pragma once
#include <iostream>
#include <mysql.h>

using namespace std;

class ConexionDB
{

private:
    MYSQL *connector;

public:
    void open_connection()
    {
        connector = mysql_init(0);
        connector = mysql_real_connect(connector, "localhost", "root", "r00t", "biblioteca", 0, NULL, 0);
    }

    MYSQL *getConnector()
    {
        return connector;
    }

    void close_connection()
    {
        mysql_close(connector);
    }
};