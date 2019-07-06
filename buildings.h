
#pragma once

#include <vector>
#include "building.h"
#include "thing.h"
#include "texture.h"
#include "functions.h"
#include "roads.h"

class buildings{

	private:

		bool busy = false;
		roads roadmanager;
		int typecount = 5;
		std::vector<building> list[5];
		texture textures[5] ={

			texture("resources/textures/building.png"),
			texture("resources/textures/building2.png"),
			texture("resources/textures/building3.png"),
			texture("resources/textures/building4.png"),
			texture("resources/textures/building5.png")
		};
		thing things[5] = { //needs to be automated like in world.cpp

			thing(100, textures[0].h / 2),
			thing(150, textures[1].h / 2),
			thing(200, textures[2].h / 2),
			thing(250, textures[3].h / 2),
			thing(300, textures[4].h / 2)
		};
		int counts[5];
		void update(int type);

	public:

		buildings();
		void add(float x_, float y_, int type);
		void display();
};
