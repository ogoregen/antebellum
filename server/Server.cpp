
#define LIBRG_IMPLEMENTATION
#include "Server.h"

void onRequest(librg_event* event){

	u32 pass = librg_data_ru32(event->data);
	if(pass != 871797) librg_event_reject(event);
}

Server::Server(){

	ctx.mode = LIBRG_MODE_SERVER;
	librg_init(&ctx);
	librg_event_add(&ctx, LIBRG_CONNECTION_REQUEST, onRequest);
}

void Server::start(){

	librg_address address = { 7779 };
	librg_network_start(&ctx, (librg_address)address);
}

Server::~Server(){

	librg_network_stop(&ctx);
	librg_free(&ctx);
}

void Server::run(){

	librg_tick(&ctx);
}

void Server::sendStart(librg_peer* target){

	int a = 1;
	librg_message_send_to(&ctx, GAME_START, target, &a, sizeof(int));
}

void Server::setMessageHandler(int slot, void function(librg_message* message)){

	librg_network_add(&ctx, slot, function);
}

void Server::setEventHandler(int slot, void function(librg_event* event)){
	
	librg_event_add(&ctx, slot, function);
}

void Server::relayPosition(librg_peer* target, float x, float y){

	librg_data* data = librg_data_init_new();
	librg_data_wu32(data, x);
	librg_data_wu32(data, y);
	librg_message_send_to(&ctx, BUILDING_POSITION, target, data->rawptr, librg_data_get_wpos(data));
	librg_data_free(data);
}

void Server::sendPlayerList(librg_peer* target){

	librg_data* data = librg_data_init_new();
	librg_data_wu32(data, names.size());

	for(std::map<librg_peer*, std::string>::iterator i = names.begin(); i != names.end(); i++){

		std::string msg = i->second;
		int length = msg.length() + 1;
		librg_data_wu32(data, length);
		librg_data_wptr(data, &msg[0], sizeof(char) * length);
	}
	librg_message_send_to(&ctx, USER_LIST, target, data->rawptr, librg_data_get_wpos(data));
	librg_data_free(data);
}
