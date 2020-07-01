
#include <librg.h>
#include <iostream>
#include <vector>
#include <string>
#include "Server.h"
#include <algorithm>  
#include <map>

Server server;

void onConnection(librg_event* event){

	std::cout << event->peer << " connected." << std::endl;
}

void onPositionMessage(librg_message* message){

	float x = (int)librg_data_ru32(message->data);
	float y = (int)librg_data_ru32(message->data);

	librg_peer* p = server.pairs.find(message->peer)->second;
	server.relayPosition(p, x, y);
}

void onPairing(librg_message* message){

	int length = librg_data_ru32(message->data);
	char* pairName = new char[length];
	librg_data_rptr(message->data, pairName, sizeof(char) * length);

	librg_peer* pair = server.peers.find(pairName)->second;
	std::string sender = server.names.find(message->peer)->second;

	std::cout << sender << " connected to " << pairName << "." << std::endl;

	server.sendStart(pair);

	server.pairs.insert({message->peer, pair});  //
	server.pairs.insert({pair, message->peer }); //add to pair table
};

void onRegistration(librg_message* message){

	int nameLength = librg_data_ru32(message->data);
	char* input = new char[nameLength];
	librg_data_rptr(message->data, input, sizeof(char) * nameLength);

	std::string name = input;
	server.names.insert({ message->peer, name }); //add to name table
	server.peers.insert({ name, message->peer }); //add to peer table

	std::cout << name << " registered." << std::endl;

	server.sendPlayerList(message->peer); 
}

int main(){

	server.setEventHandler(LIBRG_CONNECTION_ACCEPT, onConnection);
	server.start();
	server.setMessageHandler(BUILDING_POSITION, onPositionMessage);
	server.setMessageHandler(PAIRING, onPairing);
	server.setMessageHandler(REGISTRATION, onRegistration);

	std::cout << "Server started." << std::endl;

	while(1) server.run();
	return 0;
}
