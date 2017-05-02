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
		std::pair<std::string, std::string> auxiliarMapa;
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
	//Condición que impedirá que el jugador intente acceder a un elemento que no esté en su lista.
	if (num1 < elementos.size() + 1 && num2 < elementos.size() + 1 && num1 > 0 && num2 > 0) {
		//Condición que comprobará si el jugador ha escrito el mismo número dos veces. En caso negativo, se
		//seguirá con normalidad.
		if (num1 != num2) {
			//En caso de que el jugador haya escrito primero un número superior al segundo de su lista de elementos,
			//se cambiarán de posición para facilitar la eliminación de éstos más tarde e impedir que se produzcan errores
			//en el juego.
			if (num1 > num2) {
				int tmp;
				tmp = num1;
				num1 = num2;
				num2 = tmp;
			}
			//Declaración de dos elementos del tipo string para almacenar en ellos los elementos de las posiciones indicadas
			//por el jugador.
			std::string elem1, elem2;
			elem1 = elementos[num1 - 1];
			elem2 = elementos[num2 - 1];
			//Se crea un auxiliar del tipo string que guardará el símbolo " + " para ayudarnos posteriormente a combinar los
			//dos elementos en un solo string y comprobar si éste tiene una key.
			std::string aux = " + ";
			std::string comb = elem1 + aux + elem2;
			//Con un iterador, se comprueba si el string recién creado tiene una key en el mapa de elementos.
			std::unordered_map<std::string, std::string>::iterator it;
			it = mapaElementos.find(comb);
			//Si el iterador no llega al final del mapa de elementos, significa que ha encontrado la combinación, y en ese caso 
			//se eliminarán los elementos usados en la combinación y se llamará a la función scoreManager, y se añadirá el
			//resultado de la combinación al vector de elementos.
			if (it != mapaElementos.end()) {
				elementos.erase(elementos.begin() + num1 - 1);
				elementos.erase(elementos.begin() + num2 - 2);
				std::string result = it->second;
				scoreManager(result);
				elementos.push_back(result);
			}
			//En cambio, si el iterador alcanza el final del mapa, significa que dicha combinación no existe. 
			else {
				std::cout << "Combination failure, try again!" << std::endl;
			}
		}
		//Éste es el resultado de intentar combinar el mismo elemento en una misma posición, como "4 4".
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
	//Función en la que se imprimirá el títuo del juego, se llamarán a las funciones help() y addbasics()
	//para construir el inicio del juego, y se imprimirán los elementos disponibles gracias a un bucle for.
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

//MAIN del juego
void main() {
	//Llamamos a la función que leerá el archivo y lo almacenará en un unordered_map.
	readFile();
	//Inicialziamos la score a 0.
	score = 0;
	//Llamamos a la función que iniciará el juego con los elementos principales.
	startgame();
	//Delcaramos un string que se leerá con un getline, similar al cin, pero que en vez de 
	//coger una sola palabra, cogerá todo lo que se escriba. Se almacenará la primera palabra
	//en un string auxiliar y la segunda (y lo que reste) en un segundo string auxiliar. La separación
	//la marcará el espacio entre las palabras.
	std::string written;
	getline(std::cin, written);
	std::string str1;
	std::string str2;
	std::size_t found = written.find_last_of(" ");
	str1 = written.substr(0, found);
	str2 = written.substr(found + 1);

	//Bucle del juego. Mientras el jugador no escriba endgame, el juego seguirá.
	while (str1 != "endgame")
	{
		//Limpiamos la pantalla al principio de cada acción para que no se acumulen muchos elementos.
		system("cls");
		//Si el jugador escribe add, pueden pasar varias cosas:
		if (str1 == "add") {
			//Si la segunda paalabra es basics, se llamará a la función addbasics().
			if (str2 == "basics") {
				addbasics();
			}
			//Si no, se comprobará si lo que ha escrito es un número. En caso negativo, no pasará nada. En caso afirmativo, se llamará
			//a la función add() con el argumento str2 casteado a integer.
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
		//Si el jugador escribe delete, se comprobará si el valor almacenado en str2 es un número. En caso negativo, no pasará nada. En caso afirmativo,
		//se llamará a la función delet() y se le pasará como argumento str2 casteado a integer.
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
		//Si el jugador escribe info, se comprobará si el valor almacenado en str2 es un número. En caso negativo, no pasará nada. En caso afirmativo,
		//se llamará a la función info() y se le pasará como argumento str2 casteado a integer.
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
		//Si el jugador escribe sort, se llamará a la función sort().
		else if (str1 == "sort") {
			sort();
		}
		//Si el jugador escribe clean, se llamará a la función clean().
		else if (str1 == "clean") {
			clean();
		}
		//Si el jugador escribe help, se llamará a la función help().
		else if (str1 == "help") {
			help();
		}
		//Si el jugador no escirbe ninguna de las opciones anteriores, se comprobará si lo que ha escrito son números. En caso afirmativo, se llamará
		//a la función comb con str1 y str2 casteados a integer como argumento. Si no son números, no pasará nada.
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
		//Finalmente, se escribe la puntuación del jugador y los elementos disponibles. Además, se volverá a pedir que escriba 
		//algo por pantalla.
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