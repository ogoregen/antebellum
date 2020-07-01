
#pragma once
#include <librg.h>
#include <string>
#include <vector>
#include <map>

enum messageType{

	BUILDING_POSITION = LIBRG_EVENT_LAST,
	PAIRING = LIBRG_EVENT_LAST + 1,
	USER_LIST = LIBRG_EVENT_LAST + 2,
	REGISTRATION = LIBRG_EVENT_LAST + 3,
	GAME_START = LIBRG_EVENT_LAST + 4
};

class Server{

	private:

		librg_ctx ctx = { 0 };

	public:

		std::map<librg_peer*, librg_peer*> pairs;
		std::map<librg_peer*, std::string> names;
		std::map<std::string, librg_peer*> peers;
		Server();
		void start();
		~Server();
		void run();
		void sendStart(librg_peer* target);
		void setMessageHandler(int target, void function(librg_message* message));
		void setEventHandler(int slot, void function(librg_event* event));
		void relayPosition(librg_peer* sender, float x, float y);
		void sendPlayerList(librg_peer* target);
};
