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

//Declaración de la variables generales
std::vector<std::string> elementos;
std::vector<std::string> elementosNuevos;
std::unordered_map<std::string, std::string> mapaElementos;
int score;

void add(int str) {
	//Condición que impedirá que el jugador intente acceder a un elemento que no esté en su lista.
	if (str < elementos.size() + 1 && str > 0) {
		//Creo un string al que le pongo como valor el elemento en la posición dada por el jugador
		//y hago push_back para insertarlo al final del vector de elementos. 
		std::string copia;
		copia = elementos[str - 1]; //(*)
		elementos.push_back(copia);
	}
	//(*) Añadimos un -1 porque en vez de ir de 0 a x, va de 1 a x+1, por lo tanto hay que restarle 1 al valor 
	//que de el jugador de para que se adapte al valor real.
}

void addbasics() {
	//Simplemente hacemos push_back de los elementos básicos para añadirlos al final del vector de elementos.
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
}

void delet(int str) {
	//Condición que impedirá que el jugador intente acceder a un elemento que no esté en su lista.
	if (str < elementos.size() + 1 && str > 0) {
		//se hace un erase del elemento que esté en la posición dada por el jugador
		elementos.erase(elementos.begin() + str - 1); //(*)
	}
	//(*) Añadimos un -1 porque en vez de ir de 0 a x, va de 1 a x+1, por lo tanto hay que restarle 
	//1 al valor que de el jugador de para que se adapte al valor real.
}

void info(int str) {
	//Condición que impedirá que el jugador intente acceder a un elemento que no esté en su lista.
	if (str < elementos.size() + 1 && str > 0) {
		//Guardamos el valor que de el jugador para añadir el elemento que le pertenece al final del link de wikipedia.
		std::string url;
		url = "https://en.wikipedia.org/wiki/" + elementos[str - 1];//(*)
		//línea de código que nos ofrecisteis en el documento explicativo del juego.
		ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	}
	//(*) Añadimos un -1 porque en vez de ir de 0 a x, va de 1 a x+1, por lo tanto hay que restarle 
	//1 al valor que de el jugador de para que se adapte al valor real.
}

void sort() {
	//función simple que ordena automáticamente los elementos por orden alfabético gracias a sort.
	std::sort(elementos.begin(), elementos.end());
}

void clean() {
	//Se ordenan los elementos con la función sort y se recorre el vector para comprobar si hay elementos
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
	//Declaración de las variables que vamos a usar en esta función.
	std::ifstream archivo;
	std::string text;
	//Abrimos el archivo que enecesitamos para el juego.
	archivo.open("elements.dat", std::ios::in);

	if (archivo.fail()) {
		//Si el archivo no se encuentra, se cerrará el juego.
		std::cout << "Cannot read combinations of elements from file elements.dat." << std::endl;
		std::cout << "Check that it's placed in the same directory as Alchemy.exe!" << std::endl;

		exit(1);
	}

	while (!archivo.eof()) {
		//En caso de encontrarse, se recorrerá todo el archivo línea a línea. Se guarará como key 
		//el resultado de combinar dos elementos, y los dos elementos como un solo value.
		std::getline(archivo, text);
		int limitKey = 0;
		int i = 0;
		while (i < text.length() && limitKey == 0) {
			//En este bucle se separa la key de su value.
			if (text[i] == '=') limitKey = i;
			++i;
		}
		std::string key = text.substr(0, limitKey - 1);
		std::string count = text.substr(limitKey + 2, text.length() - (limitKey + 2));
		mapaElementos[count] = key;
	}
	//una vez se haya recorrido todo el archivo, se cerrará.
	archivo.close();
}

void scoreManager(std::string result); //Forward declaration

void comb(int num1, int num2) {
	system("cls");
	if (num1 < elementos.size() + 1 && num2 < elementos.size() + 1 && num1 > 0 && num2 > 0) {
		if (num1 != num2) {
			if (num1 > num2) {
				int tmp;
				tmp = num1;
				num1 = num2;
				num2 = tmp;
			}
			std::string elem1, elem2;
			elem1 = elementos[num1 - 1];
			elem2 = elementos[num2 - 1];
			std::string aux = " + ";
			std::string comb = elem1 + aux + elem2;
			std::unordered_map<std::string, std::string>::iterator it;
			it = mapaElementos.find(comb);
			if (it != mapaElementos.end()) {
				elementos.erase(elementos.begin() + num1 - 1);
				elementos.erase(elementos.begin() + num2 - 2);
				std::string result = it->second;
				scoreManager(result);
				elementos.push_back(result);
			}
			else {
				std::cout << "Combination failure, try again!" << std::endl;
			}
		}
		else {
			std::cout << "Cannot combine the same element!" << std::endl;
		}
	}
}

void scoreManager(std::string result) {
	//Comprueba si el elemento que hemos creado ya se había creado con anterioridad.
	//Si no existía, aumenta el score. En cambio, si ya se conocía la combinación, 
	//simplemente se añadirá.
	bool combDescubierta = false;
	for (auto it = elementosNuevos.begin(); it != elementosNuevos.end(); it++) {
		if (*it==result) {
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
	std::cout << "------------------" << std::endl;
	std::cout << "FULLENTI ALCHEMIST" << std::endl;
	std::cout << "------------------" << std::endl;
	help();
	addbasics();
	std::cout << "You current score: " << score << std::endl;
	std::cout << "You have those elements:" << std::endl;
	for (int i = 0; i < elementos.size(); i++) {
		std::cout << i + 1 << ": " << elementos[i] << std::endl;
	}
}

void main() {
	readFile();
	score = 0;
	startgame();
	std::string written;
	getline(std::cin, written);
	std::string str1;
	std::string str2;
	std::size_t found = written.find_last_of(" ");
	str1 = written.substr(0, found);
	str2 = written.substr(found + 1);

	//Bucle del juego
	while (str1 != "endgame")
	{
		system("cls");
		if (str1 == "add") {
			if (str2 == "basics") {
			addbasics();
			}
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
		else if (str1 == "delete") {
			int tmp = stoi(str2);
			delet(tmp);
		}
		else if (str1 == "info") {
			int tmp = stoi(str2);
			info(tmp);
		}
		else if (str1 == "sort") {
			sort();
		}
		else if (str1 == "clean") {
			clean();
		}
		else if (str1 == "help") {
			help();
		}
		else {
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
		std::cout << "You current score: " << score << std::endl;
		std::cout << "You have those elements:" << std::endl;
		for (int i = 0; i < elementos.size(); i++) {
			std::cout << i + 1 << ": " << elementos[i] << std::endl;
		}
		getline(std::cin, written);
		std::size_t found = written.find_last_of(" ");
		str1 = written.substr(0, found);
		str2 = written.substr(found + 1);
	}
}