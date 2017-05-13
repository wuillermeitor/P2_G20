#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstddef>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

//Declaraci�n de la variables generales
std::vector<std::string> elementos({" "});
std::vector<std::string> elementosNuevos;
std::unordered_map<std::string, std::string> mapaElementos;
int score;

void add(int str) {
	//Condici�n que impedir� que el jugador intente acceder a un elemento que no est� en su lista.
	if (str < elementos.size() && str > 0) {
		//Creo un string al que le pongo como valor el elemento en la posici�n dada por el jugador
		//y hago push_back para insertarlo al final del vector de elementos. 
		std::string copia;
		copia = elementos[str];
		elementos.push_back(copia);
	}
}

void addbasics() {
	//Simplemente hacemos push_back de los elementos b�sicos para a�adirlos al final del vector de elementos.
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
}

void delet(int str) {
	//Condici�n que impedir� que el jugador intente acceder a un elemento que no est� en su lista.
	if (str < elementos.size() && str > 0) {
		//se hace un erase del elemento que est� en la pocici�n dada por el jugador
		elementos.erase(elementos.begin() + str);
	}
}

void info(int str) {
	//Condici�n que impedir� que el jugador intente acceder a un elemento que no est� en su lista.
	if (str < elementos.size() && str > 0) {
		//Guardamos el valor que de el jugador para a�adir el elemento que le pertenece al final del link de wikipedia.
		std::string url;
		url = "https://en.wikipedia.org/wiki/" + elementos[str];
																	//l�nea de c�digo que nos ofrecisteis en el documento explicativo del juego.
		ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	}
}

void sort() {
	//funci�n simple que ordena autom�ticamente los elementos por orden alfab�tico gracias a sort.
	std::sort(elementos.begin(), elementos.end());
}

void clean() {
	//Se ordenan los elementos con la funci�n sort y se recorre el vector para comprobar si hay elementos
	//repetidos, y en ese caso, suprimirlos.
	sort();
	elementos.erase(std::unique(elementos.begin(), elementos.end()), elementos.end());
}

void help() {
	//Simplemente se imprimen por pantalla las instrucciones del juego.
	std::cout << "- Enter two numbers of your elements list to combine them." << std::endl;
	std::cout << "- Enter the word 'add' and the number of an element to add a new instance of that element." << std::endl;
	std::cout << "- Enter 'add basics' to add new instances of the 4 basic elements." << std::endl;
	std::cout << "- Enter the word 'delete' and the number of an element to erase it from your list." << std::endl;
	std::cout << "- Enter the word 'info' and the number of an element to get information about it in the explorer." << std::endl;
	std::cout << "- Enter the word 'sort' to sort by alphabetical order the elements in the list." << std::endl;
	std::cout << "- Enter the word 'clean' to delete all the instances of repeated elements." << std::endl;
	std::cout << "- Enter the word 'help' to show this tutorial." << std::endl;
	std::cout << std::endl;
}

void readFile()
{
	//Declaraci�n de las variables que vamos a usar en esta funci�n.
	std::ifstream archivo;
	std::string text;
	//Abrimos el archivo que enecesitamos para el juego.
	archivo.open("elements.dat", std::ios::in);

	if (archivo.fail()) {
		//Si el archivo no se encuentra, se cerrar� el juego.
		std::cout << "Cannot read combinations of elements from file elements.dat." << std::endl;
		std::cout << "Check that it's placed in the same directory as Alchemy.exe!" << std::endl;
		system("pause");
	}

	while (!archivo.eof()) {
		//En caso de encontrarse, se recorrer� todo el archivo l�nea a l�nea. Se guarar� como key 
		//el resultado de combinar dos elementos, y los dos elementos como un solo value.
		std::getline(archivo, text);
		int limitKey = 0;
		int i = 0;
		while (i < text.length() && limitKey == 0) {
			//En este bucle se separa la key de su value.
			if (text[i] == '=') limitKey = i;
			++i;
		}
		std::pair<std::string, std::string> auxiliarMapa;
		std::string key = text.substr(0, limitKey - 1);
		std::string count = text.substr(limitKey + 2, text.length() - (limitKey + 2));
		mapaElementos[count] = key;
	}
	//una vez se haya recorrido todo el archivo, se cerrar�.
	archivo.close();
}

void scoreManager(std::string result); //Forward declaration

