#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "headers\Menu.h"
#include "headers\Login.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string usuario;
	string password;
	char caracter;

	Login login = Login();
	Menu menu = Menu();

	while (true)
	{
		cout << "\n------------------Login------------------\n";
		cout << "Ingrese el nombre de usuario: ";
		cin >> usuario;
		cout << "Ingrese la contrasena: ";

		// Todo lo que esta dentro del bucle while es para ocultar la contraseña con un asterisco *
		caracter = getch();
		password = "";
		while (caracter != 13) // El numero 13 representa la tecla ENTER
		{
			if (caracter != 8) // El numero 8 representa la tecla BACKSPACE
			{
				password.push_back(caracter);
				cout << "*";
			}
			else
			{
				if (password.length() > 0) // Este bloque sirve para borrar caracteres en caso de equivocarse en la contraseña
				{
					cout << "\b \b";
					password.pop_back();
				}
			}
			caracter = getch();
		}

		// Se valida si el usuario existe en base de datos
		if (login.iniciarSesion(usuario, password) == 1)
		{
			system("cls"); // Esta linea limpia la consola
			menu.menuPrincipal();
			// break;
		}
		else
		{
			std::cout << "\nUsuario o contrasena incorrectos. Intente de nuevo.\n";
		}
	}
}