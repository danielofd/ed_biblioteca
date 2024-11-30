#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "headers\Menu.h"
#include "headers\Login.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Login login = Login();
    Menu menu = Menu();
    
    do 
    {
        if (login.mostrarLogin())
        {
            menu.menuPrincipal();
        }
    } while (true);

    return 0;   
}