void comb(int num1, int num2) {
	system("cls");
	//Condici�n que impedir� que el jugador intente acceder a un elemento que no est� en su lista.
	if (num1 < elementos.size() && num2 < elementos.size() && num1 > 0 && num2 > 0) {
		//Condici�n que comprobar� si el jugador ha escrito el mismo n�mero dos veces. En caso negativo, se
		//seguir� con normalidad.
		if (num1 != num2) {
			//En caso de que el jugador haya escrito primero un n�mero superior al segundo de su lista de elementos,
			//se cambiar�n de posici�n para facilitar la eliminaci�n de �stos m�s tarde e impedir que se produzcan errores
			//en el juego.
			if (num1 > num2) {
				int tmp;
				tmp = num1;
				num1 = num2;
				num2 = tmp;
			}
			//Declaraci�n de dos elementos del tipo string para almacenar en ellos los elementos de las posiciones indicadas
			//por el jugador.
			std::string elem1, elem2;
			elem1 = elementos[num1];
			elem2 = elementos[num2];
			//Se crea un auxiliar del tipo string que guardar� el s�mbolo " + " para ayudarnos posteriormente a combinar los
			//dos elementos en un solo string y comprobar si �ste tiene una key.
			std::string aux = " + ";
			std::string comb = elem1 + aux + elem2;
			//Con un iterador, se comprueba si el string reci�n creado tiene una key en el mapa de elementos.
			std::unordered_map<std::string, std::string>::iterator it;
			it = mapaElementos.find(comb);
			//Si el iterador no llega al final del mapa de elementos, significa que ha encontrado la combinaci�n, y en ese caso 
			//se eliminar�n los elementos usados en la combinaci�n y se llamar� a la funci�n scoreManager, y se a�adir� el
			//resultado de la combinaci�n al vector de elementos.
			if (it != mapaElementos.end()) {
				elementos.erase(elementos.begin() + num1);
				elementos.erase(elementos.begin() + num2 -1);
				std::string result = it->second;
				scoreManager(result);
				elementos.push_back(result);
			}
			//En cambio, si el iterador alcanza el final del mapa, significa que dicha combinaci�n no existe. 
			else {
				std::cout << "Combination failure, try again!" << std::endl;
			}
		}
		//�ste es el resultado de intentar combinar el mismo elemento en una misma posici�n, como "4 4".
		else {
			std::cout << "Cannot combine the same element!" << std::endl;
		}
	}
}

void scoreManager(std::string result) {
	//Comprueba si el elemento que hemos creado ya se hab�a creado con anterioridad.
	//Si no exist�a, aumenta el score. En cambio, si ya se conoc�a la combinaci�n, 
	//simplemente se a�adir�.
	bool combDescubierta = false;
	for (auto it = elementosNuevos.begin(); it != elementosNuevos.end(); it++) {
		if (*it == result) {
			combDescubierta = true;
		}
	}
	if (combDescubierta == false) {
		std::cout << "New element found: " << result << std::endl;
		++score;
		elementosNuevos.push_back(result);
	}
}

void startgame() {
	//Funci�n en la que se imprimir� el t�tuo del juego, se llamar�n a las funciones help() y addbasics()
	//para construir el inicio del juego, y se imprimir�n los elementos disponibles gracias a un bucle for.
	std::cout << "------------------" << std::endl;
	std::cout << "FULLENTI ALCHEMIST" << std::endl;
	std::cout << "------------------" << std::endl;
	help();
	addbasics();
	std::cout << "You current score: " << score << std::endl;
	std::cout << "You have those elements:" << std::endl;
	for (int i = 1; i < elementos.size(); ++i) {
		std::cout << i << ": " << elementos[i] << std::endl;
	}
}

