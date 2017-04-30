#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

std::vector<std::string> elementos;
std::unordered_map<std::string, std::string> map;

void add() {
	int num;
	std::string copia;
	std::cin >> num;
	copia = elementos[num];
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
}

void main() {
	std::cout << "------------------" << std::endl;
	std::cout << "FULLENTI ALCHEMIST" << std::endl;
	std::cout << "------------------" << std::endl;
	help();
	addbasics();
	std::cout << "You have those elements:" << std::endl;
	for (int i = 0; i < elementos.size(); i++) {
		std::cout << i+1 << ": " << elementos[i] << std::endl;
	}
	std::string written;
	std::cin >> written;
	//Bucle del juego
	while (written != "endgame") 
	{
		if (written == "add") {add();}
		else if (written == "addbasics") {addbasics();}
		else if (written == "delete") {delet();}
		else if (written == "info") {info();}
		else if (written == "sort") {sort();}
		else if (written == "clean") {clean();}
		else if (written == "help") {help();}
		else {std::cout << "and another one" << std::endl;}

		std::cout << "You have those elements:" << std::endl;
		for (int i = 0; i < elementos.size(); i++) {
			std::cout << i+1 << ": " << elementos[i] << std::endl;
		}
		std::cin >> written;
		system("cls");
	}
}