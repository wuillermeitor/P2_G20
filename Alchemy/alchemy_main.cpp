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

std::vector<std::string> elementos;
std::unordered_map<std::string, std::string> mapaElementos;
int score;

void add(int str) {
	std::string copia;
	copia = elementos[str-1];
	elementos.push_back(copia);
}

void addbasics() {
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
}

void delet() {
	int num;
	std::cin >> num;
	elementos.erase(elementos.begin() + num);
}

void info() {
	int num;
	std::cin >> num;
	std::string url;
	url = "https://en.wikipedia.org/wiki/" + elementos[num];
	ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

void sort() {
	std::sort(elementos.begin(), elementos.end());
}

void clean() {
	std::sort(elementos.begin(), elementos.end());
	elementos.erase(std::unique(elementos.begin(), elementos.end()), elementos.end());
}

void help() {
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
	std::ifstream archivo;
	std::string text;
	archivo.open("elements.dat", std::ios::in);

	if (archivo.fail()) {
		std::cout << "Cannot read combinations of elements from file elements.dat." << std::endl;
		std::cout << "Check that it's placed in the same directory as Alchemy.exe!" << std::endl;

		exit(1);
	}

	while (!archivo.eof()) {

		std::getline(archivo, text);

		int j = 0;
		int i = 0;
		while (i < text.length() && j == 0) {
			if (text[i] == '=') j = i;
			++i;
		}

		std::string key = text.substr(0, j - 1);
		std::string cont = text.substr(j + 2, text.length() - (j + 2));
		mapaElementos[cont] = key;

		//std::cout << key << std::endl;
		//std::cout << cont << std::endl;


	}
	//std::cout << text << std::endl;

	archivo.close();
}

void comb(int num1, int num2) {
	system("cls");
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
			elementos.push_back(result);
			++score;
			std::cout << "New element found: " << result << std::endl;
		}
		else {
			std::cout << "Combination failure, try again!" << std::endl;
		}
	}
	else {
		std::cout << "Cannot combine the same element!" << std::endl;
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

void splitString(std::string string, std::string string1, std::string string2) {
	std::size_t found = string.find_last_of(" ");
	string1 = string.substr(0, found);
	string2 = string.substr(found + 1);
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
		if (str1 == "add" && str2 != "basics") {
			int tmp = stoi(str2);
			add(tmp);
		}
		else if (str1 == "add" && str2 == "basics") { addbasics(); }
		else if (str1 == "delete") { delet(); }
		else if (str1 == "info") { info(); }
		else if (str1 == "sort") { sort(); }
		else if (str1 == "clean") { clean(); }
		else if (str1 == "help") { help(); }
		else {
			int tmp1 = stoi(str1);
			int tmp2 = stoi(str2);
			comb(tmp1, tmp2); 
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