//MAIN del juego
void main() {
	//Llamamos a la funci�n que leer� el archivo y lo almacenar� en un unordered_map.
	readFile();
	//Inicialziamos la score a 0.
	score = 0;
	//Llamamos a la funci�n que iniciar� el juego con los elementos principales.
	startgame();
	//Delcaramos un string que se leer� con un getline, similar al cin, pero que en vez de 
	//coger una sola palabra, coger� todo lo que se escriba. Se almacenar� la primera palabra
	//en un string auxiliar y la segunda (y lo que reste) en un segundo string auxiliar. La separaci�n
	//la marcar� el espacio entre las palabras.
	std::string written;
	getline(std::cin, written);
	std::string str1;
	std::string str2;
	std::size_t found = written.find_last_of(" ");
	str1 = written.substr(0, found);
	str2 = written.substr(found + 1);

	//Bucle del juego. Mientras el jugador no escriba endgame, el juego seguir�.
	while (str1 != "endgame")
	{
		//Limpiamos la pantalla al principio de cada acci�n para que no se acumulen muchos elementos.
		system("cls");
		//Si el jugador no escirbe ninguna de las opciones dadas, se comprobar� si lo que ha escrito son n�meros. En caso afirmativo, se llamar�
		//a la funci�n comb con str1 y str2 casteados a integer como argumento. Si no son n�meros, no pasar� nada.
		if (str1 != "\n") {
			if (std::atoi(str1.c_str()) && std::atoi(str2.c_str())) {
				bool isanumber = true;
				for (int i = 0; i < str1.size(); i++) {
					if (str1[i] != '0' && str1[i] != '1' && str1[i] != '2' && str1[i] != '3' && str1[i] != '4' && str1[i] != '5' && str1[i] != '6' && str1[i] != '7' && str1[i] != '8' && str1[i] != '9') {
						isanumber = false;
					}
				}
				for (int i = 0; i < str2.size(); i++) {
					if (str2[i] != '0' && str2[i] != '1' && str2[i] != '2' && str2[i] != '3' && str2[i] != '4' && str2[i] != '5' && str2[i] != '6' && str2[i] != '7' && str2[i] != '8' && str2[i] != '9') {
						isanumber = false;
					}
				}
				if (isanumber == true) {
					int tmp1 = stoi(str1);
					int tmp2 = stoi(str2);
					comb(tmp1, tmp2);
				}
			}
			//Si el jugador escribe add, pueden pasar varias cosas:
			else if (str1 == "add") {
				//Si la segunda paalabra es basics, se llamar� a la funci�n addbasics().
				if (str2 == "basics") {
					addbasics();
				}
				//Si no, se comprobar� si lo que ha escrito es un n�mero. En caso negativo, no pasar� nada. En caso afirmativo, se llamar�
				//a la funci�n add() con el argumento str2 casteado a integer.
				else {
					bool isanumber = true;
					for (int i = 0; i < str2.size(); i++) {
						if (str2[i] != '0' && str2[i] != '1' && str2[i] != '2' && str2[i] != '3' && str2[i] != '4' && str2[i] != '5' && str2[i] != '6' && str2[i] != '7' && str2[i] != '8' && str2[i] != '9') {
							isanumber = false;
						}
					}
					if (isanumber == true) {
						int tmp = stoi(str2);
						add(tmp);
					}
				}
			}
			//Si el jugador escribe delete, se comprobar� si el valor almacenado en str2 es un n�mero. En caso negativo, no pasar� nada. En caso afirmativo,
			//se llamar� a la funci�n delet() y se le pasar� como argumento str2 casteado a integer.
			else if (str1 == "delete") {
				bool isanumber = true;
				for (int i = 0; i < str2.size(); i++) {
					if (str2[i] != '0' && str2[i] != '1' && str2[i] != '2' && str2[i] != '3' && str2[i] != '4' && str2[i] != '5' && str2[i] != '6' && str2[i] != '7' && str2[i] != '8' && str2[i] != '9') {
						isanumber = false;
					}
				}
				if (isanumber == true) {
					int tmp = stoi(str2);
					delet(tmp);
				}
			}
			//Si el jugador escribe info, se comprobar� si el valor almacenado en str2 es un n�mero. En caso negativo, no pasar� nada. En caso afirmativo,
			//se llamar� a la funci�n info() y se le pasar� como argumento str2 casteado a integer.
			else if (str1 == "info") {
				bool isanumber = true;
				for (int i = 0; i < str2.size(); i++) {
					if (str2[i] != '0' && str2[i] != '1' && str2[i] != '2' && str2[i] != '3' && str2[i] != '4' && str2[i] != '5' && str2[i] != '6' && str2[i] != '7' && str2[i] != '8' && str2[i] != '9') {
						isanumber = false;
					}
				}
				if (isanumber == true) {
					int tmp = stoi(str2);
					info(tmp);
				}
			}
			//Si el jugador escribe sort, se llamar� a la funci�n sort().
			else if (str1 == "sort") {
				sort();
			}
			//Si el jugador escribe clean, se llamar� a la funci�n clean().
			else if (str1 == "clean") {
				clean();
			}
			//Si el jugador escribe help, se llamar� a la funci�n help().
			else if (str1 == "help") {
				help();
			}
			//Finalmente, se escribe la puntuaci�n del jugador y los elementos disponibles. Adem�s, se volver� a pedir que escriba 
			//algo por pantalla.
			std::cout << "You current score: " << score << std::endl;
			std::cout << "You have those elements:" << std::endl;
			for (int i = 1; i < elementos.size(); ++i) {
				std::cout << i << ": " << elementos[i] << std::endl;
			}

			getline(std::cin, written);
			std::size_t found = written.find_last_of(" ");
			str1 = written.substr(0, found);
			str2 = written.substr(found + 1);
		}

	}
}