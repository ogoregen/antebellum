
#include "Menu.h"

Menu::Menu():

	current(0){

	state = MAIN;

	mainMenu.push_back("KEY_1  - solo practice");
	mainMenu.push_back("KEY_2  - multiplayer");
	mainMenu.push_back("KEY_3  - credits");
	mainMenu.push_back("ESCAPE - exit");

	mpMenu.push_back("ONLINE PLAYERS:");
}

void Menu::run(){

	typer.scale(1);
	typer.type(title, 40, y);
	y += 48;
	typer.scale(0.5);

	switch(state){

	case MAIN:

	for(int i = 0; i < mainMenu.size(); i++){

		std::string line = mainMenu[i];
		typer.type(line, 40, y);
		y += 32;
	} 

	break;
	case MP:
	
	for(int i = 0; i < mpMenu.size(); i++){

		std::string line = mpMenu[i];
		typer.type(line, 40, y);
		y += 32;
	}
	typer.type("enter player ID to join them", 40, y);
	y += 32;

	break;
	}

	y += 20;
	typer.type(prompt, 40, y);
	typer.type(input, 248, y);
	typer.type("|", 248 + (input.length()) * 13, y);
	y = 100;
	if(input == "1"){
		
		current = 1;
		input = "";
	} 
	else if(input == "2"){
		
		state = MP;
		current = 2;
		input = "";
	} 
}

int Menu::check(){

	return current;
}

void Menu::insert(char c){

		if(c == '<') input.pop_back();
		else input += c;
}

void Menu::insertPlayer(std::string s){

	mpMenu.push_back(s);
}
