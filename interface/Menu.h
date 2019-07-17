
#pragma once
#include <string>
#include "Typer.h"
#include <vector>

enum page{MAIN, MP};

class Menu{

	private:

		std::string prompt = "root@antebellum>";
		std::string input = "";
		std::string title = "Antebellum - version 0.1";
		std::vector<std::string> mainMenu;
		std::vector<std::string> mpMenu;
		Typer typer;
		int y = 100;

	public:

		int current;
		page state;

		Menu();
		void run();
		int check();
		void insert(char c);

		void insertPlayer(std::string s);

};
